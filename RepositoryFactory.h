#pragma once
#include "Repository.h"
#include <string>
#include <memory>

/**
 * @class RepositoryFactory
 * @brief Factory class for creating repository instances.
 * * This class implements the Factory Design Pattern. It centralizes the
 * creation logic for repository objects, allowing the application to easily
 * switch between different storage formats (like CSV or JSON) without changing
 * the core business logic.
 */
class RepositoryFactory {
public:
    /**
     * @brief Creates and returns a concrete Repository instance.
     * * Based on the provided repository type, this method instantiates the
     * appropriate subclass (e.g., RepositoryCSV or RepositoryJSON).
     * @param repoType A string representing the type of repository to create (e.g., "csv", "json").
     * @param filename The name of the file where the repository will store its data.
     * @return A unique pointer to the instantiated Repository.
     * @throws std::invalid_argument If the requested repoType is unknown or unsupported.
     */
    static std::unique_ptr<Repository> create(const std::string& repoType, const std::string& filename);
};