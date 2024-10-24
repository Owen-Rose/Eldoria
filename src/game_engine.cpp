#include "game_engine.h"
#include <iostream>

GameEngine::GameEngine() : running_(false), gameWorld_(nullptr) {}

void GameEngine::run()
{
    initialize();
    running_ = true;

    std::cout << "Welcome to Eldoria!\n";
    std::cout << "Type 'help' for a list of commands.\n\n";

    while (running_)
    {
        processTurn();
    }

    std::cout << "Thank you for playing!\n";
}

void GameEngine::initialize()
{
    gameWorld_ = std::make_unique<GameWorld>();
    // Additional initialization code will go here
}

void GameEngine::processTurn()
{
    auto command = commandParser_.getCommand();

    if (command.isValid)
    {
        executeCommand(command);
    }
    else
    {
        std::cout << "Invalid command. Type 'help' for a list of commands.\n";
    }
}

void GameEngine::executeCommand(const CommandParser::Command &command)
{
    if (command.action == "quit")
    {
        stop();
        return;
    }

    // Handle other commands
    if (command.action == "help")
    {
        std::cout << "Available commands:\n"
                  << "  look        - Look around the current location\n"
                  << "  move [dir]  - Move in the specified direction\n"
                  << "  quit        - Exit the game\n"
                  << "  help        - Show this help message\n";
    }
    else if (command.action == "look")
    {
        // TODO: Implement look command using GameWorld
        std::cout << "You look around.\n";
    }
    else if (command.action == "move")
    {
        if (command.arguments.empty())
        {
            std::cout << "Move where? Please specify a direction.\n";
        }
        else
        {
            // TODO: Implement movement using GameWorld
            std::cout << "You try to move " << command.arguments[0] << ".\n";
        }
    }
    else
    {
        std::cout << "Unknown command. Type 'help' for available commands.\n";
    }
}

void GameEngine::stop()
{
    running_ = false;
}

bool GameEngine::isRunning() const
{
    return running_;
}
