#pragma once
#include <memory>
#include "Repository.h"
#include "CraftItem.h"

/**
 * @class Action
 * @brief Abstract base class (Interface) representing a generic executable command.
 * * This class is the core of the Command Design Pattern implementation.
 * It encapsulates operations as objects, allowing the Controller to maintain a stack
 * of generic pointers for polymorphic execution, undo, and redo functionalities.
 */
//Command Pattern: convert an action into an object
//The Controller will keep a stack with pointers to the action objects
//using polymorphism the stack will keep multiple types of actions
class Action {
    //abstract class = interface
public:
    /**
     * @brief Executes the encapsulated action.
     */
    virtual void execute() = 0;

    /**
     * @brief Reverts the effects of the executed action in the repository.
     */
    virtual void undo() = 0;

    /**
     * @brief Reapplies the action after it has been undone.
     */
    virtual void redo() = 0;

    /**
     * @brief Virtual destructor ensures safe polymorphic deletion of derived action objects.
     */
    virtual ~Action() = default;
};

/**
 * @class AddAction
 * @brief Encapsulates the logic for adding a new CraftItem to the repository.
 */
class AddAction : public Action {
private:
    std::shared_ptr<CraftItem> item; ///< The craft item to be added.
    Repository &repo;                ///< Reference to the repository where the item will be stored.

public:
    /**
     * @brief Constructs an AddAction object.
     * @param item A shared pointer to the CraftItem being added.
     * @param repo A reference to the Repository handling the data storage.
     */
    AddAction(std::shared_ptr<CraftItem> item, Repository &repo);

    void execute() override;
    void undo() override;
    void redo() override;
};

/**
 * @class RemoveAction
 * @brief Encapsulates the logic for removing an existing CraftItem from the repository.
 */
class RemoveAction : public Action {
private:
    std::shared_ptr<CraftItem> item; ///< The craft item to be removed.
    Repository &repo;                ///< Reference to the repository holding the item.

public:
    /**
     * @brief Constructs a RemoveAction object.
     * @param item A shared pointer to the CraftItem being targeted for deletion.
     * @param repo A reference to the Repository from which the item will be removed.
     */
    RemoveAction(std::shared_ptr<CraftItem> item, Repository &repo);

    void execute() override;
    void undo() override;
    void redo() override;
};

/**
 * @class UpdateAction
 * @brief Encapsulates the logic for modifying an existing CraftItem in the repository.
 * * Stores both the previous state and the new state of the item to guarantee
 * accurate undo and redo operations.
 */
class UpdateAction : public Action {
private:
    std::shared_ptr<CraftItem> oldItem; ///< The state of the item before the update.
    std::shared_ptr<CraftItem> newItem; ///< The state of the item after the update.
    Repository &repo;                   ///< Reference to the repository where the update occurs.

public:
    /**
     * @brief Constructs an UpdateAction object.
     * @param oldItem A shared pointer containing the original attributes of the item.
     * @param newItem A shared pointer containing the modified attributes of the item.
     * @param repo A reference to the Repository executing the update.
     */
    UpdateAction(std::shared_ptr<CraftItem> oldItem, std::shared_ptr<CraftItem> newItem, Repository &repo);

    void execute() override;
    void undo() override;
    void redo() override;
};