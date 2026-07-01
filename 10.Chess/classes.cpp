// #ifndef CLASSES_HPP
// #define CLASSES_HPP

#include <string>
#include <vector>

enum Color
{
    WHITE = 0,
    BLACK,
    NONE
};

enum PieceType
{
    PAWN = 0,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
    EMPTY
};

// type = {P, R, N, B, Q, K};
class Cell
{
public:
    int row;
    int col;
    Color color;
    PieceType type;

    Cell(int r, int c, Color colo, PieceType t) : row(r), col(c), color(colo), type(t) {};
};

// [Color]+[Piece]
class Board
{
private:
    std::vector<std::vector<Cell>> cells{};

public:
    bool isEmpty(Cell &location)
    {
        return location.type == EMPTY;
    }
    bool isEmpty(std::pair<int, int> &location)
    {
        return cells[location.first][location.second].type == EMPTY;
    }
    Color getColor(std::pair<int, int> &location)
    {
        return cells[location.first][location.second].color;
    }
    PieceType getTypePiece(std::pair<int, int> &location)
    {
        return cells[location.first][location.second].type;
    }

    // R N B Q K B N R .
    Board()
    {
        for (int i = 0; i < 8; i++)
        {
            std::vector<Cell> vC{};
            for (int j = 0; j < 8; j++)
            {
                Cell temp(i, j, NONE, EMPTY);
                vC.push_back(temp);
            }
            cells.push_back(vC);
        }

        for (int j = 0; j < 8; j++)
        {
            Cell temp(1, j, BLACK, PAWN);
            cells[1][j] = temp;
        }
        for (int j = 0; j < 8; j++)
        {
            Cell temp(6, j, WHITE, PAWN);
            cells[6][j] = temp;
        }

        cells[0][0] = Cell(0, 0, BLACK, ROOK);
        cells[0][1] = Cell(0, 1, BLACK, KNIGHT);
        cells[0][2] = Cell(0, 2, BLACK, BISHOP);
        cells[0][3] = Cell(0, 3, BLACK, QUEEN);
        cells[0][4] = Cell(0, 4, BLACK, KING);
        cells[0][5] = Cell(0, 5, BLACK, BISHOP);
        cells[0][6] = Cell(0, 6, BLACK, KNIGHT);
        cells[0][7] = Cell(0, 7, BLACK, ROOK);

        cells[7][0] = Cell(7, 0, WHITE, ROOK);
        cells[7][1] = Cell(7, 1, WHITE, KNIGHT);
        cells[7][2] = Cell(7, 2, WHITE, BISHOP);
        cells[7][3] = Cell(7, 3, WHITE, QUEEN);
        cells[7][4] = Cell(7, 4, WHITE, KING);
        cells[7][5] = Cell(7, 5, WHITE, BISHOP);
        cells[7][6] = Cell(7, 6, WHITE, KNIGHT);
        cells[7][7] = Cell(7, 7, WHITE, ROOK);
    };
    ~Board() {};
};

class State
{
public:
    // // Make sure to make every elements.
    Board board{};

