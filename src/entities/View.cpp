#include "View.h"

using namespace Spark::Entity;

// Iterator constructor
View::iterator::iterator(EntityIterator it) : entityIt(it) {}

// Iterator operations
View::iterator& View::iterator::operator++() {
    ++entityIt;
    return *this;
}

bool View::iterator::operator!=(const iterator& other) const {
    return entityIt != other.entityIt;
}

// Dereference operator
unsigned int View::iterator::operator*() const {
    return entityIt->first;
}

Spark::Entity::View::iterator Spark::Entity::View::begin() const
{
    return iterator(entities.begin());
}

Spark::Entity::View::iterator Spark::Entity::View::end() const
{
    return iterator(entities.end());
}
