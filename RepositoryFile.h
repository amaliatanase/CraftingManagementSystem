#pragma once
#include <string>
#include "Repository.h"

/**
 * @class RepositoryFile
 * @brief Abstract base class for file-based repositories.
 * * Inherits from the base Repository class and adds file management capabilities.
 * It forces derived classes to implement specific loading and saving mechanisms
 * while overriding CRUD operations to automatically save changes to the disk.
 */
class RepositoryFile : public Repository {
protected:
    std::string filename; ///< The name or path of the file used for persistent storage.

public:
    /**
     * @brief Constructs a RepositoryFile object.
     * @param file The path/name of the file to manage.
     */
    explicit RepositoryFile(const std::string& file);

    /**
     * @brief Virtual destructor.
     */
    virtual ~RepositoryFile() = default;

    /**
     * @brief Pure virtual method to load data from the file into memory.
     * * Must be implemented by concrete classes according to their specific file format.
     */
    virtual void loadFromFile() = 0;

    /**
     * @brief Pure virtual method to save data from memory to the file.
     * * Must be implemented by concrete classes according to their specific file format.
     */
    virtual void saveToFile() = 0;

    /**
     * @brief Adds an item to the repository and saves the updated list to the file.
     * @param item A shared pointer to the CraftItem to add.
     */
    void add(std::shared_ptr<CraftItem> item) override;

    /**
     * @brief Removes an item from the repository by ID and saves the updated list to the file.
     * @param id The ID of the item to remove.
     */
    void remove(int id) override;

    /**
     * @brief Updates an item in the repository and saves the updated list to the file.
     * @param newItem A shared pointer to the new state of the item.
     */
    void update(std::shared_ptr<CraftItem> newItem) override;
};

/**
 * @class RepositoryFileCSV
 * @brief Concrete repository class that manages data in a Comma-Separated Values (CSV) format.
 */
class RepositoryFileCSV : public RepositoryFile {
public:
    /**
     * @brief Constructs a RepositoryFileCSV object and loads existing data from the file.
     * @param file The path/name of the CSV file.
     */
    explicit RepositoryFileCSV(const std::string& file);

    /**
     * @brief Loads craft items from the CSV file into the repository memory.
     */
    void loadFromFile() override;

    /**
     * @brief Saves the current memory state of the repository into the CSV file.
     */
    void saveToFile() override;
};

/**
 * @class RepositoryFileJSON
 * @brief Concrete repository class that manages data in JSON format.
 * * Uses the Qt JSON library (QJsonDocument, QJsonObject, QJsonArray) for
 * parsing and serialization.
 */
class RepositoryFileJSON : public RepositoryFile {
public:
    /**
     * @brief Constructs a RepositoryFileJSON object and loads existing data from the file.
     * @param file The path/name of the JSON file.
     */
    explicit RepositoryFileJSON(const std::string& file);

    /**
     * @brief Loads craft items from the JSON file into the repository memory.
     */
    void loadFromFile() override;

    /**
     * @brief Saves the current memory state of the repository into the JSON file.
     */
    void saveToFile() override;
};