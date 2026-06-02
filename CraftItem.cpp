#include "CraftItem.h"
#include <string>
#include <stdexcept>

CraftItem::CraftItem(int id, const std::string &name, Category category, double price, int quantity): id(id),
    name(name), category(category), price(price), quantity(quantity) {}

int CraftItem::getID() const {return id;}
const std::string & CraftItem::getName() const {return name;}
Category CraftItem::getCategory() const {return category;}
double CraftItem::getPrice() const {return price;}
int CraftItem::getQuantity() const {return quantity;}

void CraftItem::setPrice(double newPrice) {price = newPrice;}
void CraftItem::setQuantity(int newQuantity) {quantity = newQuantity;}

std::string CraftItem::getCategoryAsString() const {
    // the enum will return the position of the category in the enumeration
    switch (category) {
        case Category::Material: return "Material";
        case Category::Tool: return "Tool";
        case Category::Blank: return "Blank";
        case Category::Packaging: return "Packaging";
        default: return "Unknown";
    }
}

Category CraftItem::stringToCategory(const std::string &categoryStr) {
    // associating the name with the category in the enum
    if (categoryStr == "Material") return Category::Material;
    else if (categoryStr == "Tool") return Category::Tool;
    else if (categoryStr == "Blank") return Category::Blank;
    else if (categoryStr == "Packaging") return Category::Packaging;
    throw std::invalid_argument("Unknown category" + categoryStr);
}
