#include "Board.h"

void Board::addTetromino(Tetromino tetromino, int boardX, int boardY)
{
    int tetroSize = tetromino.size();
    for (int i = 0; i < tetroSize; i++)
    {
        for (int j = 0; j < tetroSize; j++)
        {
            if (tetromino.check(i, j))
            {
                board_[boardX + i][boardY + j] = true;
            }
        }
    }
}

int Board::clearFullLines()
{
    int score_ = 0;
    for (int y = 0; y < GameConfig::BOARD_HEIGHT; y++)
    {
        bool lineFull = true;
        for (int x = 0; x < GameConfig::BOARD_WIDTH; x++)
        {
            if (!board_[x][y])
            {
                lineFull = false;
                break; // 행이 다 차 있지 않으면 반복 중단
            }
        }

        if (lineFull) // 줄이 차 있으면 줄 지우기
        {
            // 줄이 꽉 차면 줄을 비우고 그 위에 있는 모든 항목을 아래로 이동
            for (int yy = y; yy > 0; yy--)
            {
                for (int xx = 0; xx < GameConfig::BOARD_WIDTH; xx++)
                {
                    board_[xx][yy] = board_[xx][yy - 1]; // 행을 아래로 이동
                }
            }

            // 맨 위 행을 비워두도록 설정
            for (int xx = 0; xx < GameConfig::BOARD_WIDTH; xx++)
            {
                board_[xx][0] = false;
            }

            // 줄이 지워졌을 때, 
            // 루프의 다음 반복에서 이 행을 다시 확인하기 위해 y를 감소
            y--;

            score_++;
        }
    }

    return score_;
}

bool Board::isEmpty(Tetromino tetromino, int boardX, int boardY)
{
    int tetroSize = tetromino.size();
    for (int i = 0; i < tetroSize; i++)
    {
        for (int j = 0; j < tetroSize; j++)
        {
            if (tetromino.check(i, j))
            {
                if (board_[boardX + i][boardY + j])
                {
                    return false;
                }
            }
        }
    }
    return true;
}

int Board::shadowTetromino(Tetromino tetromino, int (&tetrominoMargin)[4], int boardX, int boardY)
{
    int _shadowPosY = GameConfig::BOARD_HEIGHT - tetromino.size() + tetrominoMargin[3];

    for (int i = boardY; i < GameConfig::BOARD_HEIGHT - tetromino.size() + tetrominoMargin[3] + 1; i++)
    {
        if (isEmpty(tetromino, boardX, i))
        {
            _shadowPosY = i;
        }
        else
        {
            break;
        }
    }
    return _shadowPosY;
}
