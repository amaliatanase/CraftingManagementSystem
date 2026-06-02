#include "UI.h"
#include "Filter.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QString>
#include <stdexcept>

UI::UI(Controller& controller, QWidget* parent)
    : QWidget(parent), controller(controller) {
    setupUI();
    connectSignals();
    populateList(this->controller.getAllItems());
    this->resize(800, 350);
}

void UI::setupUI() {
    //build the graphic interface
    QHBoxLayout* mainLayout = new QHBoxLayout(this); //create a main layout

    // left: object list
    // main layout will become its parent
    itemListWidget = new QListWidget(this); //create a list for the items
    mainLayout->addWidget(itemListWidget);

    // right side
    QVBoxLayout* rightLayout = new QVBoxLayout(); //create a vertical layout
    QFormLayout* formLayout = new QFormLayout(); //create a layout that aligns text labels on the left

    //initialize the checkboxes for filtering
    nameCheck = new QCheckBox("Filter by Name:", this);
    categoryCheck = new QCheckBox("Filter by Category:", this);
    priceCheck = new QCheckBox("Filter by Max Price:", this);

    //initialize the text boxes
    nameInput = new QLineEdit(this);

    categoryInput = new QComboBox(this); //add predefined options
    categoryInput->addItems({"Material", "Tool", "Blank", "Packaging"});

    priceInput = new QDoubleSpinBox(this);
    priceInput->setMaximum(10000.0); //set a maximum price limit

    qtyInput = new QSpinBox(this);
    qtyInput->setMaximum(5000); //set a maximum quantity limit

    operatorInput = new QComboBox(this);
    operatorInput->addItems({"AND", "OR"});//select an operator for the filtering

    //add a row for each variable and place them all in the right layout
    formLayout->addRow(nameCheck, nameInput);
    formLayout->addRow(categoryCheck, categoryInput);
    formLayout->addRow(priceCheck, priceInput);
    formLayout->addRow("Quantity:", qtyInput);
    formLayout->addRow("Filter logic (AND/OR):", operatorInput);

    rightLayout->addLayout(formLayout);

    //create buttons for the actions and place them all in the right layout
    addButton = new QPushButton("Add Item", this);
    updateButton = new QPushButton("Update Selected", this);
    deleteButton = new QPushButton("Delete Selected", this);
    undoButton = new QPushButton("Undo", this);
    redoButton = new QPushButton("Redo", this);
    filterButton = new QPushButton("Apply Advanced Filtering", this);

    rightLayout->addWidget(addButton);
    rightLayout->addWidget(updateButton);
    rightLayout->addWidget(deleteButton);
    rightLayout->addWidget(undoButton);
    rightLayout->addWidget(redoButton);
    rightLayout->addWidget(filterButton);

    mainLayout->addLayout(rightLayout);
}

void UI::connectSignals() {
    //activate the buttons, specify what will happen when the button is clicked
    connect(addButton, &QPushButton::clicked, this, &UI::handleAdd);
    connect(updateButton, &QPushButton::clicked, this, &UI::handleUpdate);
    connect(deleteButton, &QPushButton::clicked, this, &UI::handleDelete);
    connect(undoButton, &QPushButton::clicked, this, &UI::handleUndo);
    connect(redoButton, &QPushButton::clicked, this, &UI::handleRedo);
    connect(filterButton, &QPushButton::clicked, this, &UI::handleFilter);
    connect(itemListWidget, &QListWidget::itemSelectionChanged, this, &UI::handleSelectionChanged);
}

void UI::populateList(const std::vector<std::shared_ptr<CraftItem>>& items) {
    //every time something changes in the data, the list needs to be renewed
    itemListWidget->clear();
    for (const auto& item : items) {
        //text created piece by piece and creating a line
        QString displayText = QString("ID: %1 | %2 | Cat: %3 | Price: %4 | Qty: %5")
            .arg(item->getID())
            .arg(QString::fromStdString(item->getName()))
            .arg(QString::fromStdString(item->getCategoryAsString()))
            .arg(item->getPrice())
            .arg(item->getQuantity());
        // create a line for the item's list and place the text generated
        QListWidgetItem* listItem = new QListWidgetItem(displayText);
        //the id of each product won't be outputted
        listItem->setData(Qt::UserRole, item->getID());
        //add the line on the list
        itemListWidget->addItem(listItem);
    }
}

