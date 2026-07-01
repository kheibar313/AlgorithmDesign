// #ifndef CLASSES_HPP
// #define CLASSES_HPP

#include <string>
#include <vector>

// *After change NONE=-1
// Color = {WHITE, BLACK, NONE}
enum class Color
{
    WHITE = 0,
    BLACK,
    NONE
};

// *After change EMPTY=-1
// PieceType = {P, N, B, R, Q, K, E};
enum class PieceType
{
    PAWN = 0,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
    EMPTY
};

// Color = {WHITE, BLACK, NONE}
// PieceType = {P, N, B, R, Q, K, E};
class Cell
{
public:
    Color color;
    PieceType type;

    Cell(Color colo, PieceType t) : color(colo), type(t) {};
};

using pos = std::pair<int, int>;
using vec = std::pair<int, int>;

class Board
{
private:
    std::vector<std::vector<Cell>> cells{};

public:
    // {WhitePos, BlackPos}
    std::vector<pos> kingPos = {{7, 4}, {0, 4}};
    // Inp: Pos, out: (empty) ? true : false;
    bool isEmpty(pos &location)
    {
        return cells[location.first][location.second].type == EMPTY;
    }
    // Inp: Pos, out: Color
    Color getColor(pos &location)
    {
        return cells[location.first][location.second].color;
    }
    // Inp: Pos, out: PieceType
    PieceType getTypePiece(pos &location)
    {
        return cells[location.first][location.second].type;
    }
    // Inp: Pos, out: Cell, location on pos
    Cell &getCell(pos &location)
    {
        return cells[location.first][location.second];
    }
    // Set Cell(c) on location(l)
    bool setCell(pos &location, Cell &c)
    {
        if (!isValidPosition(location))
            return false;
        cells[location.first][location.second] = c;
        return;
    }
    // If inp(pos) is valueable rtn true.
    bool isValidPosition(pos location)
    {
        return (location.first < 8) && (location.first > -1) && (location.second < 8) && (location.second > -1);
    }
    // Make board for Start game.
    Board()
    {
        // Make list of board's cells.
        for (int i = 0; i < 8; i++)
        {
            std::vector<Cell> vC{};
            for (int j = 0; j < 8; j++)
            {
                Cell temp(NONE, EMPTY);
                vC.push_back(temp);
            }
            cells.push_back(vC);
        }
        // Make Pawn:
        for (int j = 0; j < 8; j++)
        {
            Cell temp(BLACK, PAWN);
            cells[1][j] = temp;
        }
        for (int j = 0; j < 8; j++)
        {
            Cell temp(WHITE, PAWN);
            cells[6][j] = temp;
        }
        // Make other Piece Black:
        cells[0][0] = Cell(BLACK, ROOK);
        cells[0][1] = Cell(BLACK, KNIGHT);
        cells[0][2] = Cell(BLACK, BISHOP);
        cells[0][3] = Cell(BLACK, QUEEN);
        cells[0][4] = Cell(BLACK, KING);
        cells[0][5] = Cell(BLACK, BISHOP);
        cells[0][6] = Cell(BLACK, KNIGHT);
        cells[0][7] = Cell(BLACK, ROOK);
        // Make other Piece White:
        cells[7][0] = Cell(WHITE, ROOK);
        cells[7][1] = Cell(WHITE, KNIGHT);
        cells[7][2] = Cell(WHITE, BISHOP);
        cells[7][3] = Cell(WHITE, QUEEN);
        cells[7][4] = Cell(WHITE, KING);
        cells[7][5] = Cell(WHITE, BISHOP);
        cells[7][6] = Cell(WHITE, KNIGHT);
        cells[7][7] = Cell(WHITE, ROOK);
    };
    ~Board() {};
};

class Move
{
private:
    /* data */
public:
    /*
    std::pair<Cell, Cell> temperaryMove(Cell &first, Cell &second)
    {
        std::pair<Cell, Cell> out = {first, second};

        second.color = first.color;
        second.type = first.type;
        // ------------------------
        first.color = NONE;
        first.type = EMPTY;

        return out;
    };
    */

