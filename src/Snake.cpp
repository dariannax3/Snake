#include "../inc/Snake.hpp"

bool isInRange(int begin, int end, int value)
{
    return begin <= value && value < end; 
}

FieldState Gameboard::checkFieldAt(const int givenWidth, const int givenHeight)
{
    if(isInRange(0,getHeight(), givenHeight) &&
       isInRange(0, getWidth(), givenWidth))
    {
        return FieldState::Empty;
    }
    return FieldState::Wall;
}

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
