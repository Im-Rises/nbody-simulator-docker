#ifndef NBODYGRAPHICS_QUERYENTITIES_H
#define NBODYGRAPHICS_QUERYENTITIES_H

//#include "curlpp/include/curlpp/cURLpp.hpp"
#include <vector>
#include <glm/glm.hpp>
//#include <curlpp/include/curlpp/Options.hpp>
//#include <curlpp/include/curlpp/Easy.hpp>

class QueryEntities {
    // Use to initialize and terminate cURLpp
//    curlpp::Cleanup myCleanup;
//
//    cURLpp::Easy easyHandle;

//    std::ostringstream os;

public:
    QueryEntities();

    QueryEntities(const QueryEntities&) = delete;
    auto operator=(const QueryEntities&) -> QueryEntities& = delete;
    QueryEntities(QueryEntities&&) = delete;
    auto operator=(QueryEntities&&) -> QueryEntities& = delete;

    ~QueryEntities() = default;

    std::vector<glm::vec3> GetAllParticles();
};



#endif // NBODYGRAPHICS_QUERYENTITIES_H
