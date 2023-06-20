//
// Created by axelc on 15/06/2023.
//

#include "QueryCallbackParameter.h"
#include "nlohmann/json.hpp"
#include <iostream>

using json = nlohmann::json;


QueryCallbackParameter::QueryCallbackParameter(int nbParticles) {
    bufferVector.resize(nbParticles);
}



// Used to parse the json string to retrieve the position of the particles
bool QueryCallbackParameter::Parse() {
    bool wasUpdated = false;
    json j;

    j = json::parse(response);

    wasUpdated = j["wasUpdated"];
    if (!wasUpdated)
    {
        return wasUpdated;
    }

    for (const auto& particule : j["particules"])
    {
        // parse json string which represent the particle
        json p = json::parse(particule.get<std::string>());
//        if(p["index"] > bufferVector.size()) {
//            std::cout << "index > size buffer vector : " << p["index"] << std::endl;
//            continue;
//        }
        // make a vec3 with the position in the json particle
        bufferVector[p["index"]] = glm::vec3(p["position"][0], p["position"][1], p["position"][2]);
    }
    return wasUpdated;
}
