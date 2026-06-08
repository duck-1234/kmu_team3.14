#pragma once
#include <vector>
#include <string>
#include "Player.h"
#include "DebtSystem.h"

// --- 업무 시스템 부모 클래스 ---
class WorkBase {
protected:
	void drawHeader(const std::string& title, long long playerMoney);
	void drawFooter();
public:
	virtual ~WorkBase() {}
	virtual void runMenu(Player& p) = 0;
};

// --- 아르바이트 매니저 ---
struct Job {
	std::string name;
	long long cost;
	double rateBoost;
	bool isOwned;
};

class JobManager : public WorkBase {
private:
	std::vector<Job> jobs;
	bool isAllJobsMastered() const;

public:
	JobManager();
	void runMenu(Player& p) override;

	// 증강 해금 조건 체크용 (마스터한 알바 개수 반환)
	int getMasteredCount() const {
		int count = 0;
		for (const auto& j : jobs) { if (j.isOwned) count++; }
		return count;
	}
};

// --- 자격증 매니저 ---
struct UpgradeData {
	long long cost;
	long long targetSalary;
	std::string certName;
};

class UpgradeManager : public WorkBase {
private:
	int upgradeLevel;
	std::vector<UpgradeData> upgradeTable;
public:
	UpgradeManager();
	void runMenu(Player& p) override;

	// 현재 레벨 반환 (main.cpp 오류 E0135 해결)
	int getUpgradeLevel() const { return upgradeLevel; }
};

// --- 채무 상환 매니저 ---
class RepayManager : public WorkBase {
public:
	void runMenu(Player& p) override {}
	void runMenu(Player& p, DebtSystem& d);
};