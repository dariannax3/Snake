#include "../inc/Snake.hpp"
#include <iostream>

void Snake::move()
{
    auto newHead = getHead();

    
    if(direction_ == Direction::ToTop)
    {
        newHead.second++;
    }
    else if(direction_ == Direction::ToBottom)
    {
        newHead.second--;
    }
    else if(direction_ == Direction::ToLeft)
    {
        newHead.first--;
    }
    else if(direction_ == Direction::ToRight)
    {
        newHead.first++;
    }

    bodySnake_.push_front(newHead);
    prevTail_ = bodySnake_.back();
    bodySnake_.pop_back();
}

bool isOpposite(Direction lhs, Direction rhs)
{
    return (rhs == Direction::ToBottom && lhs == Direction::ToTop) ||
           (rhs == Direction::ToTop && lhs == Direction::ToBottom) ||
           (rhs == Direction::ToRight && lhs == Direction::ToLeft) ||
           (rhs == Direction::ToLeft && lhs == Direction::ToRight);
}

void Snake::changeDirection(const Direction direction)
{
    if(not isOpposite(direction, direction_))
    {
        direction_ = direction;
    }
}

void Snake::increaseSnake(const Coordinates newTail)
{
    bodySnake_.emplace_back(newTail);
}