    Board board{};

    bool simpleMove(pos &first, pos &second)
    {
        if (board.getTypePiece(first) == KING)
        {
            board.kingPos[board.getColor(first)] = second;
        }
        board.setCell(second, board.getCell(first));
        Cell temp = Cell(NONE, EMPTY);
        board.setCell(first, temp);
        return true;
    };

    bool simpleMove(Cell first, Cell second)
    {
        second.color = first.color;
        second.type = first.type;
        // ------------------------
        first.color = NONE;
        first.type = EMPTY;
    };

    Move() {};
    ~Move() {};
};

class State
{
public:
    // Make sure to make every elements.
    Board board{};
    // Make sure to make every elements.
    Move move{};
    // {isKishWhite, isKishBlack}
    std::vector<bool> isKishVec = {false, false};
    // Every Piece directions: {blackPawn, whitePawn, knight, bishop, rook, Queen_&KING}
    std::vector<std::vector<std::pair<int, int>>> piecesDirections = {
        {{-1, 1}, {-1, -1}},
        {{1, 1}, {1, -1}},
        {{1, 2}, {2, 1}, {-1, 2}, {-2, 1}, {-1, -2}, {-2, -1}, {1, -2}, {2, -1}},
        {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}},
        {{-1, 0}, {1, 0}, {0, -1}, {0, 1}},
        {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}}};

    // 1. If color iskish, move can unkish?
    // 2. If move, color change to kish?
    bool canMove(pos &first, pos second)
    {
        // vector of king and first
        vec v = {first.first - board.kingPos[board.getColor(first)].first,
                 first.second - board.kingPos[board.getColor(first)].second};
        // 0NotHave / 1.+ / 2.x
        int dirModel = 0;
        // Not change to kish
        bool whileBreaker = false;
        if (v.first == v.second || v.first == -v.second)
        {
            v = {v.first / v.first, v.second / v.first};
            if (v.first < 0)
                v = {-v.first / v.first, -v.second / v.first};
            dirModel = 2;
        }
        else if (v.first == 0)
        {
            v = {0, -1};
            if (v.second > 0)
                v = {0, 1};
            dirModel = 1;
        }
        else if (v.second == 0)
        {
            v = {0, -1};
            if (v.first > 0)
                v = {0, 1};
            dirModel = 1;
        }
        else
        {
            // Flag for while to break.
            whileBreaker = true;
        }
        // A guss that can تهدید king.
        pos guess = {board.kingPos[board.getColor(first)].first + v.first, board.kingPos[board.getColor(first)].second + v.second};
        // Make sure well work while condition.
        while (board.isValidPosition(guess) && !whileBreaker && board.getTypePiece(first) != KING)
        {
            if (board.isEmpty(guess))
            {
                guess.first += v.first;
                guess.second += v.second;
                continue;
            }
            if (board.getColor(guess) == board.getColor(first))
                break;
            else
            {
                switch (dirModel)
                {
                case 1:
                    if (board.getTypePiece(guess) == QUEEN || board.getTypePiece(guess) == ROOK)
                        return false;
                    break;

                case 2:
                    if (board.getTypePiece(guess) == QUEEN || board.getTypePiece(guess) == BISHOP)
                        return false;
                    break;

                default:
                    break;
                }
            }
        }

        if (!isKishVec[board.getColor(first)] && board.getTypePiece(first) != KING)
            return true;

        // Temperary Move:
        Cell tempSecond = board.getCell(second);
        move.simpleMove(first, second);
        if (isKish(board.getColor(second)))
        {
            move.simpleMove(second, first);
            board.setCell(second, tempSecond);
            return false;
        }
        return true;
    };

    bool isKish(Color color)
    {
        // Loop on every Piece exept
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < piecesDirections[i].size(); j++)
            {
                pos loc = {board.kingPos[color].first + piecesDirections[i][j].first, board.kingPos[color].second + piecesDirections[i][j].second};
                while (board.isValidPosition(loc))
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
                        case 0:
                            if (color == WHITE)
                            {
                                if (board.getTypePiece(loc) == PAWN)
                                    return true;
                            }
                            break;
                        case 1:
                            if (color == BLACK)
                            {
                                if (board.getTypePiece(loc) == PAWN)
                                    return true;
                            }
                            break;
                        case 2:
                            if (board.getTypePiece(loc) == KNIGHT)
                                return true;
                            break;
                        case 3:
                            if (board.getTypePiece(loc) == BISHOP || board.getTypePiece(loc) == QUEEN)
                                return true;
                            break;
                        case 4:
                            if (board.getTypePiece(loc) == ROOK || board.getTypePiece(loc) == QUEEN)
                                return true;
                            break;
                        case 5:
                            if (board.getTypePiece(loc) == KING)
                                return true;
                            break;
                        default:
                            break;
                        }

                    if (i < 3 || i == 5)
                        break;
                }
            }
        }
        return false;
    };

    State() {};
    ~State() {};
};

