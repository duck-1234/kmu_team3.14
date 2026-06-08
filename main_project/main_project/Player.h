#pragma once

class Player {
private:
	long long money;
	long long baseSalary;
	double bonusRate;

public:
	Player();

	long long getMoney() const { return money; }
	void setMoney(long long m);
	void addMoney(long long m);

	long long getBaseSalary() const { return baseSalary; }
	void setBaseSalary(long long s);

	double getBonusRate() const { return bonusRate; }

	// [수정 포인트] 본문 { ... } 을 지우고 세미콜론만 남기세요.
	void addBonusRate(double r);

	long long calculateDailyIncome() const;
};