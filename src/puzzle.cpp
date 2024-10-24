#include "puzzle.h"

Puzzle::Puzzle(const std::string& name, 
               const std::string& description,
               int max_attempts)
    : name_(name),
      description_(description),
      state_(PuzzleState::UNSOLVED),
      attempts_(0),
      max_attempts_(max_attempts) {
    ValidateParameters();
}

bool Puzzle::IsSolved() const {
    return state_ == PuzzleState::SOLVED;
}

bool Puzzle::CanAttempt() const {
    if (state_ == PuzzleState::SOLVED) {
        return false;
    }
    
    if (state_ == PuzzleState::FAILED) {
        return false;
    }
    
    if (max_attempts_ != -1 && attempts_ >= max_attempts_) {
        return false;
    }
    
    return true;
}

void Puzzle::Reset() {
    state_ = PuzzleState::UNSOLVED;
    attempts_ = 0;
}

PuzzleState Puzzle::GetState() const {
    return state_;
}

std::string Puzzle::GetName() const {
    return name_;
}

std::string Puzzle::GetDescription() const {
    return description_;
}

int Puzzle::GetAttemptsRemaining() const {
    if (max_attempts_ == -1) {
        return -1;
    }
    return max_attempts_ - attempts_;
}

void Puzzle::SetState(PuzzleState new_state) {
    state_ = new_state;
}

bool Puzzle::IncrementAttempts() {
    attempts_++;
    
    if (max_attempts_ != -1 && attempts_ >= max_attempts_) {
        state_ = PuzzleState::FAILED;
        return false;
    }
    
    return true;
}

void Puzzle::ValidateParameters() {
    if (name_.empty()) {
        throw std::invalid_argument("Puzzle name cannot be empty");
    }
    
    if (description_.empty()) {
        throw std::invalid_argument("Puzzle description cannot be empty");
    }
    
    if (max_attempts_ < -1) {
        throw std::invalid_argument("Maximum attempts must be -1 or greater");
    }
}