State state{};
// Make sure to make every elements.

class Piece
{
protected:
    char sign;
    int row;
    int col;

public:
    Piece(char s) : sign(s) {};
    virtual ~Piece() = default;

    Board board{};

    char getSign() const { return sign; }

    virtual std::vector<pos> getLegalMoves(pos &location) const = 0;
};

class King : public Piece
{
public:
    King() : Piece('K') {}

    std::vector<vec> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    std::vector<pos> getLegalMoves(pos &location) const override
    {
        std::vector<pos> options;
        for (int i = 0; i < directions.size(); ++i)
        {
            pos guss;
            guss = {location.first + directions[i].first, location.second + directions[i].second};

            if (board.isValidPosition(guss))
            {
                pos temp = board.kingPos[board.getColor(location)];
                board.kingPos[k.color] = guss;
                // **********
                // Move Piece
                if (!state.isKish(k.color))
                {
                    options.push_back(guss);
                }
                // move back piece
                // ***************
                board.kingPos[cellPiece.color] = temp;
            }
        }
        return options;
    }
};

class Queen : public Piece
{
public:
    Queen() : Piece('Q') {};

    std::vector<vec> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    std::vector<pos> getLegalMoves(pos &location) const override
    {
        std::vector<pos> options{};

        for (int i = 0; directions.size(); i++)
        {
            pos guss = {cellPiece.row + directions[i].first, cellPiece.col + directions[i].second};
            while (state.isVisValidPositionaluable(guss))
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

    std::vector<vec> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    std::vector<pos> getLegalMoves(pos &location) const override
    {
        std::vector<pos> options{};

        for (int i = 0; directions.size(); i++)
        {
            pos guss = {cellPiece.row + directions[i].first, cellPiece.col + directions[i].second};
            while (state.isValidPosition(guss))
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

    std::vector<vec> directions = {{1, 1}, {-1, 1}, {-1, -1}, {1, -1}};

    std::vector<pos> getLegalMoves(pos &location) const override
    {
        std::vector<pos> options{};

        for (int i = 0; directions.size(); i++)
        {
            pos guss = {cellPiece.row + directions[i].first, cellPiece.col + directions[i].second};
            while (state.isValidPosition(guss))
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

    std::vector<vec> directions = {{1, 2}, {2, 1}, {-1, 2}, {-2, 1}, {-1, -2}, {-2, -1}, {1, -2}, {2, -1}};

    std::vector<pos> getLegalMoves(pos &location) const override
    {
        std::vector<pos> options{};

        for (int i = 0; directions.size(); i++)
        {
            spos guss = {cellPiece.row + directions[i].first, cellPiece.col + directions[i].second};
            if (state.isValidPosition(guss))
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

    std::vector<pos> getLegalMoves(pos &location) const override
    {
        std::vector<pos> options{};

        for (int i = 0; directions.size(); i++)
        {
            pos guss = {cellPiece.row + directions[i].first, cellPiece.col + directions[i].second};
            if (state.isValidPosition(guss))
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
