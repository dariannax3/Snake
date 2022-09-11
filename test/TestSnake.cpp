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
    snake.changeDirection(Direction::ToLeft);
    snake.move();

    auto actualHeadCoordinates = snake.getHead();
    Coordinates expectedHeadCoordinates{2,4};

    EXPECT_EQ(expectedHeadCoordinates, actualHeadCoordinates);
}

TEST_F(SnakeTest, givenDefaultSnakeCoordinatesWhenMakeTwoMovesAfterTurningRightThenExpectWholeBodyUpsiteDownLetterL)
{
    snake.changeDirection(Direction::ToRight);
    snake.move();
    snake.move();

    auto actualSnakeBody = snake.getBody();
    std::list<Coordinates> expectedSnakeBody{{5,4},{4,4},{3,4},{3,3},{3,2}}; 

    EXPECT_EQ(expectedSnakeBody, actualSnakeBody);
}

TEST_F(SnakeTest, givenDefaultSnakeCoordinatesWhenMakeThreeMovesAfterTurningRightAndBottomThenExpectWholeBodyReversedLetterP)
{
    snake.changeDirection(Direction::ToRight);
    snake.move();
    snake.changeDirection(Direction::ToBottom);
    snake.move();
    snake.move();

    auto actualSnakeBody = snake.getBody();
    std::list<Coordinates> expectedSnakeBody{{4,2},{4,3},{4,4},{3,4},{3,3}}; 

    EXPECT_EQ(expectedSnakeBody, actualSnakeBody);
}

TEST_F(SnakeTest, givenDefaultSnakeCoordinatesWhenChangeDirectionToTheSameDirectionThatSnakeIsCurrentlyGoingDirectionDoesNotChange)
{
    snake.move();
    snake.changeDirection(Direction::ToBottom);
    snake.move();

    auto actualSnakeBody = snake.getBody();
    std::list<Coordinates> expectedSnakeBody{{3,6},{3,5},{3,4},{3,3},{3,2}};

    EXPECT_EQ(expectedSnakeBody, actualSnakeBody);
}

