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
    //std::cout << response << std::endl;

    json j;
    try {
        j = json::parse(response);
    } catch (json::parse_error& e) {
        std::cout << "Error while parsing json : " << e.what() << std::endl;
    }
    //std::cout << "Check initial parse" << std::endl;
    for(const auto& particule : j["particules"]) {
        // parse json string which represent the particle
        //std::cout << "Particule" << particule.get<std::string>() << std::endl;
        json particules = json::parse(particule.get<std::string>());
        //if(particules["index"] == 2)
         //   std::cout << "x : " << particules["position"][0] << std::endl;

        // make a vec3 with the position in the json particle
        res.emplace_back(particules["position"][0], particules["position"][1], particules["position"][2]);
    }
    return res;
}
