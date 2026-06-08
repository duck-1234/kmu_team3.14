#pragma once

class DebtSystem {
private:
	long long principal;            // 현재 남은 원금
	long long accumulatedInterest;  // 현재 누적된 이자
	long long totalRepaidPrincipal; // 지금까지 갚은 순수 원금의 총합
	double interestRate;            // 이자율
	int daysLeft;                   // 남은 일수

	void checkInterestRate();       // 이자율 변동 체크용

public:
	DebtSystem();
	void displayStatus(long long playerMoney);
	bool nextDay();                 // 하루 경과
	void repayAmount(long long amount); // 특정 금액 상환 (이자 우선)

	int getDaysLeft() const;
	long long getTotalDebt() const;
	long long getAccumulatedInterest() const;
	long long getPrincipal() const;
	long long getTotalRepaidPrincipal() const { return totalRepaidPrincipal; }

	// [추가] 통합 대시보드 UI 출력을 위한 이자율 반환 함수
	double getInterestRate() const { return interestRate; }
};