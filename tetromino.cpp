#include "tetromino.h"
#include "console/console.h"

Tetromino::Tetromino(std::string name, int size, std::string shape)
{
    for (int i = 0; i < shape.length(); i++)
    {
        if (shape.at(i) == 'O') // O 문자열이면 true 값 입력
        {
            shape_[i / size][i % size] = true;
        }
    }
    name_ = name;
    size_ = size;
    original_ = this;
}

void Tetromino::changedShaped(bool (&changedshape_)[MAX_SIZE][MAX_SIZE])
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        for (int j = 0; j < MAX_SIZE; j++)
        {
            shape_[i][j] = changedshape_[i][j];  // argumet 값을 shape_ 값으로 대입
        }
    }
}

// 시계 방향으로 회전한 모습의 테트로미노 객체를 반환한다.
Tetromino Tetromino::rotatedCW()
{
    bool newShape_[MAX_SIZE][MAX_SIZE] = {false};
    for (int i = 0; i < size_; i++)
    {
        for (int j = 0; j < size_; j++)
        {
            newShape_[i][j] = shape_[size_ - j - 1][i];
        }
    }
    Tetromino rotated(name_, size_, "");    // null 값의 tetromino 생성
    rotated.changedShaped(newShape_);   // shape 값 변경
    rotated.original_ = original_;  // 이전 원본 shape 값 저장시키기
    return rotated;
}

// 반시계 방향으로 회전한 모습의 테트로미노 객체를 반환한다.
Tetromino Tetromino::rotatedCCW()
{
    bool newShape_[MAX_SIZE][MAX_SIZE] = {false};
    for (int i = 0; i < size_; i++)
    {
        for (int j = 0; j < size_; j++)
        {
            newShape_[j][size_ - i - 1] = shape_[i][j];
        }
    }
    Tetromino rotated(name_, size_, ""); // null 값의 tetromino 생성
    rotated.changedShaped(newShape_);  // shape 값 변경
    rotated.original_ = original_; // 이전 원본 shape 값 저장시키기
    return rotated;
}

// 화면의 x, y 위치에 s 문자열로  테트로미노를 그린다
void Tetromino::drawAt(std::string s, int x, int y)
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        for (int j = 0; j < MAX_SIZE; j++)
        {
            if (shape_[i][j])  // shape_값이 true면 그리기
            {
                console::draw(x + i, y + j, s); 
            }
        }
    }
}

Tetromino Tetromino::I("I", 4, "XXXXOOOOXXXXXXXX");
Tetromino Tetromino::O("O", 2, "OOOO");
Tetromino Tetromino::T("T", 3, "XOXOOOXXX");
Tetromino Tetromino::S("S", 3, "XOOOOXXXX");
Tetromino Tetromino::Z("Z", 3, "OOXXOOXXX");
Tetromino Tetromino::J("J", 3, "OXXOOOXXX");
Tetromino Tetromino::L("L", 3, "XXOOOOXXX");