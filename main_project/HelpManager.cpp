#include "HelpManager.h"
#include <iostream>
#include <conio.h>

// UI용 구분선 및 키보드 상수 직접 정의
#define WIDTH_BORDER "================================================================================"
#define THIN_BORDER  "--------------------------------------------------------------------------------"
#define UP 72
#define DOWN 80
#define ENTER 13
#define ESC 27

HelpManager::HelpManager() {
	// 경제 용어 설명
	helpList.push_back({ "원금 (Principal)", "대출받은 원래의 금액입니다. 이 게임에서는 1억 원에서 시작합니다." });
	helpList.push_back({ "이자 (Interest)", "빌린 돈에 대한 대가입니다. 매일 남은 원금에 이자율을 곱해 계산됩니다." });
	helpList.push_back({ "상환 (Repay)", "빚을 갚는 행위입니다. 항상 이자를 먼저 갚고 남은 돈으로 원금을 갚습니다." });
	helpList.push_back({ "채무 (Debt)", "법적으로 타인에게 갚아야 할 의무가 있는 돈을 의미합니다." });
	// 시스템 설명

	helpList.push_back({ "운수 레벨 (Luck)", "자격증 취득, 상환액 등에 따라 상승하며, 좋은 증강이 나올 확률을 높여줍니다." });
	helpList.push_back({ "증강 (Augment)", "매일 아침 발생하는 무작위 변수입니다. 자산이나 수익 효율에 긍정적/부정적 영향을 줍니다." });
	helpList.push_back({ "노동 (Labor)", "타이핑을 하여 오타 없이 문장을 입력하고 정직한 대가(보상금)를 수령하는 행동입니다." });
}

void HelpManager::runMenu() {
	int selected = 0;

	while (true) {
		system("cls");

		std::cout << WIDTH_BORDER << std::endl;
		std::cout << "                                [ 게임 도움말 ]" << std::endl;
		std::cout << THIN_BORDER << std::endl;
		std::cout << "  방향키로 선택 후 [Enter]를 누르면 상세 설명을 볼 수 있습니다.\n" << std::endl;

		for (int i = 0; i < (int)helpList.size(); ++i) {
			if (i == selected)
				std::cout << "  ▶ " << helpList[i].title << std::endl;
			else
				std::cout << "     " << helpList[i].title << std::endl;
		}

		std::cout << "\n" << THIN_BORDER << std::endl;
		std::cout << "  [ ESC: 돌아가기 ]" << std::endl;

		int key = _getch();

		if (key == 224) {
			key = _getch();
			if (key == UP)
				selected = (selected - 1 + (int)helpList.size()) % (int)helpList.size();
			else if (key == DOWN)
				selected = (selected + 1) % (int)helpList.size();
		}
		else if (key == ENTER) {
			system("cls");
			std::cout << THIN_BORDER << std::endl;
			std::cout << helpList[selected].title << std::endl;
			std::cout << THIN_BORDER << std::endl;
			std::cout << helpList[selected].description << std::endl;
			std::cout << THIN_BORDER << std::endl;
			std::cout << "\n(아무 키나 누르면 돌아갑니다)";
			_getch();
		}
		else if (key == ESC) {
			break;
		}
	}
}