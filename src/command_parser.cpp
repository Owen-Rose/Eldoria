#include "command_parser.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>

CommandParser::Command CommandParser::getCommand()
{
    std::string input;
    std::cout << "> ";
    std::getline(std::cin, input);
    return parseInput(input);
}

CommandParser::Command CommandParser::parseInput(const std::string &input)
{
    Command cmd;
    cmd.isValid = false;

    // Check for empty input
    if (input.empty())
    {
        return cmd;
    }

    // Validate input characters
    if (!isValidInput(input))
    {
        return cmd;
    }

    // Convert to lowercase and parse
    std::string lowercaseInput = toLowerCase(input);
    std::istringstream stream(lowercaseInput);

    // Get the main command
    stream >> cmd.action;

    // Get any arguments
    std::string arg;
    while (stream >> arg)
    {
        cmd.arguments.push_back(arg);
    }

    cmd.isValid = true;
    return cmd;
}

bool CommandParser::isValidInput(const std::string &input) const
{
    return std::all_of(input.begin(), input.end(),
                       [](char ch)
                       { return std::isalnum(ch) || std::isspace(ch); });
}

std::string CommandParser::toLowerCase(const std::string &input) const
{
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c)
                   { return std::tolower(c); });
    return result;
}