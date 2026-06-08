#include "DebtSystem.h"
#include "CommonUtils.h"
#include <iostream>
#include <conio.h> // _getch() 사용을 위해 추가

DebtSystem::DebtSystem()
	: principal(100000000), accumulatedInterest(0), totalRepaidPrincipal(0), interestRate(0.02), daysLeft(50) {
	// [수정] 이자율 2% (0.02), 제한 일수 50일로 초기화[cite: 4]
}

// [추가] 실시간 이자율 변동 로직
void DebtSystem::checkInterestRate() {
	// 누적 이자가 5,000만 원 이상이고, 현재 이자율이 2.0%일 때
	if (accumulatedInterest >= 50000000 && interestRate < 0.033) {
		interestRate = 0.033;
		system("cls");
		std::cout << WIDTH_BORDER << std::endl;
		std::cout << "\n  [경고] 누적 이자가 5,000만 원을 초과했습니다!" << std::endl;
		std::cout << "  이자를 갚지 않아 이자율이 증가했습니다. (적용 이자율: 3.3%)" << std::endl;
		std::cout << "\n" << WIDTH_BORDER << std::endl;
		_getch();
	}
	// 누적 이자가 5,000만 원 미만이고, 현재 이자율이 3.3%일 때
	else if (accumulatedInterest < 50000000 && interestRate > 0.02) {
		interestRate = 0.02;
		system("cls");
		std::cout << WIDTH_BORDER << std::endl;
		std::cout << "\n  [안내] 누적 이자가 5,000만 원 이하로 떨어졌습니다!" << std::endl;
		std::cout << "  이자를 잘 갚아 이자율이 인하되었습니다. (적용 이자율: 2.0%)" << std::endl;
		std::cout << "\n" << WIDTH_BORDER << std::endl;
		_getch();
	}
}

void DebtSystem::displayStatus(long long playerMoney) {
	system("cls");
	std::cout << WIDTH_BORDER << std::endl;
	if (daysLeft > 0) std::cout << "                                  [ D - " << daysLeft << " ]" << std::endl;
	else std::cout << "                                  [ D - Day ]" << std::endl;
	std::cout << THIN_BORDER << std::endl;

	std::cout << "\n  < 채무 현황 >" << std::endl;
	std::cout << "  원금      : " << formatToKorean(principal) << std::endl;
	std::cout << "  현재 이자 : " << formatToKorean(accumulatedInterest) << std::endl;
	std::cout << "  이자율    : " << interestRate * 100 << "%" << std::endl;

	std::cout << "\n  < 자산 현황 >" << std::endl;
	std::cout << "  보유 자금 : " << formatToKorean(playerMoney) << std::endl;
	std::cout << std::endl << WIDTH_BORDER << std::endl;
}

bool DebtSystem::nextDay() {
	if (daysLeft <= 0) return false;

	// 매일 이자 계산 로직[cite: 4]
	accumulatedInterest += static_cast<long long>(principal * interestRate);
	daysLeft--;

	// 하루가 지나 이자가 불어난 시점에서 검사 수행
	checkInterestRate();

	return true;
}

void DebtSystem::repayAmount(long long amount) {
	if (amount <= 0) return;

	// 1. 이자부터 상환[cite: 4]
	if (amount >= accumulatedInterest) {
		long long remainingAfterInterest = amount - accumulatedInterest;
		accumulatedInterest = 0;

		// 2. 남은 금액으로 원금 상환 및 누적 상환액 기록[cite: 4]
		principal -= remainingAfterInterest;
		totalRepaidPrincipal += remainingAfterInterest;
	}
	else {
		accumulatedInterest -= amount;
	}

	// 원금을 초과해서 갚았을 경우 누적 상환액 보정[cite: 4]
	if (principal < 0) {
		totalRepaidPrincipal += principal;
		principal = 0;
	}

	// 빚을 상환하여 이자가 차감된 시점에서 검사 수행
	checkInterestRate();
}

int DebtSystem::getDaysLeft() const { return daysLeft; }
long long DebtSystem::getTotalDebt() const { return principal + accumulatedInterest; }
long long DebtSystem::getAccumulatedInterest() const { return accumulatedInterest; }
long long DebtSystem::getPrincipal() const { return principal; }