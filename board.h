#include "GameConfig.h"
#include "tetromino.h"

#ifndef BOARD_H
#define BOARD_H

class Board
{

private:
    // 게임 판을 나타내는 배열
    // board[x][y]가 true 인 경우 x, y 위치에 고정된 블록이 존재하는 것을 의미한다
    bool board_[GameConfig::BOARD_WIDTH][GameConfig::BOARD_HEIGHT] = {false};

public:
    // 테트로미노의 좌상단 기준 x, y 위치에 블록이 있는지 여부를 나타내는 함수
    bool check(int x, int y) const
    {
        return board_[x][y];
    }

    // board에 tetriomonio 추가
    void addTetromino(Tetromino tetromino, int boardX, int boardY);

    // board 줄 지우기
    int clearFullLines();

    // 특정 위치에 값이 비어 있는지 확인
    bool isEmpty(Tetromino tetromino, int boardX, int boardY);

    // board에서 shadow가 표기될 y 좌표 리턴
    // 검사하기 시작할 y 좌표를 지정해줄 수 있음
    int shadowTetromino(Tetromino tetromino, int (&tetrominoMargin)[4], int boardX, int boardY = 0);
};

#endif