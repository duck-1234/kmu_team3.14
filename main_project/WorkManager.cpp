#include "WorkManager.h"
#include "CommonUtils.h"
#include <iostream>
#include <conio.h>
#include <iomanip>

#define UP 72
#define DOWN 80
#define ENTER 13
#define ESC 27

// --- WorkBase 공통 UI ---
void WorkBase::drawHeader(const std::string& title, long long playerMoney) {
	system("cls");
	std::cout << WIDTH_BORDER << std::endl;
	std::cout << "                                " << title << std::endl;
	std::cout << THIN_BORDER << std::endl;
	std::cout << "  [ 현재 보유 금액 ] : " << formatToKorean(playerMoney) << std::endl << std::endl;
}

void WorkBase::drawFooter() {
	std::cout << "\n  [ ESC: 돌아가기 ]" << std::endl;
}

// --- JobManager 구현 ---
JobManager::JobManager() {
	jobs.push_back({ "전단지 배포", 100000, 0.05, false });
	jobs.push_back({ "식당 설거지", 500000, 0.10, false });
	jobs.push_back({ "편의점 주간", 1200000, 0.15, false });
	jobs.push_back({ "카페 바리스타", 3000000, 0.25, false });
	jobs.push_back({ "배달 라이더", 7000000, 0.40, false });
	jobs.push_back({ "택배 상하차", 12000000, 0.65, false });
	jobs.push_back({ "건설 현장 인부", 20000000, 0.90, false });
	jobs.push_back({ "고층 외벽 청소", 35000000, 1.30, false });
	jobs.push_back({ "원양어선 선원", 55000000, 2.00, false });
}

bool JobManager::isAllJobsMastered() const {
	for (const auto& j : jobs) {
		if (!j.isOwned) return false;
	}
	return true;
}

// [수정] WorkBase 규약에 맞게 DebtSystem& d 추가
void JobManager::runMenu(Player& p, DebtSystem& d) {
	int selected = 0;
	while (true) {
		drawHeader("[ 전문성 강화 (알바) ]", p.getMoney());

		if (isAllJobsMastered()) {
			std::cout << "               ★ 모든 아르바이트를 마스터했습니다! ★" << std::endl << std::endl;
		}

		for (int i = 0; i < (int)jobs.size(); ++i) {
			std::cout << (i == selected ? "  ▶ " : "     ") << std::left << std::setw(20) << jobs[i].name;
			if (jobs[i].isOwned) std::cout << "[마스터]";
			else std::cout << "비용: " << std::right << std::setw(10) << formatToKorean(jobs[i].cost) << " (+" << (int)(jobs[i].rateBoost * 100) << "%)";
			std::cout << std::endl;
		}
		drawFooter();

		int key = _getch();
		if (key == 224) {
			key = _getch();
			if (key == UP) selected = (selected - 1 + (int)jobs.size()) % (int)jobs.size();
			else if (key == DOWN) selected = (selected + 1) % (int)jobs.size();
		}
		else if (key == ENTER) {
			if (jobs[selected].isOwned) {
				std::cout << "\n  [!] 이미 마스터한 일자리입니다.";
				_getch();
			}
			else if (p.getMoney() >= jobs[selected].cost) {
				p.setMoney(p.getMoney() - jobs[selected].cost);
				jobs[selected].isOwned = true;
				p.addBonusRate(jobs[selected].rateBoost);
				std::cout << "\n  [!] 계약 성공! 수익 보너스가 적용됩니다.";
				_getch();
			}
			else {
				std::cout << "\n  [!] 자금이 부족합니다.";
				_getch();
			}
		}
		else if (key == ESC) break;
	}
}

// --- UpgradeManager 구현 ---
UpgradeManager::UpgradeManager() : upgradeLevel(1) {
	upgradeTable.push_back({ 0, 100000, "무자격 (고졸)" });
	upgradeTable.push_back({ 200000, 250000, "1종 보통 운전면허" });
	upgradeTable.push_back({ 800000, 450000, "컴퓨터활용능력 2급" });
	upgradeTable.push_back({ 2000000, 700000, "지게차운전기능사" });
	upgradeTable.push_back({ 4500000, 1000000, "위험물산업기사" });
	upgradeTable.push_back({ 8000000, 1400000, "전기기사" });
	upgradeTable.push_back({ 14000000, 1900000, "공인중개사" });
	upgradeTable.push_back({ 24000000, 2500000, "세무사" });
	upgradeTable.push_back({ 36000000, 3200000, "공인회계사(CPA)" });
	upgradeTable.push_back({ 50000000, 4000000, "변호사" });
}

