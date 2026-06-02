#pragma once
#include <string>

/**
 * @enum Category
 * @brief Defines the available categories for craft items in the store.
 */
enum class Category {
    Material,   ///< Raw materials used for crafting (e.g., thread, paint).
    Tool,       ///< Instruments or tools used to create crafts (e.g., scissors, brushes).
    Blank,      ///< Unfinished items ready to be decorated (e.g., wooden boxes, ceramic vases).
    Packaging   ///< Materials used for packaging finished products (e.g., boxes, wrapping paper).
};

/**
 * @class CraftItem
 * @brief Represents a single product in the handmade craft store.
 * * This class acts as the main domain entity of the application. It holds all
 * relevant details about a specific craft item, including its identifier, name,
 * category, pricing, and available stock.
 */
class CraftItem {
private:
    int id;             ///< The unique identifier for the item.
    std::string name;   ///< The name of the craft product.
    Category category;  ///< The category the item belongs to.
    double price;       ///< The retail price of the item.
    int quantity;       ///< The available stock quantity.

public:
    /**
     * @brief Constructs a new Craft Item object.
     * @param id The unique ID of the item.
     * @param name The name of the product.
     * @param category The category enum of the item.
     * @param price The cost of the item.
     * @param quantity The initial stock available.
     */
    CraftItem(int id, const std::string &name, Category category, double price, int quantity);

    /**
     * @brief Gets the unique ID of the item.
     * @return The integer ID.
     */
    int getID() const;

    /**
     * @brief Gets the name of the item.
     * @return A constant reference to the item's name string.
     */
    const std::string& getName() const;

    /**
     * @brief Gets the category of the item.
     * @return The item's category as an enum.
     */
    Category getCategory() const;

    /**
     * @brief Gets the current price of the item.
     * @return The price as a double.
     */
    double getPrice() const;

    /**
     * @brief Gets the available stock quantity.
     * @return The quantity as an integer.
     */
    int getQuantity() const;

    /**
     * @brief Updates the price of the item.
     * @param newPrice The new price to be set.
     */
    void setPrice(double newPrice);

    /**
     * @brief Updates the available stock quantity of the item.
     * @param newQuantity The new stock amount.
     */
    void setQuantity(int newQuantity);

    /**
     * @brief Converts the item's category enum to its string representation.
     * * Useful for displaying the category in the User Interface or saving to text files.
     * @return A string representing the category (e.g., "Material").
     */
    std::string getCategoryAsString() const;

    /**
     * @brief Static utility method that converts a string to the corresponding Category enum.
     * * Useful when parsing data from the User Interface or reading from text files.
     * @param categoryStr The string representation of the category.
     * @return The corresponding Category enum value.
     * @throws std::invalid_argument If the string does not match any known category.
     */
    static Category stringToCategory(const std::string& categoryStr);

    /**
     * @brief Default destructor.
     */
    ~CraftItem() = default;
};