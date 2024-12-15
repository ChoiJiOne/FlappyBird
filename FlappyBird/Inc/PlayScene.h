#pragma once

#include <map>
#include <vector>
#include <functional>

#include "IEntity.h"
#include "InputManager.h"
#include "IScene.h"


/**
 * @brief 플레이 씬입니다.
 */
class PlayScene : public IScene
{
public:
	/**
	 * @brief 플레이 씬의 디폴트 생성자입니다.
	 */
	PlayScene() = default;


	/**
	 * @brief 플레이 씬의 가상 소멸자입니다.
	 */
	virtual ~PlayScene() {}


	/**
	 * @brief 플레이 씬의 복사 생성자 및 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(PlayScene);


	/**
	 * @brief 플레이 씬의 한 프레임을 수행합니다.
	 *
	 * @param deltaSeconds 초 단위 델타 시간값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief 플레이 씬에 진입합니다.
	 */
	virtual void Enter() override;


	/**
	 * @brief 플레이 씬에서 나갑니다.
	 */
	virtual void Exit() override;


	/**
	 * @brief 게임 난이도에 따른 속도를 설정합니다.
	 * 
	 * @param gameSpeed 설정할 게임 속도입니다.
	 */
	void SetGameSpeed(float gameSpeed) { gameSpeed_ = gameSpeed; }


	/**
	 * @brief 백그라운드 엔티티의 ID 값을 설정합니다.
	 * 
	 * @param id 설정할 백그라운드 엔티티의 ID 값입니다.
	 */
	void SetBackgroundID(const EUID& id) { backgroundID_ = id; }


	/**
	 * @brief 바닥 엔티티의 ID 값을 설정합니다.
	 *
	 * @param id 설정할 바닥 엔티티의 ID 값입니다.
	 */
	void SetLandID(const EUID& id) { landID_ = id; }


	/**
	 * @brief 새 엔티티의 ID 값을 설정합니다.
	 * 
	 * @param id 설정할 새 엔티티의 ID 값입니다.
	 */
	void SetBirdID(const EUID& id) { birdID_ = id; }


	/**
	 * @brief 랭킹 씬을 연결합니다.
	 * 
	 * @param rankScene 설정할 랭킹 씬의 포인터입니다.
	 */
	void SetRankScene(IScene* rankScene) { rankScene_ = rankScene; }


private:
	/**
	 * @brief 랭킹 씬입니다.
	 */
	IScene* rankScene_ = nullptr;


	/**
	 * @brief 게임이 중지되었는지 확인합니다.
	 */
	bool bIsPause_ = false;


	/**
	 * @brief 카운트 다운입니다.
	 */
	float countDown_ = 3.0f;


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
	 * @brief 파이프 컨트롤러 엔티티의 ID 값입니다.
	 */
	EUID pipeController_ = -1;


	/**
	 * @brief 새 엔티티의 ID 값입니다.
	 */
	EUID birdID_ = -1;


	/**
	 * @brief 스코어 뷰어 엔티티의 ID 값입니다.
	 */
	EUID scoreViewerID_ = -1;


	/**
	 * @brief 중지 상태를 표시할 엔티티의 ID 값입니다.
	 */
	EUID pauseViewerID_ = -1;


	/**
	 * @brief 엔티티 목록입니다.
	 */
	std::vector<EUID> entityIDs_;


	/**
	 * @brief 플레이 씬 내의 이벤트입니다.
	 */
	std::map<EWindowEvent, WINDOW_EVENT_UID> sceneEvents_;
};