#include "book_sorting_puzzle.h"
#include <algorithm>
#include <stdexcept>

Book::Book(const std::string& id,
           const std::string& title,
           const std::string& inscription,
           const std::string& theme)
    : id_(id),
      title_(title),
      inscription_(inscription),
      theme_(theme) {}

BookSortingPuzzle::BookSortingPuzzle(
    const std::string& name,
    const std::string& description,
    const std::vector<std::shared_ptr<Book>>& books,
    const std::vector<std::vector<std::string>>& valid_sequences,
    const std::string& hint,
    int max_attempts)
    : Puzzle(name, description, max_attempts),
      books_(books),
      valid_sequences_(valid_sequences),
      hint_(hint) {
    
    ValidateParameters();
    InitializeBookMap();
    
    // Initialize current arrangement with empty slots
    current_arrangement_.resize(books.size(), "");
}

bool BookSortingPuzzle::PlaceBook(const std::string& book_id, size_t position) {
    if (position >= current_arrangement_.size()) {
        throw std::out_of_range("Invalid position");
    }

    // Check if book exists
    if (book_map_.find(book_id) == book_map_.end()) {
        return false;
    }

    // Check if book is already placed elsewhere
    auto existing = std::find(current_arrangement_.begin(),
                            current_arrangement_.end(),
                            book_id);
    if (existing != current_arrangement_.end()) {
        return false;
    }

    current_arrangement_[position] = book_id;
    return true;
}

std::string BookSortingPuzzle::RemoveBook(size_t position) {
    if (position >= current_arrangement_.size()) {
        throw std::out_of_range("Invalid position");
    }

    std::string removed = current_arrangement_[position];
    current_arrangement_[position] = "";
    return removed;
}

std::shared_ptr<Book> BookSortingPuzzle::GetBookAt(size_t position) const {
    if (position >= current_arrangement_.size()) {
        throw std::out_of_range("Invalid position");
    }

    const std::string& book_id = current_arrangement_[position];
    if (book_id.empty()) {
        return nullptr;
    }

    auto it = book_map_.find(book_id);
    return (it != book_map_.end()) ? it->second : nullptr;
}

std::vector<std::string> BookSortingPuzzle::GetCurrentArrangement() const {
    return current_arrangement_;
}

bool BookSortingPuzzle::AttemptSolution(const std::string& /* attempt */) {
    if (!CanAttempt()) {
        throw PuzzleException("Cannot attempt puzzle: " + GetName());
    }

    // Check if all positions are filled
    if (std::find(current_arrangement_.begin(),
                  current_arrangement_.end(),
                  "") != current_arrangement_.end()) {
        IncrementAttempts();
        return false;
    }

    bool is_correct = ValidateArrangement();
    IncrementAttempts();

    if (is_correct) {
        SetState(PuzzleState::SOLVED);
        return true;
    }

    return false;
}

std::string BookSortingPuzzle::GetHint() const {
    return hint_;
}

void BookSortingPuzzle::Reset() {
    Puzzle::Reset();
    std::fill(current_arrangement_.begin(), current_arrangement_.end(), "");
}

size_t BookSortingPuzzle::GetTotalPositions() const {
    return current_arrangement_.size();
}

std::vector<std::shared_ptr<Book>> BookSortingPuzzle::GetAvailableBooks() const {
    return books_;
}

bool BookSortingPuzzle::ValidateArrangement() const {
    return std::find(valid_sequences_.begin(),
                    valid_sequences_.end(),
                    current_arrangement_) != valid_sequences_.end();
}

void BookSortingPuzzle::InitializeBookMap() {
    for (const auto& book : books_) {
        book_map_[book->GetId()] = book;
    }
}

void BookSortingPuzzle::ValidateParameters() {
    if (books_.empty()) {
        throw std::invalid_argument("Must provide at least one book");
    }

    if (valid_sequences_.empty()) {
        throw std::invalid_argument("Must provide at least one valid sequence");
    }

    // Validate sequence lengths match number of books
    for (const auto& sequence : valid_sequences_) {
        if (sequence.size() != books_.size()) {
            throw std::invalid_argument("Invalid sequence length");
        }
    }

    // Check for duplicate book IDs
    std::unordered_map<std::string, bool> id_map;
    for (const auto& book : books_) {
        if (!book) {
            throw std::invalid_argument("Null book pointer");
        }
        if (id_map.find(book->GetId()) != id_map.end()) {
            throw std::invalid_argument("Duplicate book ID: " + book->GetId());
        }
        id_map[book->GetId()] = true;
    }
}