    std::vector<std::pair<int, int>> kingPos = {{7, 4}, {0, 4}}; // White/ Black
    std::vector<std::vector<std::pair<int, int>>> piecesDirections = {
        {{-1, 1}, {-1, -1}},
        {{1, 1}, {1, -1}},
        {{1, 2}, {2, 1}, {-1, 2}, {-2, 1}, {-1, -2}, {-2, -1}, {1, -2}, {2, -1}},
        {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}},
        {{-1, 0}, {1, 0}, {0, -1}, {0, 1}},
        {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}}};

    bool canMove(Cell &moved)
    {
        std::pair<int, int> v = {moved.row - kingPos[moved.color].first, moved.col - kingPos[moved.color].second};
        int dirModel = -1; // 0NotHave/ 1direct/ 2Diagonal

        if (v.first == v.second || v.first == -v.second)
        {
            if (v.first < 0)
                v = {-v.first / v.first, -v.second / v.first};
            else
                v = {v.first / v.first, v.second / v.first};
            dirModel = 1;
        }
        else if (v.first == 0)
        {
            if (v.second > 0)
                v = {0, v.second / v.second};
            else
                v = {0, -v.second / v.second};
            dirModel = 0;
        }
        else if (v.second == 0)
        {
            if (v.first > 0)
                v = {0, v.first / v.first};
            else
                v = {0, -v.first / v.first};
            dirModel = 0;
        }

        std::pair<int, int> guess = {kingPos[moved.color].first + v.first, kingPos[moved.color].second + v.second};
        while (state.isValuable(guess))
        {
            if (board.isEmpty(guess))
            {
                guess.first += v.first;
                guess.second += v.second;
                continue;
            }
            if (board.getColor(guess) == moved.color)
                return false;
            else if
            {
                switch (dirModel)
                {
                case 0:
                    if (board.getTypePiece(guess) == QUEEN || board.getTypePiece(guess) == ROOK)
                        return true;
                    break;

                default:
                    if (board.getTypePiece(guess) == QUEEN || board.getTypePiece(guess) == Bishop)
                        return true;
                    break;
                }
            }
        }
        return false;
    }
    bool isKish(Color color)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < piecesDirections[i].size(); j++)
            {
                std::pair<int, int> loc = {kingPos[color].first + piecesDirections[i][j].first, kingPos[color].second + piecesDirections[i][j].second};
                while (state.isValuable(loc))
                {
                    if (board.isEmpty(loc))
                    {
                        loc.first += piecesDirections[i][j].first;
                        loc.second += piecesDirections[i][j].second;
                    }
                    else if (board.getColor(loc) == color)
                        break;
                    else
                        switch (i)
                        {
                        case 0, 1:
                            if (board.getTypePiece(loc) == 0)
                                return true;
                            break;
                        case 2:
                            if (board.getTypePiece(loc) == 1)
                                return true;
                            break;
                        case 3:
                            if (board.getTypePiece(loc) == 2 || board.getTypePiece(loc) == 4)
                                return true;
                            break;
                        case 4:
                            if (board.getTypePiece(loc) == 3 || board.getTypePiece(loc) == 4)
                                return true;
                            break;
                        case 5:
                            if (board.getTypePiece(loc) == 4)
                                return true;
                            break;
                        default:
                            break;
                        }

                    if (i / 3 < 1)
                        break;
                }
            }
        }
        return false;
    }
    bool isValuable(std::pair<int, int> location)
    {
        return (location.first < 8) && (location.first > -1) && (location.second < 8) && (location.second > -1);
    }
    bool isEmpty(std::pair<int, int> &location)
    {
        return board[location.first][location.second].type == EMPTY;
    }

    State() {};
    ~State() {};
};
State state{};
// Make sure to make every elements.

class Move
{
private:
    /* data */
public:
    std::pair<Cell, Cell> temperaryMove(Cell &first, Cell &second)
    {
        std::pair<Cell, Cell> out = {first, second};

        second.color = first.color;
        second.type = first.type;
        // ------------------------
        first.color = 2;
        first.type = 7;

        return 
    };

    Move(Cell first, Cell second)
    {
        second.color = first.color;
        second.type = first.type;
        // ------------------------
        first.color = 2;
        first.type = 7;
    };
    ~Move();
};

class Piece
{
protected:
    char sign;
    int row;
    int col;

public:
    Piece(char s) : sign(s) {};
    virtual ~Piece() = default;

    char getSign() const { return sign; }

    virtual std::vector<std::pair<int, int>> getLegalMoves(Cell &cellPiece) const = 0;
};

class King : public Piece
{
public:
    King() : Piece('K') {}

    static const int directions[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    std::vector<std::pair<int, int>> getLegalMoves(Cell &cellPiece) const override
    {
        std::vector<std::pair<int, int>> options;
        for (int i = 0; i < directions.size(); ++i)
        {
            std::pair<int, int> guss;
            guss = {cellPiece.row + directions[i][0], cellPiece.col + directions[i][1]};

            if (state.isValuable(guss))
            {
                std::pair<int, int> temp = state.kingPos[cellPiece.color];
                state.kingPos[k.color] = guss;
                // **********
                // Move Piece
                if (!state.isKish(k.color))
                {
                    options.push_back(guss);
                }
                // move back piece
                // ***************
                state.kingPos[cellPiece.color] = temp;
            }
        }
        return options;
    }
};

class Queen : public Piece
{
public:
    Queen() : Piece('Q') {};

    std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    std::vector<std::pair<int, int>> getLegalMoves(Cell &cellPiece) const override
    {
        std::vector<std::pair<int, int>> options{};

        for (int i = 0; directions.size(); i++)
        {
            std::pair<int, int> guss = {cellPiece.row + directions[i].first, cellPiece.col + directions[i].second};
            while (state.isValuable(guss))
            {
                if (state.board.isEmpty(guss))
                {
                    // *************
                    // Move temprary
                    if (state.canMove(cellPiece))
                        options.push_back(guss);
                    // Move back after checking
                    // ************************
                }
                else if (state.board.getColor(guss) == cellPiece.color)
                    break;
                else
                {
                    // *************
                    // Move temprary
                    if (state.canMove(cellPiece))
                        options.push_back(guss);
                    // Move back after checking
                    // ************************
                    break;
                }
            }
        }

        return options;
    };
};

class Rook : public Piece
{
public:
    Rook() : Piece('R') {};

