#ifndef NBODYGRAPHICS_QUERYENTITIES_H
#define NBODYGRAPHICS_QUERYENTITIES_H

#include <curl/curl.h>
#include <vector>
#include <glm/glm.hpp>
#include <string>
#include <functional>
#include "QueryCallbackParameter.h"
// curl -X POST http://localhost:8080/api -d '{"particules":[{"index": 1, "x": 1}, {"index": 2, "x": 2}
// ]}' -H "Content-Type: application/json"


class QueryEntities {

    // Use to initialize and terminate cURLpp
    CURL* curl;
    CURLcode res;

    QueryCallbackParameter callbackParameter;


public:
    QueryEntities();

    QueryEntities(const QueryEntities&) = delete;
    auto operator=(const QueryEntities&) -> QueryEntities& = delete;
    QueryEntities(QueryEntities&&) = delete;
    auto operator=(QueryEntities&&) -> QueryEntities& = delete;

    ~QueryEntities();

    inline void SetCallback(const QueryCallbackParameter::CallbackQuery& callback) { callbackParameter.SetCallback(callback); }
    bool AskGetAllParticles();

    static bool isQuerying;
};



#endif // NBODYGRAPHICS_QUERYENTITIES_H
