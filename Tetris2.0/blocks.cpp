#include "block.h"
#include "position.h"

class LBlock :public Block
{
public:
    LBlock() {
        id = 1;

        height = { 2, 3, 2, 3 };
        length = { 3, 2, 3, 2 };
        leftOffset = { 2, 0, 0, 1 };
        rightOffset = { 0, 1, 2, 0 };
        irregularities = { {0, 0, 0}, {0, 0}, {1, 0, 0}, {0, 2} };

        cells[0] = { Position(0, 2), Position(1, 0), Position(1, 1), Position(1, 2) };
        cells[1] = { Position(0, 1), Position(1, 1), Position(2, 1), Position(2, 2) };
        cells[2] = { Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 0) };
        cells[3] = { Position(0, 1), Position(0, 0), Position(1, 1), Position(2, 1) };
        Move(0, 3);
    }
};

class JBlock : public Block
{
public:
    JBlock()
    {
        id = 2;

        height = { 2, 3, 2, 3 };
        length = { 3, 2, 3, 2 };
        leftOffset = { 0, 1, 2, 0 };
        rightOffset = { 2, 0, 0, 1 };
        irregularities = { {0, 0, 0}, {0, 0}, {0, 0, 1}, {2, 0} };

        cells[0] = { Position(0, 0), Position(1, 0), Position(1, 1), Position(1, 2) };
        cells[1] = { Position(0, 1), Position(0, 2), Position(1, 1), Position(2, 1) };
        cells[2] = { Position(1, 2), Position(1, 1), Position(1, 0), Position(2, 2) };
        cells[3] = { Position(2, 1), Position(1, 1), Position(2, 0), Position(0, 1) };
        Move(0, 3);
    }
};

class IBlock : public Block
{
public:
    IBlock()
    {
        id = 3;

        height = { 1, 4, 1, 4 };
        length = { 4, 1, 4, 1 };
        leftOffset = { 0, 0, 3, 0 };
        rightOffset = { 2, 0, 0, 1 };
        irregularities = { {0, 0, 0, 0}, {0}, {0, 0, 0, 0}, {0} };

        cells[0] = { Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 3) };
        cells[1] = { Position(3, 2), Position(2, 2), Position(1, 2), Position(0, 2) };
        cells[2] = { Position(2, 3), Position(2, 2), Position(2, 1), Position(2, 0) };
        cells[3] = { Position(3, 1), Position(2, 1), Position(1, 1), Position(0, 1) };
        Move(-1, 3);
    }
};

class OBlock : public Block
{
public:
    OBlock()
    {
        id = 4;

        height = { 2 };
        length = { 2 };
        leftOffset = { 0 };
        rightOffset = { 1 };
        irregularities = { { 0, 0 } };

        cells[0] = { Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1) };
        Move(0, 4);
    }
};

class SBlock : public Block
{
public:
    SBlock()
    {
        id = 5;

        height = { 2, 3, 2, 3 };
        length = { 3, 2, 3, 2 };
        leftOffset = { 1, 0, 1, 1 };
        rightOffset = { 1, 1, 1, 0 };
        irregularities = { {0, 0, -1}, {0, 1}, {0, 0, -1}, {-1, 0} };

        cells[0] = { Position(1, 1), Position(0, 2), Position(1, 0), Position(0, 1) };
        cells[1] = { Position(1, 1), Position(0, 1), Position(1, 2), Position(2, 2) };
        cells[2] = { Position(2, 1), Position(1, 2), Position(2, 0), Position(1, 1) };
        cells[3] = { Position(1, 1), Position(1, 0), Position(0, 0), Position(2, 1) };
        Move(0, 3);
    }
};

class TBlock : public Block
{
public:
    TBlock()
    {
        id = 6;

        height = { 2, 3, 2, 3 };
        length = { 3, 2, 3, 2 };
        leftOffset = { 0, 0, 1, 1 };
        rightOffset = { 2, 1, 1, 0 };
        irregularities = { {0, 0, 0}, {0, -1}, {-1, 0, -1}, {-1, 0} };

        cells[0] = { Position(1, 0), Position(0, 1), Position(1, 1), Position(1, 2) };
        cells[1] = { Position(2, 1), Position(1, 1), Position(1, 2), Position(0, 1) };
        cells[2] = { Position(2, 1), Position(1, 1), Position(1, 2), Position(1, 0) };
        cells[3] = { Position(2, 1), Position(1, 0), Position(1, 1), Position(0, 1) };
        Move(0, 3);
    }
};

class ZBlock : public Block
{
public:
    ZBlock()
    {
        id = 7;

        height = { 2, 3, 2, 3 };
        length = { 3, 2, 3, 2 };
        leftOffset = { 1, 0, 2, 0 };
        rightOffset = { 1, 1, 0, 1 };
        irregularities = { {-1, 0, 0}, {0, -1}, {-1, 0, 0}, {0, -1} };

        cells[0] = { Position(1, 1), Position(0, 1), Position(0, 0), Position(1, 2) };
        cells[1] = { Position(2, 1), Position(1, 1), Position(1, 2), Position(0, 2) };
        cells[2] = { Position(2, 2), Position(1, 1), Position(2, 1), Position(1, 0) };
        cells[3] = { Position(2, 0), Position(1, 0), Position(1, 1), Position(0, 1) };
        Move(0, 3);
    }
};