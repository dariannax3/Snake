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
    if(direction_ == Direction::ToTop)
    {
        headSnake_.second++;
        tailSnake_.second++;
    }
    else
    {
        headSnake_.first--;
    }
}

void Snake::changeDirection(const Direction direction)
{
    direction_ = direction;
}