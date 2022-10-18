#pragma once
#include "Snake.hpp"
#include <iostream>
#include <vector>

enum class FieldState {
    Empty,
    Wall,
    Food,
    Snake,
};

inline std::ostream &operator<<(std::ostream &os, FieldState state) {
  switch(state) {
    case FieldState::Empty: os << "."; break;
    case FieldState::Wall: os << "W"; break;
    case FieldState::Food: os << "F"; break;
    case FieldState::Snake: os << "S"; break;
  }
  return os;
}

void displayGameboard(const std::vector<std::vector<FieldState>>& matrix);

bool isInRange(int begin, int end, int value);


class Gameboard {
public:
    Gameboard(int width, int height){
        initializeDefaultGameboard(width, height);
    }
    ~Gameboard() = default;


    FieldState checkFieldAt(const int width, const int height) const;
    int getWidth() const { return static_cast<int>(gameboard_.size()); }
    int getHeight() const { return static_cast<int>(gameboard_.front().size()); }
    std::vector<std::vector<FieldState>> getGameboard() const { return gameboard_; }
    
    void initializeDefaultGameboard(int width, int height);
    void updateSnake(Snake& snake);
    void addFoodAt(Coordinates newFood);

private:    
    std::vector<std::vector<FieldState>> gameboard_;
};