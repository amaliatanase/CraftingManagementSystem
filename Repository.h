#pragma once
#include <vector>
#include <memory>
#include "CraftItem.h"

/**
 * @class Repository
 * @brief Base class for managing the storage and retrieval of CraftItem objects.
 * * This class acts as the lowest layer in the architecture, providing an in-memory
 * data structure to manage items. It uses virtual methods to allow derived classes
 * (like CSV or JSON repositories) to override behaviors and implement persistent storage.
 */
class Repository {
protected:
    /**
     * @brief Internal storage for the craft items.
     * * Uses shared pointers to prevent memory leaks and to safely maintain references
     * to items (even deleted ones) for the Undo/Redo command history. It is protected
     * so that derived file-based repositories can easily access and serialize the data.
     */
    // using shared pointers to avoid memory leaks and
    // to have acces at deleted items for the undo action
    // protected so the derived classes can acces them
    std::vector<std::shared_ptr<CraftItem>> items;
public:
    /**
     * @brief Default constructor.
     */
    Repository() = default;

    /**
     * @brief Virtual destructor to ensure safe polymorphic deletion of derived repositories.
     */
    virtual ~Repository() = default;

    /**
     * @brief Adds a new item to the repository.
     * @param item A shared pointer to the CraftItem to be added.
     * @throws std::runtime_error If an item with the same ID already exists.
     */
    virtual void add(std::shared_ptr<CraftItem> item);

    /**
     * @brief Removes an item from the repository based on its ID.
     * @param id The unique identifier of the item to remove.
     * @throws std::runtime_error If the item with the specified ID is not found.
     */
    virtual void remove(int id);

    /**
     * @brief Updates an existing item in the repository.
     * @param newItem A shared pointer containing the updated state of the CraftItem.
     * The ID inside the item is used to find the old object.
     * @throws std::runtime_error If the item to be updated is not found.
     */
    virtual void update(std::shared_ptr<CraftItem> newItem);

    /**
     * @brief Searches for an item in the repository by its ID.
     * @param id The unique identifier of the item to find.
     * @return A shared pointer to the found item, or nullptr if not found.
     */
    virtual std::shared_ptr<CraftItem> find(int id);

    /**
     * @brief Retrieves all items currently stored in the repository.
     * @return A vector containing shared pointers to all craft items.
     */
    virtual std::vector<std::shared_ptr<CraftItem>> getAll() const;

    /**
     * @brief Returns the total number of items in the repository.
     * @return The count of items.
     */
    virtual size_t getSize() const;

private:
    /**
     * @brief Helper function to find the memory location of an item in the vector.
     * @param id The unique identifier of the item.
     * @return An iterator pointing to the item in the vector, or items.end() if not found.
     */
    // helper function that returns the position of an item in the items vector by a given id
    std::vector<std::shared_ptr<CraftItem>>::iterator findIterator(int id);
};
