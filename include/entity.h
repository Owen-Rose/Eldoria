#ifndef ENTITY_H
#define ENTITY_H

#include <string>

class Entity {
public:
    Entity(const std::string& name, const std::string& description)
        : name(name), description(description) {}

    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
    virtual std::string Examine() const { return description; }

protected:
    std::string name;
    std::string description;
};

#endif // ENTITY_H