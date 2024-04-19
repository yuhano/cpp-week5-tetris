#include "GameConfig.h"
#include "console/console.h"
#include "Board.h"
#include "Timer.h"
#include "tetromino.h"

// 화면에 그리는 함수
namespace Display
{
    // 게임 판을 나타내는 배열을 그리기
    void drawBoard(const Board &board);

    // 박스 소메뉴 그리기
    void drawBoxMenu(std::string title, int minX, int minY, Tetromino tetromino);

    // 텍스트 메뉴 그리기
    void drawTextMenu(int leftLine, Timer timer);

    // 테트리오 그리기
    // shadow 값에 따라 화면에 표기되는 모양이 달라집니다.
    void drawTetromino(Tetromino Tetromino, int posX, int posY, bool isShadow);

    // 결과 그리기
    // 패배 시 시간 출력을 위한 timer argumet
    void drawResult(bool isWin, Timer timers);

} 
