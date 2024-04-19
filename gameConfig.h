#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

// tetris 환경 변수
namespace GameConfig
{
    // 보드 너비
    static const int BOARD_WIDTH = 10;
    // 보드 높이
    static const int BOARD_HEIGHT = 20;

    // 보드 지워야하는 줄 갯수
    static const int LINES = 40;

    // fps 프레임 수
    static const int DROP_DELAY = 60;

    // softdrop speed
    static const int SOFT_DELAY = 4;

}

#endif