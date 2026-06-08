#pragma once
#include <vector>
#include <string>

struct Scene {
	std::string asciiArt;
	std::string description;
};

class StoryManager {
private:
	std::vector<Scene> scenes;

public:
	StoryManager();
	void play();
};