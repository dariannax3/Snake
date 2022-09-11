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

void Snake::changeDirection(const Direction direction)
{
    direction_ = direction;
}