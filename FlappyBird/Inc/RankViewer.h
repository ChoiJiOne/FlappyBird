#pragma once

#include "Vec2.h"

#include "IEntity.h"
#include "IResource.h"


/**
 * @brief 랭킹을 표시하는 엔티티입니다.
 */
class RankViewer : public IEntity
{
public:
	/**
	 * @brief 랭킹을 표시하는 엔티티의 생성자입니다.
	 * 
	 * @param fontID 텍스트를 렌더링할 때 참조할 폰트 ID입니다.
	 */
	explicit RankViewer(const RUID& fontID);


	/**
	 * @brief 랭킹을 표시하는 엔티티의 가상 소멸자입니다.
	 */
	virtual ~RankViewer();


	/**
	 * @brief 랭킹을 표시하는 엔티티의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(RankViewer);


	/**
	 * @brief 랭킹을 표시하는 엔티티를 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief 랭킹을 표시하는 엔티티를 화면에 그립니다.
	 */
	virtual void Render() override;


	/**
	 * @brief 랭킹을 표시하는 엔티티 내의 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


private:
	/**
	 * @brief GameOver 텍스처입니다.
	 */
	RUID gameOverID_ = -1;


	/**
	 * @brief GameOver 텍스처의 위치입니다.
	 */
	Vec2f gameOverLocation_;


	/**
	 * @brief GameOver 텍스처의 가로 크기입니다.
	 */
	float gameOverWidth_ = 0.0f;


	/**
	 * @brief GameOver 텍스처의 세로 크기입니다.
	 */
	float gameOverHeight_ = 0.0f;
	

	/**
	 * @brief 누적 시간값입니다.
	 */
	float accumulateTime_ = 0.0f;


	/**
	 * @brief 텍스트 표시에 사용할 폰트 리소스입니다.
	 */
	RUID fontID_ = -1;


	/**
	 * @brief 현재 레벨입니다.
	 */
	std::wstring currentLevel_;


	/**
	 * @brief 현재 레벨을 표시할 위치입니다.
	 */
	Vec2f currentLevelLocation_;


	/**
	 * @brief 현재 스코어입니다.
	 */
	std::wstring currentScore_;


	/**
	 * @brief 현재 스코어를 표시할 위치입니다.
	 */
	Vec2f currentScoreLocation_;


	/**
	 * @brief 최고 스코어입니다.
	 */
	std::wstring bestScore_;


	/**
	 * @brief 최고 스코어를 표시할 위치입니다.
	 */
	Vec2f bestScoreLocation_;


	/**
	 * @brief 최고 기록이 갱신되었는지 확인합니다.
	 */
	bool bIsUpdateBest_ = false;
};