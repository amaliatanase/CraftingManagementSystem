#include "Action.h"
#include <memory>

AddAction::AddAction(std::shared_ptr<CraftItem> item, Repository &repo)
    : item(item), repo(repo) {}

void AddAction::execute() {
    repo.add(item);
}

void AddAction::undo() {
    repo.remove(item->getID());
}

void AddAction::redo() {
    execute();
}

RemoveAction::RemoveAction(std::shared_ptr<CraftItem> item, Repository &repo)
    : item(item), repo(repo) {}

void RemoveAction::execute() {
    repo.remove(item->getID());
}

void RemoveAction::undo() {
    repo.add(item);
}

void RemoveAction::redo() {
    execute();
}

UpdateAction::UpdateAction(std::shared_ptr<CraftItem> oldItem, std::shared_ptr<CraftItem> newItem, Repository &repo)
    : oldItem(oldItem), newItem(newItem), repo(repo) {}

void UpdateAction::execute() {
    repo.update(newItem);
}

void UpdateAction::undo() {
    repo.update(oldItem);
}

void UpdateAction::redo() {
    execute();
}
