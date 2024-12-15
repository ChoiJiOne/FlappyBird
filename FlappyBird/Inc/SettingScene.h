#pragma once

#include <functional>
#include <vector>

#include "IEntity.h"
#include "IScene.h"


/**
 * @brief 세팅 씬입니다.
 */
class SettingScene : public IScene
{
public:
	/**
	 * @brief 세팅 씬의 디폴트 생성자입니다.
	 */
	SettingScene() = default;


	/**
	 * @brief 세팅 씬의 가상 소멸자입니다.
	 */
	virtual ~SettingScene() {}


	/**
	 * @brief 세팅 씬의 복사 생성자 및 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(SettingScene);


	/**
	 * @brief 세팅 씬의 한 프레임을 수행합니다.
	 *
	 * @param deltaSeconds 초 단위 델타 시간값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief 세팅 씬에 진입합니다.
	 */
	virtual void Enter() override;


	/**
	 * @brief 세팅 씬에서 나갑니다.
	 */
	virtual void Exit() override;


	/**
	 * @brief 시작 씬을 연결합니다.
	 *
	 * @param startScene 설정할 시작 씬의 포인터입니다.
	 */
	void SetStartScene(IScene* startScene) { startScene_ = startScene; }


private:
	/**
	 * @brief 시작 씬 입니다.
	 */
	IScene* startScene_ = nullptr;

	
	/**
	 * @brief 엔티티 목록입니다.
	 */
	std::vector<EUID> entities_;
};