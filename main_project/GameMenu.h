#pragma once
#include <vector>
#include <string>

class GameMenu {
private:
	int selectedIndex;
	std::vector<std::string> menuItems;

public:
	GameMenu();
	void drawMenu();
	int run();
};