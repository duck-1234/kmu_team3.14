#include "type.h"
#include "CommonUtils.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>

#define ENTER 13
#define ESC 27

TypingGame::TypingGame() {
    // [도박 예방 문구]
    sentences.push_back("도박 중독은 질병이며, 치료와 회복이 가능합니다.");
    sentences.push_back("당신의 소중한 일상, 도박과 맞바꾸지 마세요.");
    sentences.push_back("잃은 돈을 쫓는 것은 더 큰 수렁으로 빠지는 길입니다.");
    sentences.push_back("한 번의 요행이 평생의 불행을 부른다.");
    sentences.push_back("땀 흘려 번 돈만이 진정한 가치를 지닙니다.");

    // [명언]
    sentences.push_back("승자는 결코 포기하지 않고, 포기하는 자는 결코 승리하지 못한다.");
    sentences.push_back("가장 큰 위험은 아무런 위험도 감수하지 않는 것이다.");
    sentences.push_back("성공은 매일 반복한 작은 노력들의 합이다.");
    sentences.push_back("끝을 맺기를 처음과 같이 하면 실패가 없다.");
}

int TypingGame::playGame(long long reward, int currentLevel) {
    system("cls");
    std::cout << WIDTH_BORDER << std::endl;
    std::cout << "                                [ 노동 (타이핑) ]" << std::endl;
    std::cout << THIN_BORDER << std::endl;
    std::cout << "  ▶ 현재 장비 레벨 : Lv." << currentLevel << std::endl;
    std::cout << "  ▶ 성공 보상금    : " << formatToKorean(reward) << std::endl;
    std::cout << THIN_BORDER << std::endl;

    std::cout << "  제시된 문장을 띄어쓰기와 문장부호까지 정확하게 입력하세요.\n" << std::endl;
    std::cout << "  [Enter] 타이핑 시작   |   [ESC] 돌아가기\n" << std::endl;

    // 시작 또는 취소 입력 대기
    while (true) {
        int key = _getch();
        if (key == ESC) {
            return -1; // 취소 반환
        }
        else if (key == ENTER) {
            break; // 루프 탈출하고 게임 시작
        }
    }

    // 랜덤으로 문장 하나 선택
    int randomIndex = rand() % sentences.size();
    std::string targetSentence = sentences[randomIndex];

    std::cout << THIN_BORDER << std::endl;
    std::cout << "  [제시어] : " << targetSentence << std::endl;
    std::cout << "  [입력창] : ";

    std::string input;
    // 띄어쓰기까지 포함하여 한 줄 전체를 입력받음
    std::getline(std::cin, input);

    std::cout << THIN_BORDER << std::endl;

    if (input == targetSentence) {
        std::cout << "  [!] 완벽합니다! 정직한 노동의 대가를 받았습니다." << std::endl;
        std::cout << WIDTH_BORDER << std::endl;
        std::cout << "  (아무 키나 누르면 돌아갑니다)";
        (void)_getch();
        return 1;  // 성공
    }
    else {
        std::cout << "  [X] 오타가 있습니다... 피로만 쌓이고 보상을 받지 못했습니다." << std::endl;
        std::cout << WIDTH_BORDER << std::endl;
        std::cout << "  (아무 키나 누르면 돌아갑니다)";
        (void)_getch();
        return 0; // 실패
    }
}