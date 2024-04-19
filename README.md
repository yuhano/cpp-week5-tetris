# cpp-week5-tetris

>  c++ 프로그래밍 5주차 과제

# 📖 Description

c++ 프로그래밍 5주차 과제입니다. 

외부 라이브러리를 이용하여 tetris 게임 개발

## 🕰️ 개발 기간
* 24.04.03일 - 24.04.21일


## 💻 Getting Started

### 실방 방법
* tetris
```
$ git clone https://github.com/yuhano/cpp-week5-tetris.git tetris
$ cd tetris
$ mingw32-make
$ .\main.exe
```
### 게임 변수 조절방법
gameConfig.h
``` c++
namespace GameConfig
{
    // 보드 지워야하는 줄 갯수
    static const int LINES = 40;

    // softdrop speed
    static const int SOFT_DELAY = 4;
}
```

## 🔧 Stack
- **Language**: c++ 

##  Project Structure

```markdown
cpp-week3
└── tetris
    ├── console
    |    └── console.cpp // 게임 엔진
    ├── board.cpp // 게임판 관련된 오브젝트
    ├── display.cpp // 화면 그리는데 사용
    ├── game.cpp // 게임 진행 / 기타 클래스들을 하나로 합치기
    ├── gameConfig.h // 공통 환경 변수, 게임 진행을 위한 변수
    ├── tetromino.cpp // 테트로미노 
    └── timer.cpp // 타이머
```