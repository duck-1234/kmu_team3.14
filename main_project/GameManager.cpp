#include "GameManager.h"
#include "EndingManager.h" // [추가] 엔딩 매니저 포함
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <iomanip> 

#define UP 72
#define DOWN 80
#define ENTER 13
#define ESC 27

struct LaborUpgradeData {
	std::string name;
	long long cost;
	long long reward;
	int maxCount;
};

GameManager::GameManager() {}

void GameManager::initGame() {
	debt = DebtSystem();
	player = Player();
	jobMgr = JobManager();
	upgradeMgr = UpgradeManager();
	augmentMgr = AugmentManager();
	isGameOver = false;
	isGameClear = false;

	dailyWorkCount = 0;
	laborLevel = 1;
	laborReward = 50000;
	maxLaborCount = 3;
}

int GameManager::displayDashboard() {
	std::vector<std::string> inGameChoices = {
		"다음 날 넘어가기",
		"돈 갚기 (은행 창구)",
		"전문성 강화 (알바 계약)",
		"자격증 취득 (기본급 증가)",
		"노동 (타이핑)",
		"노동력 강화 (단가 상승)",
		"도움말 보기 (경제 용어/시스템)"
	};
	int selected = 0;

	while (true) {
		system("cls");
		std::cout << WIDTH_BORDER << std::endl;

		std::string dday = (debt.getDaysLeft() > 0) ? "[ D - " + std::to_string(debt.getDaysLeft()) + " ]" : "[ D - Day ]";
		int padDday = (80 - (int)dday.length()) / 2;
		std::cout << std::string(padDday > 0 ? padDday : 0, ' ') << dday << std::endl;
		std::cout << THIN_BORDER << std::endl;

		std::cout << " [▼ 채무 현황]" << std::string(25, ' ') << " | [$ 자산 및 수익 현황]" << std::endl;

		std::string debtStr = " - 남은 총 빚 : " + formatToKorean(debt.getTotalDebt());
		std::string moneyStr = " - 현재 소지금  : " + formatToKorean(player.getMoney());
		int pad1 = 39 - (int)debtStr.length();
		std::cout << debtStr << std::string(pad1 > 0 ? pad1 : 0, ' ') << " | " << moneyStr << std::endl;

		std::string detailStr = "   (원금 " + formatToKorean(debt.getPrincipal()) + " / 이자 " + formatToKorean(debt.getAccumulatedInterest()) + ")";
		long long income = player.calculateDailyIncome();
		std::string incomeStr = " - 일일 총수익  : " + formatToKorean(income);
		int pad2 = 39 - (int)detailStr.length();
		std::cout << detailStr << std::string(pad2 > 0 ? pad2 : 0, ' ') << " | " << incomeStr << std::endl;

		int intRateBase = (int)(debt.getInterestRate() * 100);
		int intRateDec = (int)(debt.getInterestRate() * 1000) % 10;
		std::string rateStr = " - 적용 이자율: " + std::to_string(intRateBase) + "." + std::to_string(intRateDec) + "%";

		int bonusPercent = (int)((player.getBonusRate() - 1.0) * 100);
		std::string bonusSign = (bonusPercent >= 0) ? "+" : "";
		std::string bonusStr = "   (기본 " + formatToKorean(player.getBaseSalary()) + " / 보너스 " + bonusSign + std::to_string(bonusPercent) + "%)";

		int pad3 = 39 - (int)rateStr.length();
		std::cout << rateStr << std::string(pad3 > 0 ? pad3 : 0, ' ') << " | " << bonusStr << std::endl;

		std::string luckStr = " - 현재 운수    : Lv." + std::to_string(augmentMgr.getLuckLevel());
		std::cout << std::string(39, ' ') << " | " << luckStr << std::endl;

		std::cout << THIN_BORDER << std::endl;

		std::cout << " [ 오늘 노동 횟수 ] : " << dailyWorkCount << " / " << maxLaborCount << " 회" << std::endl;
		std::cout << THIN_BORDER << std::endl;

		double progressRaw = (100000000.0 - debt.getPrincipal()) / 100000000.0 * 100.0;
		int progress = (int)progressRaw;
		if (progress < 0) progress = 0;
		if (progress > 100) progress = 100;

		std::cout << " [ 빚 청산 진척도 : " << progress << "% ] (남은 원금: " << formatToKorean(debt.getPrincipal()) << ")" << std::endl;
		std::cout << " [";

		int filledBlocks = (progress * 30) / 100;
		for (int i = 0; i < 30; ++i) {
			if (i < filledBlocks) std::cout << "■";
			else std::cout << "□";
		}
		std::cout << "]" << std::endl;
		std::cout << WIDTH_BORDER << std::endl;

		for (int i = 0; i < (int)inGameChoices.size(); ++i) {
			if (i == selected) std::cout << "  ▶ " << inGameChoices[i] << std::endl;
			else std::cout << "     " << inGameChoices[i] << std::endl;
		}

		int key = _getch();
		if (key == 224) {
			key = _getch();
			if (key == UP) selected = (selected - 1 + (int)inGameChoices.size()) % (int)inGameChoices.size();
			else if (key == DOWN) selected = (selected + 1) % (int)inGameChoices.size();
		}
		else if (key == ENTER) return selected;
	}
}

