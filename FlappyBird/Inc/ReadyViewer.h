#pragma once

#include "Vec2.h"

#include "IEntity.h"
#include "IResource.h"


/**
 * @brief 준비(Ready) 상태를 표시하는 엔티티입니다.
 */
class ReadyViewer : public IEntity
{
public:
	/**
	 * @brief 준비(Ready) 상태를 표시하는 엔티티의 생성자입니다.
	 */
	explicit ReadyViewer();


	/**
	 * @brief 준비(Ready) 상태를 표시하는 엔티티의 가상 소멸자입니다.
	 */
	virtual ~ReadyViewer();


	/**
	 * @brief 준비(Ready) 상태를 표시하는 엔티티의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(ReadyViewer);


	/**
	 * @brief 준비(Ready) 상태를 표시하는 엔티티를 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief 준비(Ready) 상태를 표시하는 엔티티를 화면에 그립니다.
	 */
	virtual void Render() override;


	/**
	 * @brief 준비(Ready) 상태를 표시하는 엔티티 내의 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;
	

private:
	/**
	 * @brief 게임 플레이 정보를 표시할 텍스처입니다.
	 */
	RUID infoID_ = -1;


	/**
	 * @brief 게임 플레이 정보를 표시할 텍스처의 위치입니다.
	 */
	Vec2f infoLocation_;


	/**
	 * @brief 게임 플레이 정보를 표시할 텍스처의 가로 크기입니다.
	 */
	float infoWidth_ = 0.0f;


	/**
	 * @brief 게임 플레이 정보를 표시할 텍스처의 세로 크기입니다.
	 */
	float infoHeight_ = 0.0f;


	/**
	 * @brief Get Ready 텍스처입니다.
	 */
	RUID getReadyID_ = -1;


	/**
	 * @brief Get Ready 텍스처의 위치입니다.
	 */
	Vec2f getReadyLocation_;


	/**
	 * @brief Get Ready 텍스처의 가로 크기입니다.
	 */
	float getReadyWidth_ = 0.0f;


	/**
	 * @brief Get Ready 텍스처의 세로 크기입니다.
	 */
	float getReadyHeight_ = 0.0f;


	/**
	 * @brief 누적 시간값입니다.
	 */
	float accumulateTime_ = 0.0f;
};