#include "Player.h"

/**
 * 생성자
 * 게임 시작 시 초기 자산 및 급여 설정을 담당합니다.
 */
Player::Player()
	: money(100000),                // 시작 머니 0원
	baseSalary(100000),      // 초기 기본급 10만원 (자격증 0레벨 기준)
	bonusRate(1.0)           // 초기 보너스 배율 1.0 (100%)
{
}

/**
 * 보너스 배율 추가 (증강 또는 알바 계약 시 호출)
 * 기존 배율에 새로운 배율을 누적하여 더합니다.
 * 예: 1.0(기본) + 0.05(골드증강) = 1.05 (105% 수익)
 */
void Player::addBonusRate(double r) {
	this->bonusRate += r;
}

/**
 * 일일 예상 수익 계산
 * 현재 기본급과 누적된 보너스 배율을 곱하여 최종 수익을 반환합니다.
 * double 연산 후 long long으로 형변환하여 소수점을 버립니다.
 */
long long Player::calculateDailyIncome() const {
	// 기본급 * 보너스 배율 (예: 1,000,000 * 1.25 = 1,250,000)
	return static_cast<long long>(baseSalary * bonusRate);
}

/**
 * 보유 금액 설정
 * 빚 상환이나 아이템 구매 시 직접 금액을 변경할 때 사용합니다.
 */
void Player::setMoney(long long m) {
	this->money = m;
}

/**
 * 보유 금액 추가/차감
 * 수익 발생이나 소득/지출 증강 시 사용합니다.
 */
void Player::addMoney(long long m) {
	this->money += m;
}

/**
 * 기본급 설정 (자격증 취득 시 호출)
 */
void Player::setBaseSalary(long long s) {
	this->baseSalary = s;
}