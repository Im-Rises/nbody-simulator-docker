#include <cmath>
#include <glm/glm.hpp>

#include <chrono>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>

#include <nlohmann/json.hpp>

#include <curl/curl.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <csignal>
#endif

const float GravityConstant = 1.0F;
const float ParticleMass = 50.0F;
const float FixedDeltaTime = 0.02F;
const float Softening = 10.0F;
const float Friction = 0.99F;
const float SpawnRadius = 3.0F;

int baseIndex;
int numParticles;
std::string addressPost;
int currentFrame = -1;
bool changedFrame = false;
CURL* curlPostParticles;
CURL* curlGetFrame;
CURL* curlGetParticles;

std::string getParticleBuffer;

bool exitMainLoopFlag = false;


struct Particle {
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;

    Particle() : position(glm::vec3(0.0F)), velocity(glm::vec3(0.0F, 0.0F, 0.0F)) {}
};

std::vector<Particle> modifiedParticles;
std::vector<Particle> allParticles;

void signalHandler(int signum) {
    if (signum == SIGINT)
    {
        exitMainLoopFlag = true;
    }
}

// Update la physique des particules que gère le conteneur
void updatePhysics( float deltaTime) {
    for (auto& particle : modifiedParticles)
    {
        glm::vec3 sumForces(0.0F, 0.0F, 0.0F);
        for (auto& otherParticle : allParticles)
        {
            if (&particle != &otherParticle)
            {
                auto distance = glm::distance(particle.position, otherParticle.position);
                auto direction = glm::normalize(otherParticle.position - particle.position);

                auto force = GravityConstant * ParticleMass * ParticleMass / ((distance * distance) + Softening);
                sumForces += direction * force;
            }

            particle.acceleration = sumForces / ParticleMass;
        }
    }

    for (auto& particle : modifiedParticles)
    {
        particle.position += (particle.velocity * deltaTime) + ((particle.acceleration * (deltaTime * deltaTime)) / 2.0F);
        particle.velocity += particle.acceleration * deltaTime;
        particle.velocity *= Friction;
    }
}

// Retourne le string contenant le json des particules du conteneur
auto particlesToJson(const std::vector<Particle>& particles, int baseIndex) -> nlohmann::json {
    nlohmann::json json;
    json["particules"] = nlohmann::json::array();
    for (int i = baseIndex; i < baseIndex + numParticles; i++)
    {
        json["particules"].push_back(
            { { "index", 2 * i + baseIndex },
                { "position", { modifiedParticles[i].position.x, modifiedParticles[i].position.y, modifiedParticles[i].position.z } },
                { "velocity", { modifiedParticles[i].velocity.x, modifiedParticles[i].velocity.y, modifiedParticles[i].velocity.z } } });

    }
    return json;
}

// Update particles pour qu'elles soient en accord avec le json que retourne la base de données
void parseJsonToParticles() {
    std::cout << "request all particules : " << getParticleBuffer << std::endl;
    nlohmann::json j = nlohmann::json::parse(getParticleBuffer);
    getParticleBuffer.clear();

    int len = j["particules"].size();
    if(allParticles.empty()) {
        allParticles.resize(len);
    }

    for(const auto& particule : j["particules"]) {
        // parse json string which represent the particle
        nlohmann::json p = nlohmann::json::parse(particule.get<std::string>());

        // make a vec3 with the position in the json particle
        allParticles[p["index"]].position = glm::vec3(p["position"][0], p["position"][1], p["position"][2]);
        //res.emplace_back(particules["position"][0], particules["position"][1], particules["position"][2]);
    }
}

// callback de la fonction curlPostParticles
size_t static dumpCallback(char* ptr, size_t size, size_t nmemb, void* userdata) {
    return size * nmemb;
}

// callback de la fonction curlGetFrame stocke le frame dans la variable currentFrame et si le frame change set changedFrame a true
// se qui déclenchera la fonction curlGetParticles
size_t static callbackGetFrame(char* ptr, size_t size, size_t nmemb, void* userdata) {
    std::cout << "string : " << ptr << std::endl;
    nlohmann::json j = nlohmann::json::parse(ptr);


    if(currentFrame != j["frame"]) {
        changedFrame = true;
        currentFrame = j["frame"];
    }

    return size * nmemb;
}

// callback de la fonction curlGetParticles stocke le json contenant les particules dans la variable getParticleBuffer
size_t static callbackGetParticles(char* ptr, size_t size, size_t nmemb, void* userdata) {
    getParticleBuffer.append(ptr);

    return size * nmemb;
}

