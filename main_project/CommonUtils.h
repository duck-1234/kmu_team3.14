#pragma once
#include <string>
#include <windows.h>
#include <cmath>

#ifndef WIDTH_BORDER
#define WIDTH_BORDER "================================================================================"
#endif

#ifndef THIN_BORDER
#define THIN_BORDER  "--------------------------------------------------------------------------------"
#endif

// 금액 한국어 변환 (음수 및 '원' 단위 상세 출력 지원)
inline std::string formatToKorean(long long money) {
	if (money == 0) return "0원";

	std::string result = "";
	if (money < 0) result += "-"; // 음수 기호 추가

	long long absMoney = std::abs(money); // 절대값 계산
	long long eok = absMoney / 100000000;
	long long man = (absMoney % 100000000) / 10000;
	long long won = absMoney % 10000; // 만 단위 아래 나머지 금액 추가

	if (eok > 0) result += std::to_string(eok) + "억 ";
	if (man > 0) result += std::to_string(man) + "만 ";
	if (won > 0 || (eok == 0 && man == 0)) result += std::to_string(won) + "원";

	return result;
}

inline void hideCursor() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}