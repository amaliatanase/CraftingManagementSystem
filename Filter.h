#pragma once
#include "CraftItem.h"
#include <memory>
#include <string>

//Specification Pattern: a filtering rule is an object, not a function
/**
 * @class Filter
 * @brief Abstract base class (Interface) for the Specification Design Pattern.
 * * This class defines the contract for filtering rules. Instead of hardcoding
 * filtering logic into large functions, each rule is encapsulated as an object.
 * This makes the system highly extensible.
 */
class Filter {
    //abstract class = interface
public:
    /**
     * @brief Evaluates whether a given item satisfies the filter's criteria.
     * @param item A shared pointer to the CraftItem being evaluated.
     * @return True if the item matches the criteria, false otherwise.
     */
    virtual bool matches(std::shared_ptr<CraftItem> item) const = 0;

    /**
     * @brief Virtual destructor to ensure safe polymorphic deletion.
     */
    virtual ~Filter() = default;
};

/**
 * @class CategoryFilter
 * @brief A specific filter that checks if an item belongs to a target category.
 */
//each derived class has a specific responsability
class CategoryFilter : public Filter {
private:
    Category targetCategory; ///< The specific category to match against.
public:
    /**
     * @brief Constructs a CategoryFilter.
     * @param cat The target Category enum value to filter by.
     */
    CategoryFilter(Category cat);

    bool matches(std::shared_ptr<CraftItem> item) const override;
};

/**
 * @class MaxPriceFilter
 * @brief A specific filter that checks if an item's price is below or equal to a maximum limit.
 */
class MaxPriceFilter : public Filter {
private:
    double maxPrice; ///< The maximum allowed price.
public:
    /**
     * @brief Constructs a MaxPriceFilter.
     * @param price The maximum threshold for the item's price.
     */
    MaxPriceFilter(double price);

    bool matches(std::shared_ptr<CraftItem> item) const override;
};

/**
 * @class NameFilter
 * @brief A specific filter that checks if an item's name contains a given search string.
 */
class NameFilter : public Filter {
private:
    std::string searchQuery; ///< The text to search for within the item's name.
public:
    /**
     * @brief Constructs a NameFilter.
     * @param query The substring to look for in the item names.
     */
    NameFilter(const std::string& query);

    bool matches(std::shared_ptr<CraftItem> item) const override;
};

/**
 * @class AndFilter
 * @brief A composite filter that applies a logical AND operation between two filters.
 * * This class uses the Composite Design Pattern to treat a group of filters
 * exactly as a single filter. It evaluates to true only if both child filters evaluate to true.
 */
//Composite Pattern: treat a group of objects as you would treat an object
//even if it is a complex or simple filter, they all have the same function and will be treated the same
class AndFilter : public Filter {
private:
    // filter 1 and 2 will keep pointers to other filters that can also be simple or complex
    // Filter is an abstract class, so we need pointers to its objects
    // shared, because we also need them in teh controller, repo and ui
    std::shared_ptr<Filter> filter1; ///< The first filter operand.
    std::shared_ptr<Filter> filter2; ///< The second filter operand.
public:
    /**
     * @brief Constructs an AndFilter linking two abstract filters.
     * @param f1 A shared pointer to the first Filter object.
     * @param f2 A shared pointer to the second Filter object.
     */
    AndFilter(std::shared_ptr<Filter> f1, std::shared_ptr<Filter> f2);

    bool matches(std::shared_ptr<CraftItem> item) const override;
};

/**
 * @class OrFilter
 * @brief A composite filter that applies a logical OR operation between two filters.
 * * This class uses the Composite Design Pattern. It evaluates to true if
 * at least one of the child filters evaluates to true.
 */
class OrFilter : public Filter {
private:
    std::shared_ptr<Filter> filter1; ///< The first filter operand.
    std::shared_ptr<Filter> filter2; ///< The second filter operand.
public:
    /**
     * @brief Constructs an OrFilter linking two abstract filters.
     * @param f1 A shared pointer to the first Filter object.
     * @param f2 A shared pointer to the second Filter object.
     */
    OrFilter(std::shared_ptr<Filter> f1, std::shared_ptr<Filter> f2);

    bool matches(std::shared_ptr<CraftItem> item) const override;
};
