#include <gtest/gtest.h>
#include "../inc/Snake.hpp"
#include "../inc/Gameboard.hpp"

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
    SnakeTest() : headSnakeAtBegin{6,7}, snake(headSnakeAtBegin) {}

protected:
    const Coordinates headSnakeAtBegin;
    Snake snake;
};

TEST_F(SnakeTest, givenDefaultSnakeWhenCheckTailCoordinatesThenReturnFourCoordinatesBehind)
{
    auto actualTailCoordinates = snake.getTail();
    
    Coordinates expectedTailCoordinates = headSnakeAtBegin;
    expectedTailCoordinates.first += 4;

    EXPECT_EQ(expectedTailCoordinates, actualTailCoordinates);
}

TEST_F(SnakeTest, givenDefaultSnakeCoordinatesWhenMakeOneMoveCheckHeadAndTailCoordinates)
{
    snake.move();

    auto actualHeadCoordinates = snake.getHead();
    Coordinates expectedHeadCoordinates{5,7};
    auto actualTailCoordinates = snake.getTail();
    Coordinates expectedTailCoordinates{9,7};

    EXPECT_EQ(expectedHeadCoordinates, actualHeadCoordinates);
    EXPECT_EQ(expectedTailCoordinates, actualTailCoordinates);
}

TEST_F(SnakeTest, givenDefaultSnakeCoordinatesWhenMakeOneMoveAfterTurningLeftThenExpectHeadAtLeftField)
{
    Coordinates expectedHeadCoordinates(snake.getHead());
    expectedHeadCoordinates.second--;

    snake.changeDirection(Direction::ToLeft);
    snake.move();

    auto actualHeadCoordinates = snake.getHead();

    EXPECT_EQ(expectedHeadCoordinates, actualHeadCoordinates);
}

TEST_F(SnakeTest, givenDefaultSnakeCoordinatesWhenMakeTwoMovesAfterTurningRightThenExpectWholeBodyUpsiteDownLetterL)
{
    snake.changeDirection(Direction::ToRight);
    snake.move();
    snake.move();

    auto actualSnakeBody = snake.getBody();
    std::list<Coordinates> expectedSnakeBody{{6,9}, {6,8}, {6,7}, {7,7}, {8,7}};

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
    std::list<Coordinates> expectedSnakeBody{{8,8},{7,8},{6,8},{6,7},{7,7}};

    EXPECT_EQ(expectedSnakeBody, actualSnakeBody);
}

TEST_F(SnakeTest, givenDefaultSnakeCoordinatesWhenChangeDirectionToTheSameDirectionThatSnakeIsCurrentlyGoingDirectionDoesNotChange)
{
    snake.move();
    snake.changeDirection(Direction::ToBottom);
    snake.move();

    auto actualSnakeBody = snake.getBody();
    std::list<Coordinates> expectedSnakeBody{{4,7},{5,7},{6,7},{7,7},{8,7}};

    EXPECT_EQ(expectedSnakeBody, actualSnakeBody);
}

TEST(GameTest, givenSnakeInFrontOfFoodWhenSnakeMoveHisWholeBodyThenExpectIncrementedSizeByOne)
{
    const int kDimension{10};
    const int kSnakeBodySize{2};
    const int kHeadSize{1};
    Gameboard gameboard(kDimension, kDimension);

    Coordinates headSnake {kDimension/2, kDimension/2};
    Snake snake(headSnake, Direction::ToTop, kSnakeBodySize);

    gameboard.updateSnake(snake);

    Coordinates foodCoords(headSnake);
    foodCoords.first--;
    gameboard.addFoodAt(foodCoords);

    const int expectedBodySize = snake.getBody().size() + 1;
    for(int i = 0; i < kSnakeBodySize + kHeadSize; i++)
    {
        snake.move();
        gameboard.updateSnake(snake);
    }

    EXPECT_EQ(snake.getBody().size(), expectedBodySize);
}

TEST(GameTest, givenSnakeInFrontOfFoodWhenSnakeAteFoodAndMoveThreeTimesThenExpectSnakeIncrementedAtTail)
{
    const int dimension{10};
    const int beginBodySize{2};
    Gameboard gameboard(dimension, dimension);

    Coordinates headSnake {dimension/2, dimension/2};
    Snake snake(headSnake, Direction::ToTop, beginBodySize);
    gameboard.updateSnake(snake);

    Coordinates foodCoords(headSnake);
    foodCoords.first--;
    gameboard.addFoodAt(foodCoords);

    snake.move();
    gameboard.updateSnake(snake);

    snake.move();
    gameboard.updateSnake(snake);

    snake.move();
    gameboard.updateSnake(snake);

    std::vector<Coordinates> expectedSnake{{2,5}, {3,5}, {4,5}};

    for(auto coordinate : expectedSnake)
    {
        EXPECT_EQ(gameboard.checkFieldAt(coordinate.first,coordinate.second), FieldState::Snake);
    }
}
