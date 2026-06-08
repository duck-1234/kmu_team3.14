#include <windows.h>
#include <ctime>
#include <cstdlib>
#include "CommonUtils.h"
#include "GameManager.h"

int main() {
	// 1. 랜덤 시드 및 콘솔 환경 설정
	srand(static_cast<unsigned int>(time(NULL)));
	system("mode con: cols=82 lines=25");
	hideCursor();

	// 2. 게임 매니저 생성 및 실행
	GameManager game;
	game.run();

	return 0;
}