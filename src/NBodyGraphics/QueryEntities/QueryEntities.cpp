#include "QueryEntities.h"
#include <string>
#include <array>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

bool QueryEntities::isQuerying = false;

// Callback function used to treat the response
size_t static CallbackRequest(char* ptr, size_t size, size_t nmemb, void* userdata) {
    auto* callbackParameter = static_cast<QueryCallbackParameter*>(userdata);
    if (callbackParameter->response.empty())
    {
        callbackParameter->response = ptr;
    }
    else
    {
        callbackParameter->response.append(ptr);
    }

    // Call the callback function with the response parsed
    return size * nmemb;
}


// Ask the server to get all the particles
bool QueryEntities::AskGetAllParticles() {

    if (!curl)
    {
        std::cout << "Error while performing curl request : " << curl_easy_strerror(res) << std::endl;
    }
    callbackParameter->response.clear();
    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        std::cout << "Error while performing curl request : " << curl_easy_strerror(res) << std::endl;
    }


    bool wasUpdated = callbackParameter->Parse();

    if (wasUpdated)
    {
        callbackParameter->CallbackFct(callbackParameter->bufferVector);
    }
    return wasUpdated;
}

QueryEntities::~QueryEntities() {
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    callbackParameter->response.clear();
    delete callbackParameter;
}

QueryEntities::QueryEntities(int nbParticles) : curl(nullptr), callbackParameter(new QueryCallbackParameter(nbParticles)) {
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (!curl)
    {
        std::cout << "Error initializing curl" << std::endl;
    }
    isQuerying = false;

    curl_easy_setopt(curl, CURLOPT_URL, "http://api:9000/all/present");
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);

    // Configuration de la fonction de rappel pour stocker la réponse
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, callbackParameter);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CallbackRequest);
}