    std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    std::vector<std::pair<int, int>> getLegalMoves(Cell &cellPiece) const override
    {
        std::vector<std::pair<int, int>> options{};

        for (int i = 0; directions.size(); i++)
        {
            std::pair<int, int> guss = {cellPiece.row + directions[i].first, cellPiece.col + directions[i].second};
            while (state.isValuable(guss))
            {
                if (state.board.isEmpty(guss))
                {
                    // *************
                    // Move temprary
                    if (state.canMove(cellPiece))
                        options.push_back(guss);
                    // Move back after checking
                    // ************************
                }
                else if (state.board.getColor(guss) == cellPiece.color)
                    break;
                else
                {
                    // *************
                    // Move temprary
                    if (state.canMove(cellPiece))
                        options.push_back(guss);
                    // Move back after checking
                    // ************************
                    break;
                }
            }
        }

        return options;
    };
};

class Bishop : public Piece
{
public:
    Bishop() : Piece('B') {};

    std::vector<std::pair<int, int>> directions = {{1, 1}, {-1, 1}, {-1, -1}, {1, -1}};

    std::vector<std::pair<int, int>> getLegalMoves(Cell &cellPiece) const override
    {
        std::vector<std::pair<int, int>> options{};

        for (int i = 0; directions.size(); i++)
        {
            std::pair<int, int> guss = {cellPiece.row + directions[i].first, cellPiece.col + directions[i].second};
            while (state.isValuable(guss))
            {
                if (state.board.isEmpty(guss))
                {
                    // *************
                    // Move temprary
                    if (state.canMove(cellPiece))
                        options.push_back(guss);
                    // Move back after checking
                    // ************************
                }
                else if (state.board.getColor(guss) == cellPiece.color)
                    break;
                else
                {
                    // *************
                    // Move temprary
                    if (state.canMove(cellPiece))
                        options.push_back(guss);
                    // Move back after checking
                    // ************************
                    break;
                }
            }
        }

        return options;
    };
};

class Knight : public Piece
{
public:
    Knight() : Piece('N') {};

    std::vector<std::pair<int, int>> directions = {{1, 2}, {2, 1}, {-1, 2}, {-2, 1}, {-1, -2}, {-2, -1}, {1, -2}, {2, -1}};

    std::vector<std::pair<int, int>> getLegalMoves(Cell &cellPiece) const override
    {
        std::vector<std::pair<int, int>> options{};

        for (int i = 0; directions.size(); i++)
        {
            std::pair<int, int> guss = {cellPiece.row + directions[i].first, cellPiece.col + directions[i].second};
            if (state.isValuable(guss))
            {
                if (state.board.isEmpty(guss))
                {
                    // *************
                    // Move temprary
                    if (state.canMove(cellPiece))
                        options.push_back(guss);
                    // Move back after checking
                    // ************************
                }
                else if (state.board.getColor(guss) == cellPiece.color)
                    break;
                else
                {
                    // *************
                    // Move temprary
                    if (state.canMove(cellPiece))
                        options.push_back(guss);
                    // Move back after checking
                    // ************************
                    break;
                }
            }
        }

        return options;
    };
};

class Pawn : public Piece
{
public:
    Pawn() : Piece('P') {};

    std::vector<std::pair<int, int>> directions = {{-1, 1}, {-1, -1}};

    std::vector<std::pair<int, int>> getLegalMoves(Cell &cellPiece) const override const
    {
        std::vector<std::pair<int, int>> options{};

        for (int i = 0; directions.size(); i++)
        {
            std::pair<int, int> guss = {cellPiece.row + directions[i].first, cellPiece.col + directions[i].second};
            if (state.isValuable(guss))
            {
                if (state.board.isEmpty(guss))
                {
                    // *************
                    // Move temprary
                    if (state.canMove(cellPiece))
                        options.push_back(guss);
                    // Move back after checking
                    // ************************
                }
                else if (state.board.getColor(guss) == cellPiece.color)
                    break;
                else
                {
                    // *************
                    // Move temprary
                    if (state.canMove(cellPiece))
                        options.push_back(guss);
                    // Move back after checking
                    // ************************
                    break;
                }
            }
        }

        return options;
    };
};

// #endif