void GameManager::runLaborUpgrade() {
	std::vector<LaborUpgradeData> laborList = {
		{"싸구려 멤브레인 키보드", 500000, 150000, 3},
		{"최고급 기계식 키보드", 2000000, 500000, 2},
		{"인체공학 워크스테이션", 10000000, 1500000, 1}
	};

	int selected = 0;
	int numItems = (int)laborList.size();

	while (true) {
		system("cls");
		std::cout << WIDTH_BORDER << std::endl;
		std::cout << "                                [ 노동력 강화 ]" << std::endl;
		std::cout << THIN_BORDER << std::endl;
		std::cout << "  [ 현재 보유 금액 ] : " << formatToKorean(player.getMoney()) << std::endl << std::endl;

		for (int i = 0; i < numItems; ++i) {
			int targetLevel = i + 2;

			std::cout << (i == selected ? "  ▶ " : "     ");
			std::cout << std::left << std::setw(26) << laborList[i].name;

			if (laborLevel >= targetLevel) {
				std::cout << "[구매 완료]";
			}
			else {
				std::cout << "비용: " << std::right << std::setw(11) << formatToKorean(laborList[i].cost)
					<< " (단가 " << formatToKorean(laborList[i].reward)
					<< " / 일 " << laborList[i].maxCount << "회)";
			}
			std::cout << std::endl;
		}

		std::cout << "\n  [ ESC: 돌아가기 ]" << std::endl;

		int key = _getch();
		if (key == 224) {
			key = _getch();
			if (key == UP) selected = (selected - 1 + numItems) % numItems;
			else if (key == DOWN) selected = (selected + 1) % numItems;
		}
		else if (key == ENTER) {
			int targetLevel = selected + 2;

			if (laborLevel >= targetLevel) {
				std::cout << "\n  [!] 이미 구매 완료한 장비입니다.";
				_getch();
			}
			else if (laborLevel < targetLevel - 1) {
				std::cout << "\n  [!] 이전 단계의 장비를 먼저 순차적으로 구매해야 합니다.";
				_getch();
			}
			else {
				if (player.getMoney() >= laborList[selected].cost) {
					player.setMoney(player.getMoney() - laborList[selected].cost);
					laborLevel = targetLevel;
					laborReward = laborList[selected].reward;
					maxLaborCount = laborList[selected].maxCount;

					std::cout << "\n  [!] 장비 구매 완료! 노동 단가가 대폭 상승했습니다.";
					_getch();
				}
				else {
					std::cout << "\n  [!] 자금이 부족합니다.";
					_getch();
				}
			}
		}
		else if (key == ESC) {
			break;
		}
	}
}

void GameManager::checkLevelUp() {
	bool levelUpHappened = false;
	std::string unlockMessage = "";

	if (!augmentMgr.isCertConditionMet() && upgradeMgr.getUpgradeLevel() >= 5) {
		unlockMessage += " [!] 전문 자격증을 취득하여 신뢰도가 상승했습니다!\n     (플래티넘 등장 확률 증가)";
		augmentMgr.setCertConditionMet();
		augmentMgr.addLuckLevel();
		levelUpHappened = true;
	}
	if (!augmentMgr.isRepayConditionMet() && debt.getTotalRepaidPrincipal() >= 30000000) {
		if (levelUpHappened) unlockMessage += "\n\n";
		unlockMessage += " [!] 성실한 상환 태도로 금융권 신용 등급이 올랐습니다!\n     (증강 테이블 추가 강화)";
		augmentMgr.setRepayConditionMet();
		augmentMgr.addLuckLevel();
		levelUpHappened = true;
	}
	if (!augmentMgr.isJobConditionMet() && jobMgr.getMasteredCount() >= 4) {
		if (levelUpHappened) unlockMessage += "\n\n";
		unlockMessage += " [!] 수많은 아르바이트를 섭렵하여 삶의 지혜가 깊어졌습니다!\n     (증강의 기운 추가 강화)";
		augmentMgr.setJobConditionMet();
		augmentMgr.addLuckLevel();
		levelUpHappened = true;
	}

	if (levelUpHappened) {
		system("cls");
		std::cout << WIDTH_BORDER << "\n" << unlockMessage << std::endl;
		std::cout << "\n ★ 현재 운수 레벨: Lv." << augmentMgr.getLuckLevel() << " ★\n" << WIDTH_BORDER;
		(void)_getch();
	}
}

