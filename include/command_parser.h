#ifndef COMMAND_PARSER_H_
#define COMMAND_PARSER_H_

#include <string>
#include <vector>
#include <utility>

/**
 * @class CommandParser
 * @brief Processes and validates user input for the game
 * 
 * This class handles all command parsing, input validation, and initial processing
 * of user commands before they are executed by the game engine.
 */
class CommandParser {
 public:
    /**
     * @brief Structure to hold a parsed command
     */
    struct Command {
        std::string action;                  ///< The main command action
        std::vector<std::string> arguments;  ///< Command arguments
        bool isValid;                        ///< Indicates if the command is valid
    };

    /**
     * @brief Get input from the user and process it
     * @return Command structure containing the processed input
     */
    Command getCommand();

    /**
     * @brief Process a raw input string into a command
     * @param input The raw input string to process
     * @return Command structure containing the processed command
     */
    Command parseInput(const std::string& input);

 private:
    /**
     * @brief Check if the input contains only valid characters
     * @param input String to validate
     * @return true if input is valid, false otherwise
     */
    bool isValidInput(const std::string& input) const;

    /**
     * @brief Convert a string to lowercase
     * @param input String to convert
     * @return Lowercase version of the input string
     */
    std::string toLowerCase(const std::string& input) const;
};

#endif