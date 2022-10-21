#include "../inc/Gameboard.hpp"

bool isInRange(int begin, int end, int value)
{
    return begin <= value && value < end; 
}

void displayGameboard(const std::vector<std::vector<FieldState>>& matrix)
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


FieldState Gameboard::checkFieldAt(const int givenWidth, const int givenHeight) const
{
    if(isInRange(0, getHeight(), givenHeight) &&
       isInRange(0, getWidth(), givenWidth))
    {
        return gameboard_[givenWidth][givenHeight];
    }
    return FieldState::Wall;
}

void Gameboard::initializeDefaultGameboard(int width, int height)
{
    for (int i = 0; i < width; i++)
    {
        std::vector<FieldState> row;
        for (int j = 0; j < height; j++) {
            row.push_back(FieldState::Empty);
        }
        gameboard_.push_back(row);
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