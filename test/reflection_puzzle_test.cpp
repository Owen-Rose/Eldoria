#include <gtest/gtest.h>
#include "reflection_puzzle.h"

class ReflectionPuzzleTest : public ::testing::Test {
 protected:
    void SetUp() override {
        // Create a puzzle with light source at (0,0) and target at (4,4)
        puzzle_ = std::make_unique<ReflectionPuzzle>(
            "Test Reflection",
            "Redirect the light to the target",
            0, 0,    // source coordinates
            4, 4,    // target coordinates
            3        // max mirrors
        );
    }

    std::unique_ptr<ReflectionPuzzle> puzzle_;
};

TEST_F(ReflectionPuzzleTest, CannotAttemptWithoutLens) {
    EXPECT_FALSE(puzzle_->CanAttempt());
}

TEST_F(ReflectionPuzzleTest, CanAttemptWithLens) {
    puzzle_->SetHasLens(true);
    EXPECT_TRUE(puzzle_->CanAttempt());
}

TEST_F(ReflectionPuzzleTest, PlaceMirrorValidLocation) {
    EXPECT_TRUE(puzzle_->PlaceMirror(2, 2, 45));
}

TEST_F(ReflectionPuzzleTest, PlaceMirrorInvalidLocation) {
    EXPECT_FALSE(puzzle_->PlaceMirror(0, 0, 45));  // Source location
    EXPECT_FALSE(puzzle_->PlaceMirror(4, 4, 45));  // Target location
    EXPECT_FALSE(puzzle_->PlaceMirror(-1, 0, 45)); // Out of bounds
}

TEST_F(ReflectionPuzzleTest, RotateMirror) {
    EXPECT_TRUE(puzzle_->PlaceMirror(2, 2, 0));
    EXPECT_TRUE(puzzle_->RotateMirror(2, 2, 45));
}

TEST_F(ReflectionPuzzleTest, SolvePuzzle) {
    puzzle_->SetHasLens(true);
    
    // Place mirrors to create a path to target
    EXPECT_TRUE(puzzle_->PlaceMirror(2, 0, 45));
    EXPECT_TRUE(puzzle_->PlaceMirror(4, 2, 45));
    
    EXPECT_TRUE(puzzle_->AttemptSolution(""));
    EXPECT_TRUE(puzzle_->IsSolved());
}