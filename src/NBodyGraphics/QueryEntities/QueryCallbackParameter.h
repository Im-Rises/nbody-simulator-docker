#ifndef NBODYGRAPHICS_QUERYCALLBACKPARAMETER_H
#define NBODYGRAPHICS_QUERYCALLBACKPARAMETER_H


#include <vector>
#include <glm/glm.hpp>
#include <string>
#include <functional>

class QueryCallbackParameter {

public:
    QueryCallbackParameter() = delete;
    explicit QueryCallbackParameter(int nbParticles);

    typedef std::function<void(std::vector<glm::vec3>)> CallbackQuery;

    void SetCallback(const CallbackQuery& callback) { CallbackFct = callback; }

    CallbackQuery CallbackFct;

    std::string response;
    std::vector<glm::vec3> bufferVector;

    bool Parse();
};



#endif // NBODYGRAPHICS_QUERYCALLBACKPARAMETER_H
