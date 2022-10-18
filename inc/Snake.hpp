#pragma once
#include <utility>
#include <list>

using Coordinates = std::pair<int,int>;

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
    Snake(Coordinates headSnake, Direction direction = Direction::ToTop, const int beginBodySize = 5);

    Coordinates getHead() const { return bodySnake_.front(); }
    Coordinates getTail() const { return bodySnake_.back(); }
    Coordinates getPrevTail() const { return prevTail_; }
    std::list<Coordinates> getBody() const { return bodySnake_; }

    void move();
    void changeDirection(const Direction direction);
    void increaseSnake(const Coordinates newTail);

private:
    Direction direction_;
    Coordinates prevTail_;
    std::list<Coordinates> bodySnake_;
};