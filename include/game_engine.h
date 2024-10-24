#ifndef GAME_ENGINE_H_
#define GAME_ENGINE_H_

#include "command_parser.h"
#include "game_world.h"
#include <memory>
#include <string>
/**
 * @class GameEngine
 * @brief Main driver of the game
 *
 * This class manages the game loop, processes commands, and coordinates
 * between different game components.
 */
class GameEngine
{
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
    bool running_;                         ///< Flag indicating if game is running
    CommandParser commandParser_;          ///< Parser for handling user input
    std::unique_ptr<GameWorld> gameWorld_; ///< The game world instance

    /**
     * @brief Initialize the game
     */
    void initialize();

    /**
     * @brief Process a single game turn
     */
    void processTurn();

    /**
     * @brief Execute a command
     * @param command The command to execute
     */
    void executeCommand(const CommandParser::Command &command);
};
#endif