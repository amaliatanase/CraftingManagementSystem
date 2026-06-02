#include "Repository.h"
#include "CraftItem.h"
#include <memory>
#include <algorithm>
#include <string>
#include <stdexcept>

void Repository::add(std::shared_ptr<CraftItem> item) {
    if (find(item->getID()) != nullptr)
        throw std::runtime_error("There already is an item with ID = " + std::to_string(item->getID()));
    items.push_back(item);
}

void Repository::remove(int id) {
    //check if the item exists and if it does, delete it
    auto it = findIterator(id);
    if (it == items.end())
        throw std::runtime_error("There is no item with ID = " + std::to_string(id));
    items.erase(it);
}

void Repository::update(std::shared_ptr<CraftItem> newItem) {
    //check if the item exists and if it does, change it
    auto it = findIterator(newItem->getID());
    if (it == items.end())
        throw std::runtime_error("There is no item with ID = " + std::to_string(newItem->getID()));
    *it = newItem;
}

std::shared_ptr<CraftItem> Repository::find(int id) {
    //check if the item exists and if it does, return it
    auto it = findIterator(id);
    if (it != items.end())
        return *it;
    return nullptr;
}

std::vector<std::shared_ptr<CraftItem>> Repository::getAll() const {
    return items;
}

size_t Repository::getSize() const {
    return items.size();
}

std::vector<std::shared_ptr<CraftItem>>::iterator Repository::findIterator(int id) {
    //use a lambda function to go through all items of the vector and give it access to the id
    //place each element in the crtT variable and check if its id is the same with the searched one
    return std::find_if(items.begin(), items.end(),
                        [id](const std::shared_ptr<CraftItem> &crtT) {
                            return crtT->getID() == id;
                        });
}

