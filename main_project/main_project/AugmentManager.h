#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Player.h"
#include "DebtSystem.h"
#include "CommonUtils.h"

// --- 증강 추상 부모 클래스 ---
class AugmentBase {
protected:
	std::string name;
	std::string description;
	int tier; // 0: 실버, 1: 골드, 2: 플래티넘

public:
	AugmentBase(std::string n, std::string d, int t) : name(n), description(d), tier(t) {}
	virtual ~AugmentBase() {}

	virtual void apply(Player& p, DebtSystem& d) = 0;
	std::string getName() const { return name; }
	std::string getDesc() const { return description; }
	int getTier() const { return tier; }
};

// --- 증강 세부 클래스 (실버/골드/플래티넘) ---
class SilverAugment : public AugmentBase {
private:
	long long moneyChange;
public:
	SilverAugment(std::string n, std::string d, long long amount) : AugmentBase(n, d, 0), moneyChange(amount) {}
	void apply(Player& p, DebtSystem& d) override { p.addMoney(moneyChange); }
};

class GoldAugment : public AugmentBase {
private:
	double bonusRate;
public:
	GoldAugment(std::string n, std::string d, double rate) : AugmentBase(n, d, 1), bonusRate(rate) {}
	void apply(Player& p, DebtSystem& d) override { p.addBonusRate(bonusRate); }
};

class PlatinumAugment : public AugmentBase {
private:
	long long moneyChange;
	double bonusRate;
public:
	PlatinumAugment(std::string n, std::string d, long long m, double r) : AugmentBase(n, d, 2), moneyChange(m), bonusRate(r) {}
	void apply(Player& p, DebtSystem& d) override {
		p.addMoney(moneyChange);
		p.addBonusRate(bonusRate);
	}
};

// --- 증강 관리 매니저 ---
class AugmentManager {
private:
	int luckLevel;      // 0 ~ 3 단계 확률 테이블
	bool condCertSeen;  // 자격증 조건 달성 플래그
	bool condRepaySeen; // 상환액 조건 달성 플래그
	bool condJobSeen;   // 알바 조건 달성 플래그

public:
	AugmentManager();

	void addLuckLevel() { if (luckLevel < 3) luckLevel++; }
	int getLuckLevel() const { return luckLevel; }

	bool isCertConditionMet() const { return condCertSeen; }
	void setCertConditionMet() { condCertSeen = true; }

	bool isRepayConditionMet() const { return condRepaySeen; }
	void setRepayConditionMet() { condRepaySeen = true; }

	bool isJobConditionMet() const { return condJobSeen; }
	void setJobConditionMet() { condJobSeen = true; }

	void runAugmentSelection(Player& p, DebtSystem& d);

private:
	std::vector<std::unique_ptr<AugmentBase>> generateChoices();
};