void UI::handleAdd() {
    try {
        //compute a new temporary id and initialize the attributes
        int id = controller.getAllItems().size() + 1;
        std::string name = nameInput->text().toStdString();
        Category cat = CraftItem::stringToCategory(categoryInput->currentText().toStdString());
        double price = priceInput->value();
        int qty = qtyInput->value();
        //add the item and place it in the list
        controller.addItem(id, name, cat, price, qty);
        populateList(controller.getAllItems());
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void UI::handleDelete() {
    try {
        //search for the selected line
        QListWidgetItem* selectedItem = itemListWidget->currentItem();
        if (!selectedItem) throw std::runtime_error("No item selected for deletion.");
        //read the id of the selected line
        int id = selectedItem->data(Qt::UserRole).toInt();
        //delete the item and update the list
        controller.deleteItem(id);
        populateList(controller.getAllItems());
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void UI::handleUpdate() {
    try {
        //search for the selected line
        QListWidgetItem* selectedItem = itemListWidget->currentItem();
        if (!selectedItem) throw std::runtime_error("No item selected for update.");
        //read the id and the attributes of the selected item
        int id = selectedItem->data(Qt::UserRole).toInt();
        std::string name = nameInput->text().toStdString();
        Category cat = CraftItem::stringToCategory(categoryInput->currentText().toStdString());
        double price = priceInput->value();
        int qty = qtyInput->value();
        //update the item and  the list
        controller.updateItem(id, name, cat, price, qty);
        populateList(controller.getAllItems());
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void UI::handleUndo() {
    try {
        //delegate the responsibility to the controller and update the list
        controller.undo();
        populateList(controller.getAllItems());
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Undo", e.what());
    }
}

void UI::handleRedo() {
    try {
        //delegate the responsibility to the controller and update the list
        controller.redo();
        populateList(controller.getAllItems());
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Redo", e.what());
    }
}

void UI::handleFilter() {
    // create a vector to keep track of the active filters
    std::vector<std::shared_ptr<Filter>> activeFilters;

    // verify the name check
    if (nameCheck->isChecked()) {
        std::string nameQuery = nameInput->text().toStdString();
        if (!nameQuery.empty()) {
            activeFilters.push_back(std::make_shared<NameFilter>(nameQuery));
        }
    }

    // verify the category check
    if (categoryCheck->isChecked()) {
        Category cat = CraftItem::stringToCategory(categoryInput->currentText().toStdString());
        activeFilters.push_back(std::make_shared<CategoryFilter>(cat));
    }

    // verify the price check
    if (priceCheck->isChecked()) {
        double maxPrice = priceInput->value();
        activeFilters.push_back(std::make_shared<MaxPriceFilter>(maxPrice));
    }

    // if the user has not checked anything, output all the items
    if (activeFilters.empty()) {
        populateList(controller.getAllItems());
        QMessageBox::information(this, "Filter", "No filters selected. Showing all items.");
        return;
    }

    // start constructing the final polymorphic starting from the first active filter found
    std::shared_ptr<Filter> finalFilter = activeFilters[0];
    std::string logicOp = operatorInput->currentText().toStdString();

    // if more filters are checked, combine them successively
    for (size_t i = 1; i < activeFilters.size(); ++i) {
        if (logicOp == "AND") {
            finalFilter = std::make_shared<AndFilter>(finalFilter, activeFilters[i]);
        } else {
            finalFilter = std::make_shared<OrFilter>(finalFilter, activeFilters[i]);
        }
    }

    // delegate the responsibility to the controller and update the list
    auto filteredItems = controller.filterItems(finalFilter);
    populateList(filteredItems);
}

void UI::handleSelectionChanged() {
    //when selecting an item, the boxes will automatically be filled with that item's info
    //search for the selected line
    QListWidgetItem* selectedItem = itemListWidget->currentItem();
    if (!selectedItem) return;
    //read the id of the selected line
    int id = selectedItem->data(Qt::UserRole).toInt();

    // search for the item in controller using the id
    for (const auto& item : controller.getAllItems()) {
        if (item->getID() == id) {
            // fill the text boxes with the item's info
            nameInput->setText(QString::fromStdString(item->getName()));
            int index = categoryInput->findText(QString::fromStdString(item->getCategoryAsString()));
            if (index != -1) categoryInput->setCurrentIndex(index);
            priceInput->setValue(item->getPrice());
            qtyInput->setValue(item->getQuantity());
            break; // when the boxes have been filled, stop the for loop
        }
    }
}

UI::~UI() {
    qDebug() << "------------------------------------------";
    qDebug() << "Memory released successfully!";
    qDebug() << "Program closed successfully, nu memory leaks!";
    qDebug() << "------------------------------------------";
}