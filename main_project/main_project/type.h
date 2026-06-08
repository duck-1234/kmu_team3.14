#pragma once
#include <string>
#include <vector>

class TypingGame {
private:
    std::vector<std::string> sentences;

public:
    TypingGame();

    // 반환값 변경: 1(성공), 0(실패), -1(ESC 취소)
    int playGame(long long reward, int currentLevel);
};