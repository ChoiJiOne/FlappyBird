#pragma once

#include <vector>

#include "IEntity.h"
#include "IScene.h"


/**
 * @brief 준비(Ready) 씬입니다.
 */
class ReadyScene : public IScene
{
public:
	/**
	 * @brief 준비(Ready) 씬의 디폴트 생성자입니다.
	 */
	ReadyScene() = default;


	/**
	 * @brief 준비(Ready) 씬의 가상 소멸자입니다.
	 */
	virtual ~ReadyScene() {}


	/**
	 * @brief 준비(Ready) 씬의 복사 생성자 및 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(ReadyScene);


	/**
	 * @brief 준비(Ready) 씬의 한 프레임을 수행합니다.
	 *
	 * @param deltaSeconds 초 단위 델타 시간값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief 준비(Ready) 씬에 진입합니다.
	 */
	virtual void Enter() override;


	/**
	 * @brief 준비(Ready) 씬에서 나갑니다.
	 */
	virtual void Exit() override;


	/**
	 * @brief 플레이 씬을 연결합니다.
	 *
	 * @param playScene 설정할 플레이 씬의 포인터입니다.
	 */
	void SetPlayScene(IScene* playScene) { playScene_ = playScene; }


private:
	/**
	 * @brief 다음 플레이 씬 입니다.
	 */
	IScene* playScene_ = nullptr;


	/**
	 * @brief 백그라운드 스크롤 속도입니다.
	 */
	const float backgroundScrollSpeed_ = 50.0f;


	/**
	 * @brief 게임 난이도에 따른 속도입니다.
	 */
	float gameSpeed_ = 0.0f;


	/**
	 * @brief 백그라운드 엔티티의 ID 값입니다.
	 */
	EUID backgroundID_ = -1;


	/**
	 * @brief 바닥 엔티티의 ID 값입니다.
	 */
	EUID landID_ = -1;


	/**
	 * @brief 새 엔티티의 ID 값입니다.
	 */
	EUID birdID_ = -1;


	/**
	 * @brief 준비(Ready) 상태를 표시하는 엔티티의 ID 값입니다.
	 */
	EUID readyViewer_ = -1;


	/**
	 * @brief 준비(Ready) 씬의 엔티티 목록입니다.
	 */
	std::vector<EUID> entityIDs_;
};