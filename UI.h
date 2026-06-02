#pragma once
#include "Controller.h"
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QCheckBox>

/**
 * @class UI
 * @brief The main Graphical User Interface of the application.
 * * Inherits from QWidget. It provides a desktop interface using Qt Widgets
 * for users to interact with the Handmade Craft Store inventory.
 * It delegates all business logic and data manipulation to the Controller layer.
 */
class UI: public QWidget {
    Q_OBJECT ///< Macro required by Qt for the Signals and Slots mechanism.
private:
    //ui will send to the controller the commands inputted by the user
    Controller& controller; ///< Reference to the application's business logic controller.

    // visual components for output and input
    //vertical widget where the items will be displayed
    QListWidget* itemListWidget;  ///< Vertical list widget displaying the inventory items.
    //simple text box where the user can type the name of the item
    QLineEdit* nameInput;         ///< Text box for inputting the item's name.
    //a dropdown list where the user can select the category
    QComboBox* categoryInput;     ///< Dropdown list for selecting the item's category.
    //a numeric box with arrows to set the price for floats
    QDoubleSpinBox* priceInput;   ///< Numeric box with arrows for inputting the price (floating point).
    //a numeric box with arrows for integers
    QSpinBox* qtyInput;           ///< Numeric box with arrows for inputting the quantity (integers).

    // Buttons for actions
    QPushButton* addButton;       ///< Button to trigger the add item operation.
    QPushButton* updateButton;    ///< Button to trigger the update item operation.
    QPushButton* deleteButton;    ///< Button to trigger the delete item operation.
    QPushButton* undoButton;      ///< Button to undo the last action.
    QPushButton* redoButton;      ///< Button to redo the last undone action.
    QPushButton* filterButton;    ///< Button to apply the selected filters.

    QComboBox* operatorInput;     ///< Dropdown to select the logical operator (AND / OR) for filtering.
    QCheckBox* nameCheck;         ///< Checkbox to enable filtering by name.
    QCheckBox* categoryCheck;     ///< Checkbox to enable filtering by category.
    QCheckBox* priceCheck;        ///< Checkbox to enable filtering by maximum price.

    // intern methods for building the interface
    /**
     * @brief Initializes and arranges all visual widgets on the screen.
     * Uses Qt layout managers (QHBoxLayout, QVBoxLayout, QFormLayout) to build the interface.
     */
    void setupUI();

    /**
     * @brief Connects the Qt signals (e.g., button clicks) to their respective slots (functions).
     */
    void connectSignals();

    /**
     * @brief Clears and repopulates the visual list widget with the provided items.
     * @param items A vector of shared pointers to CraftItem objects to be displayed.
     */
    void populateList(const std::vector<std::shared_ptr<CraftItem>>& items);
private slots:
    // functions that will be called when clicking the buttons
    /**
     * @brief Slot triggered when the add button is clicked.
     * Reads input fields, validates data, and delegates the add action to the Controller.
     */
    void handleAdd();

    /**
     * @brief Slot triggered when the update button is clicked.
     * Reads input fields and updates the currently selected item in the list.
     */
    void handleUpdate();

    /**
     * @brief Slot triggered when the delete button is clicked.
     * Deletes the currently selected item from the list.
     */
    void handleDelete();

    /**
     * @brief Slot triggered when the undo button is clicked.
     */
    void handleUndo();

    /**
     * @brief Slot triggered when the redo button is clicked.
     */
    void handleRedo();

    /**
     * @brief Slot triggered when the filter button is clicked.
     * Evaluates active checkboxes, constructs a composite filter, and updates the display.
     */
    void handleFilter();

    /**
     * @brief Slot triggered when a different item is selected in the list widget.
     * Automatically populates the input fields with the data of the selected item.
     */
    void handleSelectionChanged();
public:
    // the constructor gets a reference to the controller and a widget parent optionally
    // explicit is used to prevent implicit data type conversions
    /**
     * @brief Constructs the UI object.
     * @param controller A reference to the Controller handling business logic.
     * @param parent An optional parent widget (nullptr for the main window).
     */
    explicit UI(Controller& controller, QWidget* parent = nullptr);

    /**
     * @brief Destructor for the UI class.
     * Memory management of widgets is automatically handled by the Qt parent-child system.
     */
    ~UI();
};


