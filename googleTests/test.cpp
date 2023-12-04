#include "pch.h"


#include "../Tetris2.0/grid.h"
#include "../Tetris2.0/grid.cpp"

#include "../Tetris2.0/block.h"

//#include "../Tetris/blocks.cpp"


#include "../Tetris2.0/game.h"


#include "../Tetris2.0/position.h"

#include "../Tetris2.0/color.h"
#include "../Tetris2.0/color.cpp"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

class GridTest :public testing::Test
{
protected:
    virtual void SetUp()
    {
        grid.Initialize();
    }
    virtual void TearDown()
    {
        //delete grid.grid;
    }

    Grid grid;
};

TEST_F(GridTest, HandlesZeroInput) {
    //Grid grid;
    //grid.Initialize();
    EXPECT_TRUE(grid.grid[0][0] == 0);
    //delete grid.grid;
};


