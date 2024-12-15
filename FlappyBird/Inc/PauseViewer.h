#pragma once

#include <string>
#include <functional>

#include "IEntity.h"
#include "IResource.h"


/**
 * @brief 게임 중지 상태를 표시하는 엔티티입니다.
 */
class PauseViewer : public IEntity
{
public:
	/**
	 * @brief 게임 중지 상태를 표시하는 엔티티의 생성자입니다.
	 * 
	 * @param fontID 텍스트 렌더링 시 사용할 폰트 리소스의 ID입니다.
	 */
	explicit PauseViewer(const RUID& fontID);


	/**
	 * @brief 게임 중지 상태를 표시하는 엔티티의 가상 소멸자입니다.
	 */
	virtual ~PauseViewer();


	/**
	 * @brief 게임 중지 상태를 표시하는 엔티티의 복사 생성자 및 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(PauseViewer);


	/**
	 * @brief 게임 중지 상태를 표시하는 엔티티를 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief 게임 중지 상태를 표시하는 엔티티를 화면에 그립니다.
	 */
	virtual void Render() override;


	/**
	 * @brief 게임 중지 상태를 표시하는 엔티티 내의 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


	/**
	 * @brief 중지 상태를 다시 재개할 이벤트를 설정합니다.
	 * 
	 * @param continueEvent 설정할 이벤트입니다.
	 */
	void SetContinueEvent(const std::function<void()>& continueEvent) { continueEvent_ = continueEvent; }


private:
	/**
	 * @brief 텍스트 렌더링 시 사용할 폰트 리소스의 ID입니다.
	 */
	RUID fontID_ = -1;


	/**
	 * @brief 화면에 표시할 텍스트의 위치입니다.
	 */
	Vec2f center_;


	/**
	 * @brief 화면에 표시할 텍스트입니다.
	 */
	std::wstring text_;


	/**
	 * @brief 중지 상태를 다시 재개할 이벤트입니다.
	 */
	std::function<void()> continueEvent_;
};