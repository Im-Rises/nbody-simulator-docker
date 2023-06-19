//
// Created by axelc on 15/06/2023.
//

#ifndef NBODYGRAPHICS_QUERYCALLBACKPARAMETER_H
#define NBODYGRAPHICS_QUERYCALLBACKPARAMETER_H


#include <vector>
#include <glm/glm.hpp>
#include <string>
#include <functional>

class QueryCallbackParameter {

public:
    typedef std::function<void(std::vector<glm::vec3>)> CallbackQuery;

    void SetCallback(const CallbackQuery& callback) { CallbackFct = callback; }

    CallbackQuery CallbackFct;

    std::string response;

    std::vector<glm::vec3> Parse(bool& wasUpdated);

};



#endif // NBODYGRAPHICS_QUERYCALLBACKPARAMETER_H
