#pragma once

#include <array>

#include "Vec2.h"

#include "IEntity.h"
#include "IResource.h"


/**
 * @brief 스코어를 표시하는 엔티티입니다.
 */
class ScoreViewer : public IEntity
{
public:
	/**
	 * @brief 스코어를 표시하는 엔티티의 생성자입니다.
	 */
	explicit ScoreViewer();


	/**
	 * @brief 스코어를 표시하는 엔티티의 가상 소멸자입니다.
	 */
	virtual ~ScoreViewer();


	/**
	 * @brief 스코어를 표시하는 엔티티의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(ScoreViewer);


	/**
	 * @brief 스코어를 표시하는 엔티티를 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief 스코어를 표시하는 엔티티를 화면에 그립니다.
	 */
	virtual void Render() override;


	/**
	 * @brief 스코어를 표시하는 엔티티 내의 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


	/**
	 * @brief 새 엔티티의 ID 값을 설정합니다.
	 * 
	 * @param birdID 새 엔티티의 ID 값입니다.
	 */
	void SetBirdID(const EUID& birdID) { birdID_ = birdID; }


private:
	/**
	 * @brief 스코어를 표시할 때 사용할 숫자 텍스처입니다.
	 */
	std::array<RUID, 10> numberIDs_;


	/**
	 * @brief 스코어를 표시할 때 참조할 새 엔티티의 ID 값입니다.
	 */
	EUID birdID_ = -1;


	/**
	 * @brief 스코어의 중심 위치입니다.
	 */
	Vec2f center_;


	/**
	 * @brief 숫자 하나의 가로 크기입니다.
	 */
	float numberWidth_ = 0.0f;


	/**
	 * @brief 숫자 하나의 세로 크기입니다.
	 */
	float numberHeight_ = 0.0f;


	/**
	 * @brief 숫자 간의 간격 크기입니다.
	 */
	float numberGap_ = 0.0f;


	/**
	 * @brief 스코어 캐쉬 값입니다.
	 */
	int32_t scoreCache_ = -1;

	
	/**
	 * @brief 숫자 배열입니다.
	 */
	std::vector<int32_t> number_;
};