// Initialize les 3 requêtes que va faire le docker
void initializeRequest() {
        curl_global_init(CURL_GLOBAL_ALL);
        curlPostParticles = curl_easy_init();
        // La requête POST qui se charge d'envoyer les particules au serveur
        if (curlPostParticles)
        {
            curl_easy_setopt(curlPostParticles, CURLOPT_URL, (addressPost + "/api/").c_str());
            // Définition de l'en-tête "Content-Type: application/json"
            struct curl_slist* headers = NULL;
            headers = curl_slist_append(headers, "Content-Type: application/json");
            curl_easy_setopt(curlPostParticles, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curlPostParticles, CURLOPT_CUSTOMREQUEST, "POST");

            curl_easy_setopt(curlPostParticles, CURLOPT_WRITEFUNCTION, dumpCallback);
            curl_easy_setopt(curlPostParticles, CURLOPT_VERBOSE, 0L); // change to 1L to see verbose output
        }
        else {
            std::cout << "Error generatiing Curl Get Frame" << std::endl;
        }

        curlGetFrame = curl_easy_init();
        // La requête GET qui se charge de récupérer le frame actuel
        if(curlGetFrame) {
            curl_easy_setopt(curlGetFrame, CURLOPT_URL, (addressPost + "/getFrame/").c_str());
            curl_easy_setopt(curlGetFrame, CURLOPT_CUSTOMREQUEST, "GET");

            curl_easy_setopt(curlGetFrame, CURLOPT_WRITEFUNCTION, callbackGetFrame);
            curl_easy_setopt(curlGetFrame, CURLOPT_VERBOSE, 0L); // change to 1L to see verbose output
        }
        else {
            std::cout << "Error generatiing Curl Get Frame" << std::endl;
        }

        curlGetParticles = curl_easy_init();
        // La requête GET qui se charge de récupérer les particules du frame actuel
        if(curlGetParticles) {
            curl_easy_setopt(curlGetParticles, CURLOPT_URL, (addressPost + "/all/particules").c_str());
            curl_easy_setopt(curlGetParticles, CURLOPT_VERBOSE, 0L);

            // Configuration de la fonction de rappel pour stocker la réponse
            curl_easy_setopt(curlGetParticles, CURLOPT_WRITEFUNCTION, callbackGetParticles);
        }
        else {
            std::cout << "Error generatiing Curl Get Frame" << std::endl;
        }
}

// Envoie les particules au serveur
void curlPostRequest(const std::string& data) {
    CURLcode res;

    curl_easy_setopt(curlPostParticles, CURLOPT_POSTFIELDS, data.c_str());
    res = curl_easy_perform(curlPostParticles);

    if (res != CURLE_OK)
        std::cout << "Error: " << curl_easy_strerror(res) << std::endl;
}

// Récupère les particules du serveur puis mets à jour la physique des particules et démarre la requête post
void curlGetParticlesRequest() {
    CURLcode res;

    res = curl_easy_perform(curlGetParticles);

    if (res != CURLE_OK)
        std::cout << "Error: " << curl_easy_strerror(res) << std::endl;

    parseJsonToParticles();

    updatePhysics(FixedDeltaTime);
    nlohmann::json j = particlesToJson(modifiedParticles, baseIndex);
    curlPostRequest(j.dump());
}

// Récupère le frame actuel du serveur et si le frame a changé lance la requête curlGetParticlesRequest
void curlGetRequest() {
    CURLcode res;
    std::cout << "perform request" << std::endl;
    res = curl_easy_perform(curlGetFrame);
    std::cout << "end request" << std::endl;

    if (res != CURLE_OK)
        std::cout << "Error: " << curl_easy_strerror(res) << std::endl;
    if(changedFrame) {
        changedFrame = false;
        curlGetParticlesRequest();
    }
}

// Cleanup des requêtes
void cleanup() {
    curl_easy_cleanup(curlPostParticles);
    curl_easy_cleanup(curlGetFrame);
    curl_easy_cleanup(curlGetParticles);
    curl_global_cleanup();
}

auto main(int argc, char* argv[]) -> int {

    // Check arguments
    if (argc < 4)
    {
        std::cout << "Usage: " << argv[0] << " <baseIndex> <numParticles> <addressPost> <particlesCountWork>" << std::endl;
        return 1;
    }

    std::cout << argv[1] << " " <<  std::getenv("NB_PARTICULES") << " "<<argv[2] << " " << argv[3] << " " << argv[4] << std::endl;

    // Get arguments
    baseIndex = std::atoi(argv[1]);
    numParticles = std::atoi(std::getenv("NB_PARTICULES"));
    addressPost = std::string(argv[3]);
    // auto particlesCountWork = std::atoi(argv[4]);

    // Init curl
    initializeRequest();

    // Init random
    srand(static_cast<unsigned int>(time(nullptr)));

    // Set exit signals
    signal(SIGINT, signalHandler);

    /* Init */
    modifiedParticles = std::vector<Particle>(numParticles);
    std::mt19937 randomEngine;
    std::uniform_real_distribution<float> randomFloats(0.0F, static_cast<float>(2.0F * M_PI));
    for (auto p : modifiedParticles)
    {
        const float angle1 = randomFloats(randomEngine);
        const float angle2 = randomFloats(randomEngine);
        const float x = SpawnRadius * std::sin(angle1) * std::cos(angle2);
        const float y = SpawnRadius * std::sin(angle1) * std::sin(angle2);
        const float z = SpawnRadius * std::cos(angle1);
        p.position = glm::vec3(x, y, z);
        p.velocity = glm::vec3(0.0F, 0.0F, 0.0F);


        /*particle.position = glm::vec3(
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0F - 1.0F,
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0F - 1.0F,
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0F - 1.0F);*/
    }



//    auto json = particlesToJson(particles, baseIndex);
//    curlPostRequest(addressPost, json.dump());

    /* Loop*/
    //
    //const float FixedDeltaTime = 0.02F;
    float accumulator = 0.0F;
    //
    auto previousTime = std::chrono::high_resolution_clock::now();
    float deltaTime = 0.0F;
    //
    while (!exitMainLoopFlag)
    {
        // GET la frame du serveur et si elle change, appelle les autres fonctions pour mettre à jour les toutes les particules puis mettre à jour la
        // physique des particules et enfin envoyer les particules au serveur
        //curlGetRequest();

//        auto currentTime = std::chrono::high_resolution_clock::now();
//
//        deltaTime = std::chrono::duration<float>(currentTime - previousTime).count();
//
//        accumulator += deltaTime;
//        while (accumulator >= FixedDeltaTime)
//        {
//
//        }
//
//        previousTime = currentTime;
    }

    std::cout << "Exiting..." << std::endl;

    return 0;
}
