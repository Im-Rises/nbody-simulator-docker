//
// Created by axelc on 15/06/2023.
//

#include "QueryCallbackParameter.h"
#include "nlohmann/json.hpp"
#include <iostream>

using json = nlohmann::json;

// Used to parse the json string to retrieve the position of the particles
std::vector<glm::vec3> QueryCallbackParameter::Parse() {
    std::vector<glm::vec3> res;

    // parse json string
    json j = json::parse(response);
    for(const auto& particule : j["particules"]) {
        // parse json string which represent the particle
        json particules = json::parse(particule.get<std::string>());

        // make a vec3 with the position in the json particle
        res.emplace_back(particules["position"][0], particules["position"][1], particules["position"][2]);
    }

    return res;
}
