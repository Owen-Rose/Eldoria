#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <unordered_map>

class Room {
public:
    // Constructor: Initializes the room with a name and description
    Room(std::string roomName, std::string roomDescription);

    // Destructor
    ~Room() = default;

    // Public Methods
    std::string getName() const;                 // Returns the name of the room
    std::string getDescription() const;          // Returns the description of the room
    void setWall(std::string direction);         // Sets a wall in a specific direction
    void setDoor(std::string direction);         // Sets a door in a specific direction
    bool hasWall(std::string direction) const;   // Checks if there is a wall in a specific direction
    bool hasDoor(std::string direction) const;   // Checks if there is a door in a specific direction

private:
    std::string name;                            // Room name
    std::string description;                     // Room description

    // Maps to represent walls and doors in each direction
    std::unordered_map<std::string, bool> walls;
    std::unordered_map<std::string, bool> doors;
};

#endif  // End of include guard
