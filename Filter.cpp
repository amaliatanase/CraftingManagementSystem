#include "Filter.h"
#include "Controller.h"
#include "CraftItem.h"
#include <algorithm>
#include <memory>

static std::string convertToLower(const std::string& s) {
    std::string res = s;
    std::transform(res.begin(), res.end(), res.begin(), ::tolower);
    return res;
}

static bool containsString(const std::string& text, const std::string& query) {
    std::string textLower = convertToLower(text);
    std::string queryLower = convertToLower(query);
    return textLower.find(queryLower) != std::string::npos;
}

CategoryFilter::CategoryFilter(Category cat) : targetCategory(cat) {}

bool CategoryFilter::matches(std::shared_ptr<CraftItem> item) const {
    return item->getCategory() == targetCategory;
}

MaxPriceFilter::MaxPriceFilter(double price) : maxPrice(price) {}

bool MaxPriceFilter::matches(std::shared_ptr<CraftItem> item) const {
    return item->getPrice() <= maxPrice;
}

NameFilter::NameFilter(const std::string& query) : searchQuery(query) {}

bool NameFilter::matches(std::shared_ptr<CraftItem> item) const {
    return containsString(item->getName(), searchQuery);
}

AndFilter::AndFilter(std::shared_ptr<Filter> f1, std::shared_ptr<Filter> f2) : filter1(f1), filter2(f2) {}

bool AndFilter::matches(std::shared_ptr<CraftItem> item) const {
    // item needs to meet both criteria
    // the matches method of each filter is being called
    return filter1->matches(item) && filter2->matches(item);
}

OrFilter::OrFilter(std::shared_ptr<Filter> f1, std::shared_ptr<Filter> f2) : filter1(f1), filter2(f2) {}

bool OrFilter::matches(std::shared_ptr<CraftItem> item) const {
    // item needs to meet at least a criterion
    // the matches method of each filter is being called
    return filter1->matches(item) || filter2->matches(item);
}