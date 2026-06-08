#include "AugmentManager.h"
#include "CommonUtils.h"
#include <iostream>
#include <conio.h>
#include <ctime>
#include <cmath>
#include <vector>
#include <string>

#define UP 72
#define DOWN 80
#define ENTER 13

AugmentManager::AugmentManager()
	: luckLevel(0), condCertSeen(false), condRepaySeen(false), condJobSeen(false) {
}

std::vector<std::unique_ptr<AugmentBase>> AugmentManager::generateChoices() {
	std::vector<std::unique_ptr<AugmentBase>> choices;
	int silverCut, goldCut;

	// 운수 레벨에 따른 확률 테이블
	switch (luckLevel) {
	case 1: silverCut = 60; goldCut = 90; break;
	case 2: silverCut = 50; goldCut = 85; break;
	case 3: silverCut = 40; goldCut = 75; break;
	default: silverCut = 80; goldCut = 100; break;
	}

	for (int i = 0; i < 3; ++i) {
		int r = rand() % 100;

		// 1. 실버 증강 (범위: -30만 ~ +30만)
		if (r < silverCut) {
			long long amount = (rand() % 61 - 30) * 10000;
			std::string n, d;

			if (amount < 0) {
				std::vector<std::string> negNames = { "보험료 납부", "휴대폰 요금", "전기세 납부", "수도세 납부", "월세 지출", "병원비 발생" };
				std::string amtStr = formatToKorean(std::abs(amount));
				std::vector<std::string> negDescs = {
					"보험료 고지서가 날아와 [ -" + amtStr + " ] 지출이 발생했습니다.",
					"이번 달 휴대폰 요금 자동이체로 [ -" + amtStr + " ] 빠져나갔습니다.",
					"누진세 폭탄! 전기세 정산으로 [ -" + amtStr + " ] 납부했습니다.",
					"수도요금 고지서를 확인하고 [ -" + amtStr + " ] 지출했습니다.",
					"야속한 집주인... 이번 달 월세로 [ -" + amtStr + " ] 빠져나갔습니다.",
					"과로로 인한 감기몸살에 걸려 병원비로 [ -" + amtStr + " ] 썼습니다."
				};
				int idx = rand() % negNames.size();
				n = negNames[idx];
				d = negDescs[idx];
			}
			else {
				std::vector<std::string> posNames = { "일이 잘됨", "능률 상승", "보너스 획득", "로또 5등 당첨" };
				std::string amtStr = formatToKorean(amount);
				std::vector<std::string> posDescs = {
					"오늘따라 일이 잘 풀려 수고비로 [ +" + amtStr + " ] 얻었습니다.",
					"능률이 올라 빠른 퇴근과 함께 추가 수당 [ +" + amtStr + " ] 받았습니다.",
					"우수 근무자로 선정되어 깜짝 보너스 [ +" + amtStr + " ] 획득했습니다.",
					"쉬는 시간에 우연히 산 로또가 5등에 당첨되어 [ +" + amtStr + " ] 생겼습니다."
				};
				int idx = rand() % posNames.size();
				n = posNames[idx];
				d = posDescs[idx];
			}
			choices.push_back(std::make_unique<SilverAugment>(n, d, amount));
		}
		// 2. 골드 증강 (범위: -10% ~ +10%)
		else if (r < goldCut) {
			int rateInt = (rand() % 21 - 10);
			double rate = rateInt / 100.0;
			std::string n, d;

			if (rateInt < 0) {
				std::vector<std::string> negNames = { "발주 실수", "민원 발생", "범칙금 부과", "지각 처리" };
				std::string rateStr = std::to_string(std::abs(rateInt));
				std::vector<std::string> negDescs = {
					"치명적인 발주 실수로 멘탈이 흔들려 업무 효율이 [ -" + rateStr + "% ] 하락했습니다.",
					"악성 민원 고객을 상대하느라 지쳐 업무 효율이 [ -" + rateStr + "% ] 떨어졌습니다.",
					"예상치 못한 범칙금 부과에 스트레스를 받아 효율이 [ -" + rateStr + "% ] 감소했습니다.",
					"피로 누적으로 지각하여 페널티를 받아 효율이 [ -" + rateStr + "% ] 깎였습니다."
				};
				int idx = rand() % negNames.size();
				n = negNames[idx];
				d = negDescs[idx];
			}
			else {
				std::vector<std::string> posNames = { "성과금 지급", "로또 3등 당첨", "공모전 수상", "강연 초청" };
				std::string rateStr = std::to_string(rateInt);
				std::vector<std::string> posDescs = {
					"뛰어난 성과를 인정받아 일할 맛이 나 효율이 [ +" + rateStr + "% ] 상승했습니다.",
					"로또 3등 당첨의 쾌감 덕분에 업무 집중력과 효율이 [ +" + rateStr + "% ] 증가했습니다!",
					"참여했던 공모전에서 수상하여 자신감이 붙어 효율이 [ +" + rateStr + "% ] 상승했습니다.",
					"노하우 강연 초청을 받아 전문가로서의 능률이 [ +" + rateStr + "% ] 올랐습니다."
				};
				int idx = rand() % posNames.size();
				n = posNames[idx];
				d = posDescs[idx];
			}
			choices.push_back(std::make_unique<GoldAugment>(n, d, rate));
		}
		// 3. 플래티넘 증강 (효율 +15%~+20%, 즉시지급 50~100만)
		else {
			long long pMoney = (rand() % 51 + 50) * 10000;
			int pRateInt = (rand() % 6 + 15);
			double pRate = pRateInt / 100.0;

			std::string pMoneyStr = formatToKorean(pMoney);
			std::string pRateStr = std::to_string(pRateInt);

			choices.push_back(std::make_unique<PlatinumAugment>(
				"인생의 전환점",
				"운수 대통! 즉시 자금 [ +" + pMoneyStr + " ] 확보 및 효율 [ +" + pRateStr + "% ] 영구 증가!",
				pMoney, pRate
			));
		}
	}
	return choices;
}

void AugmentManager::runAugmentSelection(Player& p, DebtSystem& d) {
	auto choices = generateChoices();
	int selected = 0;

	while (true) {
		system("cls");
		std::cout << WIDTH_BORDER << std::endl;
		std::cout << "                       [ 오늘의 운세와 변수 (증강 선택) ]" << std::endl;
		std::cout << "         운수 레벨: Lv." << luckLevel << " | 신중한 선택이 곧 실력입니다." << std::endl;
		std::cout << THIN_BORDER << std::endl;

		for (int i = 0; i < 3; ++i) {
			std::string tierLine = (choices[i]->getTier() == 0) ? "[SILVER]" : (choices[i]->getTier() == 1) ? "[GOLD]" : "[PLATINUM]";
			std::cout << (i == selected ? "  ▶ " : "     ") << tierLine << " " << choices[i]->getName() << std::endl;

			// 들여쓰기를 맞춰 사건(문장)이 깔끔하게 보이도록 출력
			std::cout << "        - " << choices[i]->getDesc() << std::endl << std::endl;
		}

		int key = _getch();
		if (key == 224) {
			key = _getch();
			if (key == UP) selected = (selected - 1 + 3) % 3;
			else if (key == DOWN) selected = (selected + 1) % 3;
		}
		else if (key == ENTER) {
			choices[selected]->apply(p, d);
			std::cout << "\n  [!] 선택하신 효과가 즉시 적용되었습니다.";
			(void)_getch();
			break;
		}
	}
}