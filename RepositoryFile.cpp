#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include "RepositoryFile.h"
#include "CraftItem.h"
#include <fstream>
#include <sstream>

RepositoryFile::RepositoryFile(const std::string &file): filename(file) {}

void RepositoryFile::add(std::shared_ptr<CraftItem> item) {
    //calls the classic repo function and saves the result to the file
    Repository::add(item);
    saveToFile();
}

void RepositoryFile::remove(int id) {
    //calls the classic repo function and saves the result to the file
    Repository::remove(id);
    saveToFile();
}

void RepositoryFile::update(std::shared_ptr<CraftItem> newItem) {
    //calls the classic repo function and saves the result to the file
    Repository::update(newItem);
    saveToFile();
}

RepositoryFileCSV::RepositoryFileCSV(const std::string& file) : RepositoryFile(file) {
    loadFromFile();
}

void RepositoryFileCSV::loadFromFile() {
    std::ifstream file(filename);
    if (!file.is_open()) return;
    std::string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        //place in a line a whole line wrote from the file, then tokenize it
        std::stringstream ss(line);
        std::string idStr, name, categoryStr, priceStr, qtyStr;
        //get each attribute in a different variable
        std::getline(ss, idStr, ',');
        std::getline(ss, name, ',');
        std::getline(ss, categoryStr, ',');
        std::getline(ss, priceStr, ',');
        std::getline(ss, qtyStr, ',');
        //convert the strings into the needed data types
        int id = std::stoi(idStr);
        Category cat = CraftItem::stringToCategory(categoryStr);
        double price = std::stod(priceStr);
        int qty = std::stoi(qtyStr);
        //create the item and add it to the vector of items
        auto item = std::make_shared<CraftItem>(id, name, cat, price, qty);
        Repository::add(item);
    }
}

void RepositoryFileCSV::saveToFile() {
    std::ofstream file(filename);
    if (!file.is_open()) return;
    // iterate through the items and write its attributes one by one separated by comma
    for (const auto& item : items) {
        file << item->getID() << ","
             << item->getName() << ","
             << item->getCategoryAsString() << ","
             << item->getPrice() << ","
             << item->getQuantity() << "\n";
    }
    file.close();
}

RepositoryFileJSON::RepositoryFileJSON(const std::string &file) : RepositoryFile(file) {
    loadFromFile();
}

void RepositoryFileJSON::loadFromFile() {
    // open the file and read from it
    QFile file(QString::fromStdString(filename));
    // if it does not exist yet, start with an empty list
    if (!file.open(QIODevice::ReadOnly)) return;
    // read the whole content
    QByteArray data = file.readAll();
    file.close();

    // convert the text in a JSON document
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray jsonArray = doc.array(); // extract the object list that is encapsulated between []

    // iterate through the list and create the C++ objects
    for (int i = 0; i < jsonArray.size(); ++i) {
        // converts each element encapsulated in {} into an object
        QJsonObject obj = jsonArray[i].toObject();
        //extract the attributes
        int id = obj["id"].toInt();
        std::string name = obj["name"].toString().toStdString();
        Category cat = CraftItem::stringToCategory(obj["category"].toString().toStdString());
        double price = obj["price"].toDouble();
        int qty = obj["quantity"].toInt();
        //create the item and add it to the vector
        auto item = std::make_shared<CraftItem>(id, name, cat, price, qty);
        Repository::add(item);
    }
}

void RepositoryFileJSON::saveToFile() {
    QJsonArray jsonArray;
    // iterate through the items and convert them into JSON objects
    for (const auto& item : items) {
        QJsonObject obj;
        obj["id"] = item->getID();
        obj["name"] = QString::fromStdString(item->getName());
        obj["category"] = QString::fromStdString(item->getCategoryAsString());
        obj["price"] = item->getPrice();
        obj["quantity"] = item->getQuantity();
        //add the item to the list
        jsonArray.append(obj);
    }
    // create the final document and write it on the disk
    QJsonDocument doc(jsonArray);
    QFile file(QString::fromStdString(filename));
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    }
}