void GameManager::processNextDay() {
	augmentMgr.runAugmentSelection(player, debt);
	player.addMoney(player.calculateDailyIncome());

	dailyWorkCount = 0;

	// [수정] 파산(기한 초과) 시 EndingManager 호출
	if (!debt.nextDay()) {
		EndingManager ending;
		ending.playEnding(EndingType::Bankruptcy, player.getMoney());
		isGameOver = true;
		return;
	}

	// [수정] 파산(이자 초과) 시 EndingManager 호출
	if (debt.getAccumulatedInterest() >= 100000000) {
		EndingManager ending;
		ending.playEnding(EndingType::Bankruptcy, player.getMoney());
		isGameOver = true;
		return;
	}
}

void GameManager::checkGameEndConditions() {
	// [수정] 빚 청산 시 우선순위에 따른 엔딩 분기 처리
	if (debt.getTotalDebt() <= 0) {
		EndingManager ending;

		// 1. 도박 중독 엔딩 (가장 우선)
		if (augmentMgr.getHasGambled()) {
			ending.playEnding(EndingType::GamblingAddiction, player.getMoney());
		}
		// 2. 기부 천사 엔딩
		else if (augmentMgr.getHasDonated()) {
			ending.playEnding(EndingType::DonationAngel, player.getMoney());
		}
		// 3. 일반 성공 엔딩
		else {
			ending.playEnding(EndingType::NormalSuccess, player.getMoney());
		}

		isGameClear = true;
	}
}

void GameManager::run() {
	while (true) {
		int mainChoice = menu.run();

		if (mainChoice == 0) {
			initGame();
			story.play();

			while (!isGameOver && !isGameClear) {
				checkLevelUp();

				int action = displayDashboard();

				if (action == 0) processNextDay();
				else if (action == 1) repayMgr.runMenu(player, debt);
				// [수정] WorkBase 추상화에 맞춰 매개변수 통일 (debt 추가)
				else if (action == 2) jobMgr.runMenu(player, debt);
				else if (action == 3) upgradeMgr.runMenu(player, debt);
				else if (action == 4) {
					if (dailyWorkCount >= maxLaborCount) {
						system("cls");
						std::cout << WIDTH_BORDER << "\n  오늘 할당된 노동 횟수를 모두 마쳤습니다.\n  다음 날 다시 시도하세요.\n" << WIDTH_BORDER;
						(void)_getch();
					}
					else {
						TypingGame typeGame;
						int result = typeGame.playGame(laborReward, laborLevel);

						if (result == 1) {
							player.addMoney(laborReward);
							dailyWorkCount++;
						}
						else if (result == 0) {
							dailyWorkCount++;
						}
					}
				}
				else if (action == 5) runLaborUpgrade();
				else if (action == 6) helpMgr.runMenu();

				if (!isGameOver) checkGameEndConditions();
			}
		}
		else if (mainChoice == 1) {
			system("cls");
			std::cout << WIDTH_BORDER << std::endl;
			std::cout << "                                [ 게임 조작법 및 규칙 ]" << std::endl;
			std::cout << THIN_BORDER << std::endl;
			std::cout << "\n  ■ 목표: 50일 이내에 원금 1억 원과 누적 이자를 모두 상환하십시오." << std::endl;
			std::cout << "  ■ 조작: 방향키(상/하)로 메뉴 이동, Enter로 선택합니다." << std::endl;
			std::cout << "  ■ 팁  : 전문성을 강화하여 기본급을 높이고, 알바를 통해 보너스를 챙기세요." << std::endl;
			std::cout << "  ■ 경고: 누적 이자가 5,000만 원을 넘으면 이자율이 폭등(3.3%)하며," << std::endl;
			std::cout << "           누적 이자가 1억 원 이상이 되면 즉시 파산(게임 오버)합니다!" << std::endl;
			std::cout << "\n" << WIDTH_BORDER << std::endl;
			std::cout << "                       [ 아무 키나 누르면 돌아갑니다 ]";
			(void)_getch();
		}
		else if (mainChoice == 2) {
			break;
		}
	}
}