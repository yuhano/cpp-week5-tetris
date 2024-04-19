#include "Display.h"

std::string strLeftLine = "";

// 텍스트 중앙 정렬 그리기
void drawTextMiddle(int y, std::string str);

void drawTextMiddle(int y, std::string str)
{
    console::draw(GameConfig::BOARD_WIDTH / 2 - str.size() / 2 + 1, y, str);
}

void Display::drawBoard(const Board &board_)
{
    for (int i = 0; i < GameConfig::BOARD_WIDTH; i++)
    {
        for (int j = 0; j < GameConfig::BOARD_HEIGHT; j++)
        {
            if (board_.check(i, j))
            {
                console::draw(i + 1, j + 1, BLOCK_STRING);
            }
        }
    }
}

void Display::drawBoxMenu(std::string title, int minX, int minY, Tetromino tetromino)
{
    console::drawBox(minX, minY, minX + 5, minY + 5);
    console::draw(minX + 1, minY, title);

    if (tetromino.size() != 0) // tetromino가 null 이면 출력하지 않기 
    {
        tetromino.drawAt(BLOCK_STRING, minX + 1, minY + 1);
    }
}

void Display::drawTextMenu(int leftLine, Timer timer)
{
    strLeftLine = std::to_string(leftLine) + " lines left";
    drawTextMiddle(GameConfig::BOARD_HEIGHT + 2, strLeftLine);

    drawTextMiddle(GameConfig::BOARD_HEIGHT + 3, timer.getFormattedTime());
}

void Display::drawTetromino(Tetromino Tetromino, int posX, int posY, bool isShadow)
{
    if (isShadow)
    {
        Tetromino.drawAt(SHADOW_STRING, posX, posY);
    }
    else
    {
        Tetromino.drawAt(BLOCK_STRING, posX, posY);
    }
}

void Display::drawResult(bool isWin, Timer timers)
{
    if (isWin)
    {
        drawTextMiddle(GameConfig::BOARD_HEIGHT / 2, "You Win");
    }
    else
    {
        drawTextMiddle(GameConfig::BOARD_HEIGHT / 2, "You Lost");
        drawTextMiddle(GameConfig::BOARD_HEIGHT / 2 + 1, timers.getFormattedTime());
    }
}