// [수정] WorkBase 규약에 맞게 DebtSystem& d 추가
void UpgradeManager::runMenu(Player& p, DebtSystem& d) {
	int selected = 0;
	int numUpgrades = (int)upgradeTable.size() - 1; // 1번 인덱스부터 9번까지 (총 9개)

	while (true) {
		drawHeader("[ 자격증 취득 ]", p.getMoney());

		for (int i = 0; i < numUpgrades; ++i) {
			int tableIdx = i + 1; // 실제 upgradeTable 접근 인덱스 (1 ~ 9)

			std::cout << (i == selected ? "  ▶ " : "     ");
			std::cout << std::left << std::setw(22) << upgradeTable[tableIdx].certName;

			if (tableIdx < upgradeLevel) {
				std::cout << "[취득 완료]";
			}
			else {
				std::cout << "비용: " << std::right << std::setw(11) << formatToKorean(upgradeTable[tableIdx].cost)
					<< " (기본급 " << formatToKorean(upgradeTable[tableIdx].targetSalary) << ")";
			}
			std::cout << std::endl;
		}

		drawFooter();

		int key = _getch();
		if (key == 224) {
			key = _getch();
			if (key == UP) selected = (selected - 1 + numUpgrades) % numUpgrades;
			else if (key == DOWN) selected = (selected + 1) % numUpgrades;
		}
		else if (key == ENTER) {
			int tableIdx = selected + 1;

			if (tableIdx < upgradeLevel) {
				std::cout << "\n  [!] 이미 취득한 자격증입니다.";
				_getch();
			}
			else if (tableIdx > upgradeLevel) {
				std::cout << "\n  [!] 이전 단계의 자격증을 먼저 순차적으로 취득해야 합니다.";
				_getch();
			}
			else { // tableIdx == upgradeLevel (정확히 다음 단계 자격증)
				if (p.getMoney() >= upgradeTable[tableIdx].cost) {
					p.setMoney(p.getMoney() - upgradeTable[tableIdx].cost);
					p.setBaseSalary(upgradeTable[tableIdx].targetSalary);
					upgradeLevel++;
					std::cout << "\n  [!] 자격증 취득 성공! 기본급이 인상되었습니다.";
					_getch();
				}
				else {
					std::cout << "\n  [!] 자금이 부족합니다.";
					_getch();
				}
			}
		}
		else if (key == ESC) break;
	}
}

// --- RepayManager 구현 ---
// (이곳은 이미 매개변수가 2개로 올바르게 설정되어 있었습니다)
void RepayManager::runMenu(Player& p, DebtSystem& d) {
	std::vector<std::string> opts = { "100만 원 상환", "500만 원 상환", "1,000만 원 상환", "5,000만 원 상환", "보유 자금 전액 상환 (MAX)", "직접 입력하여 상환" };
	int selected = 0;
	while (true) {
		drawHeader("[ 채무 상환 창구 ]", p.getMoney());
		std::cout << "  [ 남은 원금 ] : " << formatToKorean(d.getPrincipal()) << std::endl;
		std::cout << "  [ 현재 이자 ] : " << formatToKorean(d.getAccumulatedInterest()) << std::endl;
		std::cout << THIN_BORDER << std::endl;
		for (int i = 0; i < (int)opts.size(); ++i) std::cout << (i == selected ? "  ▶ " : "     ") << opts[i] << std::endl;
		drawFooter();

		int key = _getch();
		if (key == 224) {
			key = _getch();
			if (key == UP) selected = (selected - 1 + (int)opts.size()) % (int)opts.size();
			else if (key == DOWN) selected = (selected + 1) % (int)opts.size();
		}
		else if (key == ENTER) {
			long long amount = 0;
			bool cancel = false;
			if (selected == 0) amount = 1000000;
			else if (selected == 1) amount = 5000000;
			else if (selected == 2) amount = 10000000;
			else if (selected == 3) amount = 50000000;
			else if (selected == 4) amount = p.getMoney();
			else if (selected == 5) {
				std::cout << "\n  상환 금액 입력 (원): ";
				if (!(std::cin >> amount)) { std::cin.clear(); std::cin.ignore(1024, '\n'); std::cout << "  [!] 잘못된 입력입니다."; cancel = true; }
				else if (amount < 0) { std::cout << "  [!] 0 이상만 입력 가능합니다."; cancel = true; }
			}
			if (!cancel) {
				if (amount > p.getMoney()) { std::cout << "  [!] 자금이 부족합니다."; cancel = true; }
				else if (amount > 0) {
					if (amount > d.getTotalDebt()) amount = d.getTotalDebt();
					d.repayAmount(amount);
					p.setMoney(p.getMoney() - amount);
					std::cout << "\n  " << formatToKorean(amount) << " 상환 완료.";
					if (d.getTotalDebt() <= 0) { _getch(); break; }
				}
			}
			_getch();
		}
		else if (key == ESC) break;
	}
}