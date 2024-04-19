#include "game.h"
#include "console/console.h"
#include "GameConfig.h"
#include "tetromino.h"
#include "Timer.h"
#include "Display.h"

#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <time.h>
#include <iomanip>

// 게임의 한 프레임을 처리한다.
void Game::update()
{
    // isEnd = checkGameEnd();

    handleInput();
    dropTetromino();
    restrictInScreen(myTetromino);
    score_ += board.clearFullLines();

    timer.update();
}

// 게임 화면을 그린다.
void Game::draw()
{
    Display::drawBoxMenu("Next", 12, 0, nextTetromino);
    Display::drawBoxMenu("Hold", 18, 0, holdTetromino);
    console::drawBox(0, 0, 11, 21);
    Display::drawTextMenu(GameConfig::LINES - score_, timer);

    Display::drawBoard(board);

    isEnd = checkGameEnd();
}

void Game::handleInput()
{
    if (console::key(console::K_ESC)) // esc 게임 끝내기
    {
        exit(0);
    }

    if (console::key(console::K_DOWN)) // 아래 키 눌렀을 때, _dropDelay 속도 조정
    {
        _dropDelay = GameConfig::DROP_DELAY / GameConfig::SOFT_DELAY;
    }
    else
    {
        _dropDelay = GameConfig::DROP_DELAY;
    }

    if (console::key(console::K_SPACE)) // space 눌렀을 때 테트리오 홀드
    {
        if (canHold)
        {
            holdTetromino = *myTetromino.original(); // 원본 테트리오 모양
            newTetromino();                          // 새로운 테트리오 생성
            canHold = false;                         // 홀드 못하도록 비활성화
        }
    }

    if (console::key(console::K_UP)) // 키 업
    {
        posTetrominoY = posShadowY; // shadow에서 표기되는 Y 좌표를 테트리오 좌표에 대입
        fpsCount = 100;             // 화면 즉시 업데이트
    }

    if (console::key(console::K_LEFT)) // 왼쪽
    {
        if (board.isEmpty(myTetromino, posTetrominoX - 2, posTetrominoY - 1)) // 이동 이전 게임 판이 비어 있는지 검사
        {
            posTetrominoX--;
            _keyPressed = true; // 화면 업데이트를 위한 변수
        }
    }
    if (console::key(console::K_RIGHT)) // 오른쪽
    {
        if (board.isEmpty(myTetromino, posTetrominoX - 0, posTetrominoY - 1)) // 이동 이전 게임 판이 비어 있는지 검사
        {
            posTetrominoX++;
            _keyPressed = true; // 화면 업데이트를 위한 변수
        }
    }
    if (console::key(console::K_Z)) // 테트리오 돌리기
    {
        myTetromino = myTetromino.rotatedCCW();
        paddingTetromino(myTetromino, emptyTetromino);
        _keyPressed = true;
    }
    if (console::key(console::K_X)) // 테트리오 돌리기
    {
        myTetromino = myTetromino.rotatedCW();
        paddingTetromino(myTetromino, emptyTetromino);
        _keyPressed = true;
    }
}

void Game::restrictInScreen(Tetromino tetromino)
{
    int tetroSize = tetromino.size();

    // x, y 위치를 화면의 최대 크기에서 벗어나지 않게 한다.
    if (posTetrominoX + emptyTetromino[0] - 1 < 0)
        posTetrominoX = -emptyTetromino[0] + 1;

    if (posTetrominoX + tetroSize - emptyTetromino[2] - 1 >= GameConfig::BOARD_WIDTH)
        posTetrominoX = GameConfig::BOARD_WIDTH - tetroSize + emptyTetromino[2] + 1;

    if (posTetrominoY + tetroSize - emptyTetromino[3] - 1 >= GameConfig::BOARD_HEIGHT)
        posTetrominoY = GameConfig::BOARD_HEIGHT - tetroSize + emptyTetromino[3] + 1;

    if (_keyPressed) // shadow Y좌표 업데이트
    {
        posShadowY = board.shadowTetromino(myTetromino, emptyTetromino, posTetrominoX - 1, posTetrominoY - 1) + 1;
        _keyPressed = false;
    }
}

