#include "../inc/Gameboard.hpp"

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

void Gameboard::initializeDefaultGameboard()
{
    for (int i = 0; i < width_; i++)
    {
        std::vector<FieldState> v;
        for (int j = 0; j < height_; j++) {
            v.push_back(FieldState::Empty);
        }
        gameboard_.push_back(v);
    }
}



void Gameboard::updateSnake(Snake& snake)
{
    std::list<Coordinates> snakeBody = snake.getBody();
    gameboard_[snake.getPrevTail().first][snake.getPrevTail().second] = FieldState::Empty;

    for(auto el : snakeBody)
    {      
        if(gameboard_[el.first][el.second] == FieldState::Food)
        {
            snake.increaseSnake(std::pair<int, int>(el.first,el.second));
        }
        gameboard_[el.first][el.second] = FieldState::Snake;
    }
}

void Gameboard::addFoodAt(Coordinates newFood)
{
    gameboard_[newFood.first][newFood.second] = FieldState::Food;
}