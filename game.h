
#ifndef GAME_H
#define GAME_H

#include "tetromino.h"
#include "Timer.h"
#include "Board.h"
#include <iostream>
#include <string>
#include <chrono>
#include <sstream>

class Game
{
private:
  Timer timer;
  Board board;

  // 로그 출력을 위한 변수
  std::string strLog = "";

  // 화면 업데이트를 위한 변수
  int fpsCount = 0;
  int _dropDelay = GameConfig::DROP_DELAY;

  // 테트리오 좌표
  int posTetrominoX = 5;
  int posTetrominoY = 1;
  int posShadowY = GameConfig::BOARD_HEIGHT - 2;

  // 점수
  int score_ = 0;

  // 중복된 테트리오가 나오지 않기 하기 위해 randomTetromino 함수에서 사용되는 변수
  int lastTetromino = -1;

  // 게임에서 사용되는 테트리오 변수
  Tetromino myTetromino = Tetromino("null", 0, "");
  Tetromino holdTetromino = Tetromino("null", 0, "");
  Tetromino nextTetromino = Tetromino("null", 0, "");

  // 키를 눌렀을 때, 화면 업데이트를 위한 변수
  bool _keyPressed = false;

  // 홀드 활성화 여부
  bool canHold = true;

  // 게임 끝났는지 확인
  bool isEnd = false;

  // 테트리오에서 왼쪽 위 오른쪽 아래 순으로 비어있는 공간 출력
  int emptyTetromino[4] = {0};

  // 테트리오를 아래로 내리는 함수
  void dropTetromino();

  // 사용자 키 입력 함수
  void handleInput();

  // 게임이 끝나는지 확인
  bool checkGameEnd();

  // 테트리오가 화면 밖으로 나가지 않도록 조정
  void restrictInScreen(Tetromino tetromino);

  // 테트리오에서 왼쪽 위 오른쪽 아래 순으로 비어있는 공간 검사 함수
  void paddingTetromino(Tetromino tetromino, int (&margin)[4]);

  // 랜덤 테트리오 생성
  Tetromino &randomTetromino();

  // 새로운 테트리오 생성 함수
  void newTetromino();

public:
  // 게임의 한 프레임을 처리한다.
  void update();

  // 게임 화면을 그린다.
  void draw();

  // 게임 루프가 종료되어야 하는지 여부를 반환한다.
  bool shouldExit();

  Game();
};
#endif