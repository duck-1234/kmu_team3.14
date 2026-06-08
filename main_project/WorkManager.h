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
	// [핵심 수정] 인터페이스 통일: 모든 자식은 반드시 player와 debt를 함께 받아야 함
	virtual void runMenu(Player& p, DebtSystem& d) = 0;
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
	// [수정] 매개변수 통일 (DebtSystem 추가)
	void runMenu(Player& p, DebtSystem& d) override;

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
	// [수정] 매개변수 통일 (DebtSystem 추가)
	void runMenu(Player& p, DebtSystem& d) override;

	// 현재 레벨 반환 (main.cpp 오류 E0135 해결)
	int getUpgradeLevel() const { return upgradeLevel; }
};

// --- 채무 상환 매니저 ---
class RepayManager : public WorkBase {
public:
	// [수정] 불필요하게 2개로 나뉘어 있던 runMenu를 하나로 통합하여 완벽한 오버라이딩 적용
	void runMenu(Player& p, DebtSystem& d) override;
};