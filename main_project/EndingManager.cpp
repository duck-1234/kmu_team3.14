#include "EndingManager.h"
#include "CommonUtils.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

void EndingManager::drawEndingHeader(const std::string& title) {
	system("cls");
	std::cout << WIDTH_BORDER << std::endl;
	std::cout << "                            [ GAME ENDING ]" << std::endl;
	std::cout << "                           - " << title << " -" << std::endl;
	std::cout << WIDTH_BORDER << std::endl << std::endl;
}

void EndingManager::playEnding(EndingType type, long long finalMoney) {
	switch (type) {
	case EndingType::Bankruptcy:
		drawEndingHeader("기한 초과 및 파산");
		std::cout << "  [ 게임 오버 ]\n"
			<< "  눈덩이처럼 불어난 채무를 감당하지 못했습니다.\n"
			<< "  차가운 사채업자들이 문을 두드립니다.\n"
			<< "  당신의 빛나던 미래는 흔적도 없이 사라졌습니다.\n\n";
		break;

	case EndingType::GamblingAddiction:
		drawEndingHeader("도박 중독의 늪 (BAD ENDING)");
		std::cout << "  [ 빚은 모두 갚았지만... ]\n"
			<< "  당신은 합법적으로 모든 채무 관계를 정리했습니다.\n"
			<< "  하지만 쉽게 얻은 대박의 짜릿함을 잊지 못합니다.\n"
			<< "  결국 더 큰 판돈을 쥐고 다시 카지노로 향합니다.\n\n"
			<< "  ▶ 최종 자산: " << formatToKorean(finalMoney) << " (도박 자금으로 탕진 예정)\n\n";
		break;

	case EndingType::DonationAngel:
		drawEndingHeader("기부 천사: 새로운 삶 (HAPPY ENDING)");
		std::cout << "  [ 진정한 새 출발 ]\n"
			<< "  돈이 없어 고통받던 시절을 기억하는 당신은\n"
			<< "  어려운 이웃들을 위해 선뜻 손을 내밀었습니다.\n"
			<< "  빚 청산과 동시에 사회의 따뜻한 빛이 되었습니다.\n\n"
			<< "  ▶ 최종 자산: " << formatToKorean(finalMoney) << " (명예로운 사회 환원)\n\n";
		break;

	case EndingType::NormalSuccess:
		drawEndingHeader("정직한 노동의 결실 (NORMAL CLEAR)");
		std::cout << "  [ 50일의 기적 성취 ]\n"
			<< "  지옥 같던 빚더미에서 완전히 벗어났습니다!\n"
			<< "  땀 흘려 번 돈의 가치를 깨달은 당신은\n"
			<< "  다시는 도박을 돌아보지 않고 평범한 행복을 누립니다.\n\n"
			<< "  ▶ 최종 자산: " << formatToKorean(finalMoney) << "\n\n";
		break;
	}

	std::cout << THIN_BORDER << std::endl;
	std::cout << "                   [ 아무 키나 누르면 메인 메뉴로 돌아갑니다 ]";
	(void)_getch();
}