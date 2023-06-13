//
// Created by axelc on 13/06/2023.
//

#include "QueryEntities.h"
#include <string>
#include <array>
QueryEntities::QueryEntities() {
    // easyHandle.setOpt(cURLpp::Options::Url("http://localhost:8080/all/"));

}


std::vector<glm::vec3> QueryEntities::GetAllParticles() {

//    try {
//        easyHandle.perform();
//
//        os << easyHandle;
//
//        std::cout << os.str() << std::endl;
//    }
//    catch (curlpp::RuntimeError& e) {
//        std::cout << "Runtime Error : " << e.what() << std::endl;
//    }
//    catch (curlpp::LogicError& e) {
//        std::cout << "Logic Error : " << e.what() << std::endl;
//    }
//
//    // parse json string to vec3 array
//    std::string json = os.str();
//    std::vector<glm::vec3> vec3Array;
//
//    for(auto it= json["particules"].iterator(); it != json[1].end(); ++it) {
//        glm::vec3 vec3 = glm::vec3(it["x"], it["y"], it["z"]);
//
//    }
//

    // return array
    return std::vector<glm::vec3>();
}