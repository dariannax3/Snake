#pragma once
#include <utility>

using Coordinates = std::pair<int,int>;

enum class FieldState {
    Wall,
    Empty
};

bool isInRange(int begin, int end, int value);

class Gameboard {
public:
    Gameboard(int width, int height) : width_(width), height_(height) {}
    ~Gameboard() = default;

    FieldState checkFieldAt(const int width, const int height);

    int getWidth() const { return width_; }
    int getHeight() const { return height_; }
private:
    int width_;
    int height_;
};

enum class Direction
{
    ToTop,
    ToLeft
};

class Snake
{
public:
    Snake(Coordinates headSnake, Direction direction = Direction::ToTop) : direction_(direction), headSnake_(headSnake)
    {
        if(direction == Direction::ToTop)
        {
            tailSnake_ = headSnake;
            tailSnake_.second -= beginBodySize;
        }
    }
    Coordinates getHead() const { return headSnake_; }
    Coordinates getTail() const { return tailSnake_; }
    void move();
    void changeDirection(const Direction direction);
private:
    Direction direction_;
    Coordinates headSnake_;
    Coordinates tailSnake_;
    const int beginBodySize{4};
};