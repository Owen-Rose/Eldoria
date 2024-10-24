#ifndef GAME_ENGINE_H_
#define GAME_ENGINE_H_

#include "command_parser.h"
#include "game_world.h"
#include "player.h"
#include <memory>
#include <string>

/**
 * @class GameEngine
 * @brief Main driver of the game
 *
 * This class manages the game loop, processes commands, and coordinates
 * between different game components. It handles all primary game functionality
 * including movement, environment interaction, and game state management.
 */
class GameEngine {
public:
    /**
     * @brief Constructor for GameEngine
     */
    GameEngine();

    /**
     * @brief Start the game loop
     */
    void run();

    /**
     * @brief Check if the game is still running
     * @return true if the game is running
     */
    bool isRunning() const;

    /**
     * @brief Stop the game
     */
    void stop();

private:
    bool running_;                               ///< Flag indicating if game is running
    CommandParser commandParser_;                ///< Parser for handling user input
    std::unique_ptr<GameWorld> gameWorld_;       ///< The game world instance
    std::unique_ptr<Player> currentPlayer_;      ///< The current player instance

    /**
     * @brief Initialize the game
     * Sets up the game world, player, and initial game state
     */
    void initialize();

    /**
     * @brief Process a single game turn
     * Handles command input and execution
     */
    void processTurn();

    /**
     * @brief Execute a parsed command
     * @param command The command to execute
     */
    void executeCommand(const CommandParser::Command& command);

    /**
     * @brief Handle movement commands
     * @param command The movement command to process
     */
    void handleMovement(const CommandParser::Command& command);

    /**
     * @brief Handle examine commands
     * @param command The examine command to process
     */
    void handleExamine(const CommandParser::Command& command);

    /**
     * @brief Handle pickup commands
     * @param command The pickup command to process
     */
    void handlePickup(const CommandParser::Command& command);

    /**
     * @brief Handle drop commands
     * @param command The drop command to process
     */
    void handleDrop(const CommandParser::Command& command);

    /**
     * @brief Handle use commands
     * @param command The use command to process
     */
    void handleUse(const CommandParser::Command& command);

    /**
     * @brief Display the current location details
     * Shows description, exits, items, and NPCs
     */
    void displayCurrentLocation();

    /**
     * @brief Display the help message
     * Shows available commands and their usage
     */
    void displayHelp();

    /**
     * @brief Display the welcome message
     * Shows game title and initial instructions
     */
    void displayWelcomeMessage();

    /**
     * @brief Display the player's inventory
     * Shows all items currently carried by the player
     */
    void displayInventory();
};

#endif  // GAME_ENGINE_H_