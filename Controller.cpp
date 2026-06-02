#include "Controller.h"
#include "Filter.h"
#include <stdexcept>
#include <algorithm>

Controller::Controller(Repository &repo): repo(repo) {}

void Controller::addItem(int id, const std::string& name, Category category, double price, int quantity) {
    if (name.empty()) throw std::runtime_error("Name cannot be empty!");
    if (price < 0) throw std::runtime_error("Price cannot be negative!");
    if (quantity < 0) throw std::runtime_error("Quantity cannot be negative!");
    // create new item
    auto item = std::make_shared<CraftItem>(id, name, category, price, quantity);
    // create action and execute it
    auto action = std::make_unique<AddAction>(item, repo);
    action->execute();
    // put it in the undo stack and empty the redo one, as a new action cancels the history
    undoStack.push(std::move(action));
    while (!redoStack.empty()) {
        redoStack.pop();
    }
}

void Controller::deleteItem(int id) {
    // find the old item (find from repo will throw an error if it does not exist)
    auto item = repo.find(id);
    // create action and execute it
    auto action = std::make_unique<RemoveAction>(item, repo);
    action->execute();
    // keep the action for undo and empty the redo
    undoStack.push(std::move(action));
    while (!redoStack.empty()) {
        redoStack.pop();
    }
}

void Controller::updateItem(int id, const std::string& newName, Category newCategory, double newPrice, int newQuantity) {
    if (newName.empty()) throw std::runtime_error("Name cannot be empty!");
    if (newPrice < 0) throw std::runtime_error("Price cannot be negative!");
    if (newQuantity < 0) throw std::runtime_error("Quantity cannot be negative!"); // Opțional, dar util
    // find the old state of the item
    auto oldItem = repo.find(id);
    if (!oldItem) throw std::runtime_error("Item with the specified ID was not found!");
    // create the new state
    auto newItem = std::make_shared<CraftItem>(id, newName, newCategory, newPrice, newQuantity);
    // create the update action  and execute it
    auto action = std::make_unique<UpdateAction>(oldItem, newItem, repo);
    action->execute();
    // keep the action for undo and empty the redo
    undoStack.push(std::move(action));
    while (!redoStack.empty()) {
        redoStack.pop();
    }
}

std::vector<std::shared_ptr<CraftItem>> Controller::getAllItems() const {
    return repo.getAll();
}

void Controller::undo() {
    if (undoStack.empty()) throw std::runtime_error("No more actions to undo!");
    // take the action from the top of the undo stack
    auto action = std::move(undoStack.top());
    undoStack.pop();
    // call inverse logic
    action->undo();
    // move the action in the redo stack
    redoStack.push(std::move(action));
}

void Controller::redo() {
    if (redoStack.empty()) throw std::runtime_error("No more actions to redo!");
    // take the action from the redo stack
    auto action = std::move(redoStack.top());
    redoStack.pop();
    // redo the action
    action->redo();
    // place it back in the undo stack
    undoStack.push(std::move(action));
}

std::vector<std::shared_ptr<CraftItem>> Controller::filterItems(std::shared_ptr<Filter> filter) const {
    std::vector<std::shared_ptr<CraftItem>> result;
    auto allItems = repo.getAll();
    // iterate through all items from the repository
    for (const auto& item : allItems)
        // if the item meets the criteria of the filter
        if (filter->matches(item)) result.push_back(item);
    return result;
}