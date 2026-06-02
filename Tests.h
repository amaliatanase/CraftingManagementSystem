#pragma once

/**
 * @class Tests
 * @brief A utility class containing automated tests for the application.
 * * This class groups together all the unit tests required to validate the core
 * functionality of the Repository and Controller layers. It uses standard C++
 * assertions to ensure that CRUD operations, undo/redo mechanisms, and filters
 * work correctly before the graphical interface is launched.
 */
class Tests {
public:
    /**
     * @brief Executes all the automated test suites sequentially.
     * * If any assertion fails during execution, the program will terminate immediately,
     * pointing to the exact line where the bug occurred. If all tests pass, it prints
     * a success message to the console.
     */
    static void runAllTests();

private:
    /**
     * @brief Tests the base Repository functionalities.
     * Ensures that items can be added, found by ID, and removed correctly.
     */
    static void testRepository();

    /**
     * @brief Tests the Controller's CRUD operations.
     * Verifies that business logic and input validations are applied correctly
     * when adding, updating, or deleting items.
     */
    static void testControllerCRUD();

    /**
     * @brief Tests the Command Design Pattern implementation.
     * Verifies that the Undo and Redo stacks behave correctly and restore the
     * repository to its accurate past or future states.
     */
    static void testUndoRedo();

    /**
     * @brief Tests the Specification and Composite Design Patterns.
     * Evaluates whether individual filters (Category, MaxPrice) and composite
     * logic gates (AndFilter) correctly isolate the desired items.
     */
    static void testFiltering();
};