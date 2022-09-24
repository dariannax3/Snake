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

bool isInRange(int begin, int end, int value);

template <typename T>
static void displayGameboard(const std::vector<std::vector<T>>& matrix)
{
    for(auto row_obj : matrix)
    {
        for (auto elem: row_obj)
        {
            std::cout<<elem<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

class Gameboard {
public:
    Gameboard(int width, int height) : width_(width), height_(height) {
        initializeDefaultGameboard();
    }
    ~Gameboard() = default;

    FieldState checkFieldAt(const int width, const int height);

    int getWidth() const { return width_; }
    int getHeight() const { return height_; }
    std::vector<std::vector<FieldState>> getGameboard() const { return gameboard_; }
    
    void initializeDefaultGameboard();
    void updateSnake(Snake& snake);
    void addFoodAt(Coordinates newFood);

private:    
    std::vector<std::vector<FieldState>> gameboard_;
    int width_;
    int height_;
};