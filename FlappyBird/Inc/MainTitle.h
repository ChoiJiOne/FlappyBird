#pragma once

#include <vector>

#include "Panel.h"


/**
 * @brief 메인 타이틀 엔티티입니다.
 */
class MainTitle : public Panel
{
public:
	/**
	 * @brief 메인 타이틀의 생성자입니다.
	 * 
	 * @param fontID 메인 타이틀의 폰트 리소스 ID입니다.
	 */
	explicit MainTitle(const RUID& fontID);

	
	/**
	 * @brief 메인 타이틀의 가상 소멸자입니다.
	 */
	virtual ~MainTitle();


	/**
	 * @brief 메인 타이틀의 복사 생성자 및 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(MainTitle);


	/**
	 * @brief 메인 타이틀을 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief 메인 타이틀을 화면에 그립니다.
	 */
	virtual void Render() override;


	/**
	 * @brief 메인 타이틀 내의 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;
	

private:
	/**
	 * @brief 메인 타이틀의 문자 색상 목록입니다.
	 */
	std::vector<Vec4f> colors_;


	/**
	 * @brief 새의 위치입니다.
	 */
	Vec2f birdPosition_;


	/**
	 * @brief 새의 가로 크기입니다.
	 */
	float birdWidth_ = 0.0f;


	/**
	 * @brief 새의 세로 크기입니다.
	 */
	float birdHeight_ = 0.0f;


	/**
	 * @brief 새의 날개짓 시간입니다.
	 */
	float flyTime_ = 0.09f;


	/**
	 * @brief 새의 날개짓을 위한 누적 시간입니다.
	 */
	float accumulateFlyTime_ = 0.0f;


	/**
	 * @brief 현재 새 리소스 인덱스입니다.
	 */
	std::size_t birdIndex_ = 0;


	/**
	 * @brief 메인 타이틀에서 사용할 새 리소스 목록입니다.
	 */
	std::vector<RUID> birds_;


	/**
	 * @brief 텍스트 그림자 효과를 위한 바이어스입니다.
	 */
	float bias_ = 5.0f;


	/**
	 * @brief 전체 누적 시간값입니다.
	 */
	float accumulateTime_ = 0.0f;


	/**
	 * @brief 누적 시간값입니다.
	 */
	float updateAccumulateTime_ = 0.0f;


	/**
	 * @brief 최대 누적 시간값입니다.
	 */
	float maxAccumulateTime_ = 1.0f;
};