#pragma once
#include <vector>
#include <string>

// 도움말 항목을 저장하는 구조체
struct HelpItem {
    std::string title;
    std::string description;
};

class HelpManager {
private:
    std::vector<HelpItem> helpList;

public:
    HelpManager();
    void runMenu(); // 도움말 메뉴를 실행하는 함수
};
