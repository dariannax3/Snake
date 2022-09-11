#include <gtest/gtest.h>
#include "../inc/Snake.hpp"

using namespace testing;

class GameboardTest : public ::Test 
{
protected:
    int width{10};
    int height{10};
    Gameboard gameboard{width,height};
};

TEST_F(GameboardTest, generateGameboardWithGivenSize)
{
    EXPECT_EQ(gameboard.getWidth(), width);
    EXPECT_EQ(gameboard.getHeight(), height);
}

TEST_F(GameboardTest, givenDefaultGameboardWhenCheckTheFieldOutOfBoardThenReturnWallState)
{
    auto expectedState = FieldState::Wall;

    EXPECT_EQ(expectedState, gameboard.checkFieldAt(width, height + 1));
}

TEST_F(GameboardTest, givenDefaultGameboardWhenCheckTheFieldOutOfBoardWidthThenReturnWallState)
{
    auto expectedState = FieldState::Wall;

    EXPECT_EQ(expectedState, gameboard.checkFieldAt(-1, height));
}

class SnakeTest : public ::Test 
{
public: 
    SnakeTest() : headSnakeAtBegin{3,4}, snake(headSnakeAtBegin) {}

protected:
    const Coordinates headSnakeAtBegin;
    Snake snake;
};

TEST_F(SnakeTest, givenDefaultSnakeWhenCheckTailCoordinatesThenReturnFourCoordinatesBehind)
{
    auto actualTailCoordinates = snake.getTail();
    
    Coordinates expectedTailCoordinates = headSnakeAtBegin;
    expectedTailCoordinates.second -= 4;

    EXPECT_EQ(expectedTailCoordinates, actualTailCoordinates);
}

TEST_F(SnakeTest, givenDefaultSnakeCoordinatesWhenMakeOneMoveCheckHeadAndTailCoordinates)
{
    snake.move();

    auto actualHeadCoordinates = snake.getHead();
    Coordinates expectedHeadCoordinates{3,5};
    auto actualTailCoordinates = snake.getTail();
    Coordinates expectedTailCoordinates{3,1};

    EXPECT_EQ(expectedHeadCoordinates, actualHeadCoordinates);
    EXPECT_EQ(expectedTailCoordinates, actualTailCoordinates);
}

TEST_F(SnakeTest, givenDefaultSnakeCoordinatesWhenMakeOneMoveAfterTurningLeftThenExpectHeadAtLeftField)
{
    Direction turnLeft{Direction::ToLeft};
    
    snake.changeDirection(turnLeft);
    snake.move();

    auto actualHeadCoordinates = snake.getHead();
    Coordinates expectedHeadCoordinates{2,4};

    EXPECT_EQ(expectedHeadCoordinates, actualHeadCoordinates);
}

TEST_F(SnakeTest, givenDefaultSnakeCoordinatesWhenMakeTwoMovesAfterTurningRightThenExpectWholeBodyUpsiteDownLetterL)
{
    Direction turnLeft{Direction::ToRight};
    
    snake.changeDirection(turnRight);
    snake.move();
    snake.move();

    auto actualSnakeBody = snake.getBody();
    std::vector<Coordinates> expectedSnakeBody{{5,4},{4,4},{3,4},{3,3},{3,2}}; 

    EXPECT_EQ(expectedSnakeBody, actualSnakeBody);
}