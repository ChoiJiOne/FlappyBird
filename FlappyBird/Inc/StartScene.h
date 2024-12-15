#pragma once

#include <functional>
#include <vector>

#include "IEntity.h"
#include "IScene.h"


/**
 * @brief 시작 씬입니다.
 */
class StartScene : public IScene
{
public:
	/**
	 * @brief 시작 씬의 디폴트 생성자입니다.
	 */
	StartScene() = default;


	/**
	 * @brief 시작 씬의 가상 소멸자입니다.
	 */
	virtual ~StartScene() {}


	/**
	 * @brief 시작 씬의 복사 생성자 및 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(StartScene);


	/**
	 * @brief 시작 씬의 한 프레임을 수행합니다.
	 *
	 * @param deltaSeconds 초 단위 델타 시간값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief 시작 씬에 진입합니다.
	 */
	virtual void Enter() override;


	/**
	 * @brief 시작 씬에서 나갑니다.
	 */
	virtual void Exit() override;


	/**
	 * @brief 루프 종료 이벤트를 설정합니다.
	 * 
	 * @param quitLoopEvent 설정할 루프 종료 이벤트입니다.
	 */
	void SetQuitLoopEvent(const std::function<void()>& quitLoopEvent) { quitLoopEvent_ = quitLoopEvent;	}


	/**
	 * @brief 준비 씬을 연결합니다.
	 * 
	 * @param readyScene 설정할 준비 씬의 포인터입니다.
	 */
	void SetReadyScene(IScene* readyScene) { readyScene_ = readyScene; }


	/**
	 * @brief 설정 씬을 연결합니다.
	 * 
	 * @param settingScene 설정할 설정 씬의 포인터입니다.
	 */
	void SetSettingScene(IScene* settingScene) { settingScene_ = settingScene; }


private:
	/**
	 * @brief 루프 종료 이벤트입니다.
	 */
	std::function<void()> quitLoopEvent_;


	/**
	 * @brief 준비 씬 입니다.
	 */
	IScene* readyScene_ = nullptr;


	/**
	 * @brief 세팅 씬입니다.
	 */
	IScene* settingScene_ = nullptr;


	/**
	 * @brief 엔티티 목록입니다.
	 */
	std::vector<EUID> entities_;
};