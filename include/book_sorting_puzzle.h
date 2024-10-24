#ifndef BOOK_SORTING_PUZZLE_H_
#define BOOK_SORTING_PUZZLE_H_

#include "puzzle.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

/**
 * @class Book
 * @brief Represents a book in the sorting puzzle
 */
class Book {
 public:
    /**
     * @brief Constructor for Book
     * @param id Unique identifier for the book
     * @param title The book's title
     * @param inscription Text inscribed in the book
     * @param theme The book's theme or category
     */
    Book(const std::string& id,
         const std::string& title,
         const std::string& inscription,
         const std::string& theme);

    std::string GetId() const { return id_; }
    std::string GetTitle() const { return title_; }
    std::string GetInscription() const { return inscription_; }
    std::string GetTheme() const { return theme_; }

 private:
    std::string id_;          ///< Unique identifier
    std::string title_;       ///< Book title
    std::string inscription_; ///< Inscribed text
    std::string theme_;       ///< Book theme/category
};

/**
 * @class BookSortingPuzzle
 * @brief Puzzle where players must arrange books in the correct order
 * 
 * Players must examine inscriptions and arrange books based on themes
 * and historical periods. Multiple valid arrangements may exist.
 */
class BookSortingPuzzle : public Puzzle {
 public:
    /**
     * @brief Constructor for BookSortingPuzzle
     * @param name Puzzle name
     * @param description Puzzle description
     * @param books Vector of books to be sorted
     * @param valid_sequences Vector of valid book orderings
     * @param hint Optional hint text
     * @param max_attempts Maximum allowed attempts (-1 for unlimited)
     */
    BookSortingPuzzle(const std::string& name,
                      const std::string& description,
                      const std::vector<std::shared_ptr<Book>>& books,
                      const std::vector<std::vector<std::string>>& valid_sequences,
                      const std::string& hint = "",
                      int max_attempts = -1);

    /**
     * @brief Place a book in a specific position
     * @param book_id ID of the book to place
     * @param position Position in sequence (0-based)
     * @return true if placement was successful
     * @throws std::out_of_range if position is invalid
     */
    bool PlaceBook(const std::string& book_id, size_t position);

    /**
     * @brief Remove a book from a position
     * @param position Position to remove from
     * @return ID of removed book, empty string if position was empty
     */
    std::string RemoveBook(size_t position);

    /**
     * @brief Get book at specified position
     * @param position Position to check
     * @return Pointer to book, nullptr if position is empty
     */
    std::shared_ptr<Book> GetBookAt(size_t position) const;

    /**
     * @brief Get current arrangement
     * @return Vector of book IDs in current order
     */
    std::vector<std::string> GetCurrentArrangement() const;

    /**
     * @brief Attempt to solve with current arrangement
     * @param attempt Unused parameter (required by base class)
     * @return true if current arrangement is valid
     */
    bool AttemptSolution(const std::string& attempt = "") override;

    /**
     * @brief Get hint for puzzle
     * @return Hint string
     */
    std::string GetHint() const override;

    /**
     * @brief Reset puzzle to initial state
     */
    void Reset() override;

    /**
     * @brief Get total number of slots for books
     * @return Number of positions available
     */
    size_t GetTotalPositions() const;

    /**
     * @brief Get all available books
     * @return Vector of all books in the puzzle
     */
    std::vector<std::shared_ptr<Book>> GetAvailableBooks() const;

 private:
    std::vector<std::shared_ptr<Book>> books_;              ///< All books in puzzle
    std::vector<std::string> current_arrangement_;          ///< Current book order
    std::vector<std::vector<std::string>> valid_sequences_; ///< Valid solutions
    std::string hint_;                                      ///< Puzzle hint
    std::unordered_map<std::string, std::shared_ptr<Book>> book_map_; ///< Quick book lookup

    /**
     * @brief Validate current arrangement against solutions
     * @return true if arrangement matches any valid sequence
     */
    bool ValidateArrangement() const;

    /**
     * @brief Initialize the book lookup map
     */
    void InitializeBookMap();

    /**
     * @brief Validate puzzle parameters
     * @throws std::invalid_argument if parameters are invalid
     */
    void ValidateParameters();
};

#endif  // BOOK_SORTING_PUZZLE_H_