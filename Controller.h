#pragma once
#include "Action.h"
#include "Repository.h"
#include <stack>
#include <memory>
#include <string>
#include <vector>

class Filter; // Forward declaration for the Filter interface

/**
 * @class Controller
 * @brief Handles the business logic of the application.
 * * The Controller acts as a bridge between the User Interface and the Repository.
 * It manages CRUD operations, handles data validation, executes undo/redo
 * functionality using the Command Design Pattern, and applies filtering logic.
 */
class Controller {
private:
    Repository& repo; ///< Reference to the repository layer managing data storage.

    // Stacks for Command Pattern
    std::stack<std::unique_ptr<Action>> undoStack; ///< Stack holding executed actions available for undo.
    std::stack<std::unique_ptr<Action>> redoStack; ///< Stack holding undone actions available for redo.
public:
    /**
     * @brief Constructs a Controller object.
     * @param repo A reference to the Repository to be manipulated.
     */
    explicit Controller(Repository& repo);

    /**
     * @brief Reverts the last executed action.
     * * Pops the top action from the undo stack, executes its undo logic,
     * and pushes it onto the redo stack. Throws an error if the stack is empty.
     * @throws std::runtime_error If there are no actions to undo.
     */
    void undo();

    /**
     * @brief Reapplies the last undone action.
     * * Pops the top action from the redo stack, executes its redo logic,
     * and pushes it back onto the undo stack. Throws an error if the stack is empty.
     * @throws std::runtime_error If there are no actions to redo.
     */
    void redo();

    /**
     * @brief Creates and adds a new CraftItem to the store.
     * * Validates the input data and creates an AddAction. The action is executed
     * and saved in the undo stack. The redo stack is cleared.
     * @param id The unique identifier for the new item.
     * @param name The name of the product.
     * @param category The category of the item.
     * @param price The price of the item. Must be >= 0.
     * @param quantity The stock available. Must be >= 0.
     * @throws std::runtime_error If data validation fails (e.g., negative price or empty name).
     */
    void addItem(int id, const std::string& name, Category category, double price, int quantity);

    /**
     * @brief Creates and adds a new CraftItem to the store.
     * * Validates the input data and creates an AddAction. The action is executed
     * and saved in the undo stack. The redo stack is cleared.
     * @param id The unique identifier for the new item.
     * @param name The name of the product.
     * @param category The category of the item.
     * @param price The price of the item. Must be >= 0.
     * @param quantity The stock available. Must be >= 0.
     * @throws std::runtime_error If data validation fails (e.g., negative price or empty name).
     */
    /**
     * @brief Deletes a CraftItem from the store by its ID.
     * * Searches for the item, creates a RemoveAction, executes it,
     * and saves it to the undo stack. The redo stack is cleared.
     * @param id The unique identifier of the item to be removed.
     * @throws std::runtime_error If the item with the specified ID is not found.
     */
    void deleteItem(int id);

    /**
     * @brief Modifies the attributes of an existing CraftItem.
     * * Locates the old state of the item, constructs a new state with the provided
     * arguments, and creates an UpdateAction. The action is executed and saved
     * in the undo stack. The redo stack is cleared.
     * @param id The unique identifier of the item to update.
     * @param newName The updated name.
     * @param newCategory The updated category.
     * @param newPrice The updated price. Must be >= 0.
     * @param newQuantity The updated quantity. Must be >= 0.
     * @throws std::runtime_error If validation fails or the ID does not exist.
     */
    void updateItem(int id, const std::string& newName, Category newCategory, double newPrice, int newQuantity);

    /**
     * @brief Retrieves all items currently stored in the repository.
     * @return A vector of shared pointers to all CraftItems.
     */
    std::vector<std::shared_ptr<CraftItem>> getAllItems() const;

    /**
     * @brief Filters the items in the repository based on specific criteria.
     * * Uses the Specification/Strategy Design Pattern by accepting a polymorphic
     * Filter object that evaluates each item.
     * @param filter A shared pointer to a concrete Filter object (e.g., NameFilter, AndFilter).
     * @return A vector of shared pointers to CraftItems that match the filter criteria.
     */
    std::vector<std::shared_ptr<CraftItem>> filterItems(std::shared_ptr<Filter> filter) const;
};