void Game::paddingTetromino(Tetromino tetromino, int (&margin)[4])
{
    bool isEmpty = true;
    int tetroSize = tetromino.size();
    margin[0] = 0;
    margin[1] = 0;
    margin[2] = 0;
    margin[3] = 0;

    // 왼쪽
    for (int i = 0; i < tetroSize / 2; i++)
    {
        for (int j = 0; j < tetroSize; j++)
        {
            if (tetromino.check(i, j))
            {
                isEmpty = false;
                break;
            }
        }
        if (isEmpty)
        {
            margin[0]++;
        }
        else
        {
            break;
        }
    }

    // 위
    isEmpty = true;
    for (int i = 0; i < tetroSize / 2; i++)
    {
        for (int j = 0; j < tetroSize; j++)
        {
            if (tetromino.check(j, i))
            {
                isEmpty = false;
                break;
            }
        }
        if (isEmpty)
        {
            margin[1]++;
        }
        else
        {
            break;
        }
    }

    // 오른쪽
    isEmpty = true;
    for (int i = 0; i < tetroSize / 2; i++)
    {
        for (int j = 0; j < tetroSize; j++)
        {
            if (tetromino.check(tetroSize - i - 1, j))
            {
                isEmpty = false;
                break;
            }
        }
        if (isEmpty)
        {
            margin[2]++;
        }
        else
        {
            break;
        }
    }

    // 아래
    isEmpty = true;
    for (int i = 0; i < tetroSize / 2; i++)
    {
        for (int j = 0; j < tetroSize; j++)
        {
            if (tetromino.check(j, tetroSize - i - 1))
            {
                isEmpty = false;
                break;
            }
        }
        if (isEmpty)
        {
            margin[3]++;
        }
        else
        {
            break;
        }
    }
}

void Game::dropTetromino()
{
    if (fpsCount >= _dropDelay)
    {
        if (posTetrominoY >= posShadowY)
        {
            board.addTetromino(myTetromino, posTetrominoX - 1, posTetrominoY - 1);
            newTetromino();
            canHold = true;
        }
        else
        {
            posTetrominoY++;
        }

        fpsCount = 0;
    }
    fpsCount++;
    isEnd = checkGameEnd();

    // 만일 게임이 끝나면 화면에 표시 안되도록 하는 로직
    if (!isEnd)
    {
        Display::drawTetromino(myTetromino, posTetrominoX, posShadowY, true);
        Display::drawTetromino(myTetromino, posTetrominoX, posTetrominoY, false);
    }
}

// 새로운 테트리오 생성
void Game::newTetromino()
{
    myTetromino = nextTetromino;       // 다음 -> 현재
    nextTetromino = randomTetromino(); // 새로운 다음 생성

    posTetrominoY = 1;
    paddingTetromino(myTetromino, emptyTetromino); // 생성된 tetrio의 공백 확인

    // shadow y 좌표 확인
    posShadowY = board.shadowTetromino(myTetromino, emptyTetromino, posTetrominoX - 1) + 1;
}

// 랜덤 테트리오 생성
Tetromino &Game::randomTetromino()
{
    srand((unsigned int)time(NULL)); // 랜덤 seed 생성
    int randomInt = (int)rand() % 7;
    do
    {
        randomInt = rand() % 7;
    } while (randomInt == lastTetromino); // 이전 값과 다를 때까지 랜덤 생성

    lastTetromino = randomInt; // 선택된 값을 저장

    switch (randomInt)
    {
    case 0:
        return Tetromino::I;
        break;
    case 1:
        return Tetromino::O;
        break;
    case 2:
        return Tetromino::T;
        break;
    case 3:
        return Tetromino::S;
        break;
    case 4:
        return Tetromino::Z;
        break;
    case 5:
        return Tetromino::J;
        break;
    case 6:
        return Tetromino::L;
        break;
    }
}

bool Game::checkGameEnd()
{
    // 새 테트로미노가 시작 위치에서 겹치거나(패배), 목표 라인 수를 완료하였을 때(승리) 판단
    if (GameConfig::LINES <= score_)
    {
        Display::drawResult(true, timer);
        return true;
    }
    else if (!board.isEmpty(myTetromino, posTetrominoX - 1, posTetrominoY - 1))
    {
        Display::drawResult(false, timer);
        return true;
    }

    return false;
}

// 게임 루프가 종료되어야 하는지 여부를 반환한다.
bool Game::shouldExit()
{
    return isEnd;
}

Game::Game()
{
    timer.start();

    nextTetromino = randomTetromino();
    newTetromino();
}
