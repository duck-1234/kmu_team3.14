#pragma once
#include <string>
#include <vector>
#include "CommonUtils.h"
#include "GameMenu.h"
#include "StoryManager.h"
#include "DebtSystem.h"
#include "Player.h"
#include "WorkManager.h"
#include "AugmentManager.h"
#include "HelpManager.h"
#include "type.h"

class GameManager {
private:
	GameMenu menu;
	StoryManager story;
	DebtSystem debt;
	Player player;
	JobManager jobMgr;
	UpgradeManager upgradeMgr;
	RepayManager repayMgr;
	AugmentManager augmentMgr;
	HelpManager helpMgr;

	bool isGameOver = false;
	bool isGameClear = false;

	// [추가] 노동 시스템 관련 변수들
	int dailyWorkCount = 0;   // 오늘 노동한 횟수
	int laborLevel = 1;       // 노동 장비 레벨
	long long laborReward = 50000; // 현재 1회 성공 보상금
	int maxLaborCount = 3;    // 하루 최대 가능 횟수

public:
	GameManager();
	void run();

private:
	void initGame();
	int displayDashboard();
	void checkLevelUp();
	void processNextDay();
	void checkGameEndConditions();
	void runLaborUpgrade(); // [추가] 노동력 강화 전용 메뉴
};