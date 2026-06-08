#include "GameMenu.h"
#include "CommonUtils.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

#define UP 72
#define DOWN 80
#define ENTER 13

GameMenu::GameMenu() : selectedIndex(0) {
	menuItems = { "게임 시작", "조작법", "게임 종료" };
}

void GameMenu::drawMenu() {
	system("cls");
	std::cout << WIDTH_BORDER << std::endl;
	// [수정] 30일 -> 50일로 타이틀 수정[cite: 6]
	std::cout << "               [도박 예방 캠페인] 50일의 기적: 빚 갚기" << std::endl;
	std::cout << R"( .----------------.  .----------------.  .----------------.  .----------------.
| .--------------. || .--------------. || .--------------. || .--------------. |
| |  ________    | || |              | || |   _______    | || |     ____     | |
| | |_   ___ `.  | || |              | || |  |  _____|   | || |   .'    '.   | |
| |   | |   `. \ | || |    ______    | || |  | |____     | || |  |  .--.  |  | |
| |   | |    | | | || |   |______|   | || |  '_.____''.  | || |  | |    | |  | |
| |  _| |___.' / | || |              | || |  | \____) |  | || |  |  `--'  |  | |
| | |________.'  | || |              | || |   \______.'  | || |   '.____.'   | |
| |              | || |              | || |              | || |              | |
| '--------------' || '--------------' || '--------------' || '--------------' |
'----------------'  '----------------'  '----------------'  '----------------'
	)";
	std::cout << WIDTH_BORDER << std::endl;
	std::cout << "\n\n\n\n\n\n\n";

	for (int i = 0; i < (int)menuItems.size(); ++i) {
		if (i == selectedIndex)
			std::cout << "                             > " << menuItems[i] << " <" << std::endl;
		else
			std::cout << "                               " << menuItems[i] << std::endl;
	}
}

int GameMenu::run() {
	while (true) {
		drawMenu();
		int key = _getch();
		if (key == 224) {
			key = _getch();
			switch (key) {
			case UP:
				selectedIndex = (selectedIndex - 1 + (int)menuItems.size()) % (int)menuItems.size();
				break;
			case DOWN:
				selectedIndex = (selectedIndex + 1) % (int)menuItems.size();
				break;
			}
		}
		else if (key == ENTER) {
			return selectedIndex;
		}
	}
}