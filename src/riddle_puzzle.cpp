#include "riddle_puzzle.h"

RiddlePuzzle::RiddlePuzzle(const std::string& name,
                           const std::string& description,
                           const std::vector<std::string>& answers,
                           const std::string& hint,
                           int max_attempts)
    : Puzzle(name, description, max_attempts),
      correct_answers_(answers),
      hint_(hint) {
    if (answers.empty()) {
        throw std::invalid_argument("Riddle must have at least one correct answer");
    }

    // Normalize all answers for consistent comparison
    for (auto& answer : correct_answers_) {
        answer = NormalizeString(answer);
    }
}

bool RiddlePuzzle::AttemptSolution(const std::string& attempt) {
    if (!CanAttempt()) {
        throw PuzzleException("Cannot attempt puzzle: " + GetName());
    }

    std::string normalized_attempt = NormalizeString(attempt);
    
    // Check if the attempt matches any correct answer
    bool is_correct = std::find(correct_answers_.begin(),
                               correct_answers_.end(),
                               normalized_attempt) != correct_answers_.end();

    IncrementAttempts();
    
    if (is_correct) {
        SetState(PuzzleState::SOLVED);
        return true;
    }

    return false;
}

std::string RiddlePuzzle::GetHint() const {
    return hint_;
}

std::string RiddlePuzzle::NormalizeString(const std::string& str) {
    std::string result = str;
    
    // Convert to lowercase
    std::transform(result.begin(), result.end(), result.begin(), 
                  [](unsigned char c) { return std::tolower(c); });
    
    // Trim leading whitespace
    result.erase(0, result.find_first_not_of(" \t\n\r\f\v"));
    
    // Trim trailing whitespace
    result.erase(result.find_last_not_of(" \t\n\r\f\v") + 1);
    
    return result;
}