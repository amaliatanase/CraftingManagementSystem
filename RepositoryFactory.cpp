#include "RepositoryFactory.h"
#include "RepositoryFile.h"
#include <string>
#include <memory>
#include <stdexcept>

std::unique_ptr<Repository> RepositoryFactory::create(const std::string &repoType, const std::string &filename) {
    // will create a repository based on the inputted type
    if (repoType=="csv") {
        return std::make_unique<RepositoryFileCSV>(filename);
    }
    else if (repoType=="json") {
        return std::make_unique<RepositoryFileJSON>(filename);
    }
    else if (repoType == "memory") {
        return std::make_unique<Repository>();
    }else{
        throw std::invalid_argument("Unknown repository type: " + repoType);
    }
}