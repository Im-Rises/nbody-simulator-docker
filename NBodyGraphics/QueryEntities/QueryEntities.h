#ifndef NBODYGRAPHICS_QUERYENTITIES_H
#define NBODYGRAPHICS_QUERYENTITIES_H

#include <curl/curl.h>
#include <vector>
#include <glm/glm.hpp>
#include <string>

// curl -X POST http://localhost:8080/api -d '{"particules":[{"index": 1, "x": 1}, {"index": 2, "x": 2}
// ]}' -H "Content-Type: application/json"


class QueryEntities {
    typedef void(*Callback)(std::vector<glm::vec3>);

    Callback callbackfct;
    // Use to initialize and terminate cURLpp
    CURL* curl;
    CURLcode res;

    std::string response;

    size_t GetAllParticlesCallback(void* contents, size_t size, size_t nmemb, std::string* response);

    void Parse() const;
public:
    QueryEntities();

    QueryEntities(const QueryEntities&) = delete;
    auto operator=(const QueryEntities&) -> QueryEntities& = delete;
    QueryEntities(QueryEntities&&) = delete;
    auto operator=(QueryEntities&&) -> QueryEntities& = delete;

    ~QueryEntities() = default;

    inline void SetCallback(Callback callback) { callbackfct = callback; }
    void AskGetAllParticles();
};



#endif // NBODYGRAPHICS_QUERYENTITIES_H
