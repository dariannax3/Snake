#pragma once
#include <utility>
#include <list>

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
    ToBottom,
    ToLeft,
    ToRight,
};

bool isOpposite(Direction lhs, Direction rhs);

class Snake
{
public:
    Snake(Coordinates headSnake, Direction direction = Direction::ToTop, const int beginBodySize = 5) : direction_(direction)
    {
        bodySnake_.emplace_back(headSnake);
        for(int i = 1; i < beginBodySize; i++)
        {
            if(direction == Direction::ToTop)
            {
                auto lastSegment = bodySnake_.back();
                lastSegment.second--;
                bodySnake_.emplace_back(lastSegment);
            }
        }
    }
    Coordinates getHead() const { return bodySnake_.front(); }
    Coordinates getTail() const { return bodySnake_.back(); }
    std::list<Coordinates> getBody() const { return bodySnake_; }
    void move();
    void changeDirection(const Direction direction);
private:
    Direction direction_;
    std::list<Coordinates> bodySnake_;
};