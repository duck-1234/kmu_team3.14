#pragma once
#include <string>

enum class EndingType {
	Bankruptcy,        // 1. 파산 (Failure)
	GamblingAddiction, // 2. 도박중독 (Bad Success)
	DonationAngel,     // 3. 기부천사 (True Happy Success)
	NormalSuccess      // 4. 일반 성공 (Normal Success)
};

class EndingManager {
private:
	void drawEndingHeader(const std::string& title);

public:
	EndingManager() = default;

	// 엔딩을 출력하는 핵심 함수
	void playEnding(EndingType type, long long finalMoney);
};