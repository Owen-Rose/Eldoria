#include "reflection_puzzle.h"
#include <cmath>
#include <queue>

ReflectionPuzzle::ReflectionPuzzle(const std::string& name,
                                   const std::string& description,
                                   int source_x, int source_y,
                                   int target_x, int target_y,
                                   int max_mirrors)
    : Puzzle(name, description),
      source_x_(source_x),
      source_y_(source_y),
      target_x_(target_x),
      target_y_(target_y),
      max_mirrors_(max_mirrors),
      placed_mirrors_(0),
      has_crystal_lens_(false) {
    
    if (!ValidateCoordinates(source_x, source_y) ||
        !ValidateCoordinates(target_x, target_y)) {
        throw std::invalid_argument("Invalid coordinates");
    }

    if (max_mirrors < 1) {
        throw std::invalid_argument("Must allow at least one mirror");
    }

    // Initialize empty grid
    for (auto& row : grid_) {
        row.fill(std::nullopt);
    }
}

bool ReflectionPuzzle::AttemptSolution(const std::string& /* attempt */) {
    if (!CanAttempt()) {
        throw PuzzleException("Cannot attempt puzzle without Crystal Lens");
    }

    bool solved = SimulateBeam();
    if (solved) {
        SetState(PuzzleState::SOLVED);
    }

    return solved;
}

std::string ReflectionPuzzle::GetHint() const {
    if (!has_crystal_lens_) {
        return "You need the Crystal Lens to attempt this puzzle.";
    }

    auto path = GetBeamPath();
    if (path.empty()) {
        return "Try placing a mirror to redirect the light beam.";
    }

    auto last = path.back();
    if (last.first == target_x_ && last.second == target_y_) {
        return "The beam has reached its target!";
    }

    // Calculate distance to target
    int dx = target_x_ - last.first;
    int dy = target_y_ - last.second;
    
    if (std::abs(dx) > std::abs(dy)) {
        return dx > 0 ? "Try redirecting the beam eastward." 
                     : "Try redirecting the beam westward.";
    } else {
        return dy > 0 ? "Try redirecting the beam southward." 
                     : "Try redirecting the beam northward.";
    }
}

bool ReflectionPuzzle::CanAttempt() const {
    return has_crystal_lens_ && Puzzle::CanAttempt();
}

bool ReflectionPuzzle::PlaceMirror(int x, int y, int rotation) {
    if (!ValidateCoordinates(x, y)) {
        return false;
    }

    if (grid_[y][x].has_value()) {
        return false;
    }

    if (placed_mirrors_ >= max_mirrors_) {
        return false;
    }

    if (x == source_x_ && y == source_y_) {
        return false;
    }

    if (x == target_x_ && y == target_y_) {
        return false;
    }

    grid_[y][x] = Mirror{NormalizeRotation(rotation), true};
    placed_mirrors_++;
    return true;
}

bool ReflectionPuzzle::RemoveMirror(int x, int y) {
    if (!ValidateCoordinates(x, y)) {
        return false;
    }

    if (!grid_[y][x].has_value()) {
        return false;
    }

    grid_[y][x] = std::nullopt;
    placed_mirrors_--;
    return true;
}

bool ReflectionPuzzle::RotateMirror(int x, int y, int degrees) {
    if (!ValidateCoordinates(x, y)) {
        return false;
    }

    auto& mirror_opt = grid_[y][x];
    if (!mirror_opt.has_value()) {
        return false;
    }

    mirror_opt->rotation = NormalizeRotation(mirror_opt->rotation + degrees);
    return true;
}

std::vector<std::pair<int, int>> ReflectionPuzzle::GetBeamPath() const {
    std::vector<std::pair<int, int>> path;
    LightBeam beam{source_x_, source_y_, 1, 0};  // Start moving right
    
    while (ValidateCoordinates(beam.x, beam.y)) {
        path.emplace_back(beam.x, beam.y);
        
        if (beam.x == target_x_ && beam.y == target_y_) {
            break;
        }

        if (grid_[beam.y][beam.x].has_value()) {
            beam = CalculateReflection(beam, *grid_[beam.y][beam.x]);
        }

        beam.x += beam.dx;
        beam.y += beam.dy;
    }

    return path;
}

void ReflectionPuzzle::SetHasLens(bool has_lens) {
    has_crystal_lens_ = has_lens;
}

LightBeam ReflectionPuzzle::CalculateReflection(const LightBeam& beam, 
                                               const Mirror& mirror) {
    // Convert rotation to radians
    double angle = mirror.rotation * M_PI / 180.0;
    
    // Rotate direction vector
    int new_dx = static_cast<int>(std::round(
        beam.dx * std::cos(2 * angle) + beam.dy * std::sin(2 * angle)));
    int new_dy = static_cast<int>(std::round(
        beam.dx * std::sin(2 * angle) - beam.dy * std::cos(2 * angle)));
    
    return LightBeam{beam.x, beam.y, new_dx, new_dy};
}

bool ReflectionPuzzle::ValidateCoordinates(int x, int y) {
    return x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE;
}

int ReflectionPuzzle::NormalizeRotation(int degrees) {
    degrees = degrees % 360;
    if (degrees < 0) {
        degrees += 360;
    }
    return degrees;
}

bool ReflectionPuzzle::SimulateBeam() const {
    auto path = GetBeamPath();
    if (path.empty()) {
        return false;
    }

    auto last = path.back();
    return last.first == target_x_ && last.second == target_y_;
}