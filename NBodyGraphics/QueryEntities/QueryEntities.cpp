//
// Created by axelc on 13/06/2023.
//

#include "QueryEntities.h"
#include <string>
#include <array>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

QueryEntities::QueryEntities() : curl(nullptr) {
     curl_global_init(CURL_GLOBAL_ALL);
     curl = curl_easy_init();

     if(!curl) {
         std::cout << "Error initializing curl" << std::endl;
     }

     curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8080/all/present");

     // Configuration de la fonction de rappel pour stocker la réponse
     curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,
         [this](void* contents, size_t size, size_t nmemb, std::string* response)
         {
            return GetAllParticlesCallback(contents, size, nmemb, response);}
         );
     curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
}


auto QueryEntities::GetAllParticlesCallback(void* contents, size_t size, size_t nmemb, std::string* response) -> size_t {
     size_t total_size = size * nmemb;
     response->append(static_cast<char*>(contents), total_size);
     Parse();
     return total_size;
}


void QueryEntities::AskGetAllParticles() {

    res = curl_easy_perform(curl);

    if(res != CURLE_OK) {
         std::cout << "Error while performing curl request : " << curl_easy_strerror(res) << std::endl;
    }
}
void QueryEntities::Parse() const {
    std::cout << "Response : " << response << std::endl;

    std::vector<glm::vec3> res;
    json j = json::parse(response);

    for(auto it = j[1].begin(); it != j.end(); ++it) {
        std::cout << "x : " << it.value()["x"] << std::endl;
    }

}
