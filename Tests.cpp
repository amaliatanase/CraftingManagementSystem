#include "Tests.h"
#include "Repository.h"
#include "Controller.h"
#include "Filter.h"
#include "CraftItem.h"
#include <cassert>
#include <iostream>

void Tests::runAllTests() {
    std::cout << "Starting automated tests:\n";
    testRepository();
    testControllerCRUD();
    testUndoRedo();
    testFiltering();
    std::cout << "All tests executed successfully!\n\n";
}

void Tests::testRepository() {
    Repository repo;
    // Test Add: create an item and add it in the repo
    auto item = std::make_shared<CraftItem>(1, "Test Item", Category::Tool, 10.0, 5);
    repo.add(item);
    assert(repo.getAll().size() == 1);
    // Test Find: search the added item and one that does not exist
    assert(repo.find(1) != nullptr);
    assert(repo.find(99) == nullptr);
    // Test Delete: delete the added item
    repo.remove(1);
    assert(repo.getAll().empty());
    std::cout << "Repository tests passed.\n";
}

void Tests::testControllerCRUD() {
    Repository repo;
    Controller ctrl(repo);
    // Test AddItem
    ctrl.addItem(1, "Vase", Category::Blank, 50.0, 10);
    assert(ctrl.getAllItems().size() == 1);
    assert(ctrl.getAllItems()[0]->getName() == "Vase");
    // Test UpdateItem
    ctrl.updateItem(1, "Ceramic vase", Category::Blank, 60.0, 15);
    assert(ctrl.getAllItems()[0]->getName() == "Ceramic vase");
    assert(ctrl.getAllItems()[0]->getPrice() == 60.0);
    // Test DeleteItem
    ctrl.deleteItem(1);
    assert(ctrl.getAllItems().empty());
    std::cout << "Controller CRUD tests passed.\n";
}

void Tests::testUndoRedo() {
    Repository repo;
    Controller ctrl(repo);
    // Create an action
    ctrl.addItem(1, "Brush", Category::Tool, 15.0, 2);
    assert(ctrl.getAllItems().size() == 1);
    // Test Undo
    ctrl.undo();
    assert(ctrl.getAllItems().empty()); // item disappeared
    // Test Redo
    ctrl.redo();
    assert(ctrl.getAllItems().size() == 1); // item got back
    assert(ctrl.getAllItems()[0]->getName() == "Brush");
    std::cout << "Undo/Redo tests passed.\n";
}

void Tests::testFiltering() {
    Repository repo;
    Controller ctrl(repo);
    // add some items to filter
    ctrl.addItem(1, "Small vase", Category::Blank, 30.0, 5);
    ctrl.addItem(2, "Big vase", Category::Blank, 70.0, 5);
    ctrl.addItem(3, "Brush", Category::Tool, 15.0, 10);
    // Test Category Filter
    auto catFilter = std::make_shared<CategoryFilter>(Category::Blank);
    auto blankItems = ctrl.filterItems(catFilter);
    assert(blankItems.size() == 2);
    // Test Max Price Filter
    auto priceFilter = std::make_shared<MaxPriceFilter>(50.0);
    auto cheapItems = ctrl.filterItems(priceFilter);
    assert(cheapItems.size() == 2); // small vase and brush
    // Test AND Filter
    auto andFilter = std::make_shared<AndFilter>(catFilter, priceFilter);
    auto combinedItems = ctrl.filterItems(andFilter);
    assert(combinedItems.size() == 1);
    assert(combinedItems[0]->getName() == "Small vase");
    std::cout << "Filtering tests passed.\n";
}
