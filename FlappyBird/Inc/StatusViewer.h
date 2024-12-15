#pragma once

#include <string>
#include <map>

#include "Vec2.h"
#include "Vec4.h"

#include "ConfigManager.h"
#include "IEntity.h"
#include "IResource.h"


/**
 * @brief 게임 상태를 보여주는 엔티티입니다.
 */
class StatusViewer : public IEntity
{
public:
	/**
	 * @brief 게임 상태를 보여주는 엔티티의 생성자입니다.
	 * 
	 * @param fontID 폰트 리소스 ID입니다.
	 */
	explicit StatusViewer(const RUID& fontID);


	/**
	 * @brief 게임 상태를 보여주는 엔티티의 가상 소멸자입니다.
	 */
	virtual ~StatusViewer();


	/**
	 * @brief 게임 상태를 보여주는 엔티티의 복사 생성자 및 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(StatusViewer);


	/**
	 * @brief 게임 상태를 보여주는 엔티티을 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief 게임 상태를 보여주는 엔티티을 화면에 그립니다.
	 */
	virtual void Render() override;


	/**
	 * @brief 게임 상태를 보여주는 엔티티 내의 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


private:
	/**
	 * @brief 텍스트의 폰트입니다.
	 */
	RUID fontID_ = -1;


	/**
	 * @brief 설정 레벨에 맞는 텍스트입니다.
	 */
	std::map<ConfigManager::ELevel, std::wstring> levels_;
	

	/**
	 * @brief 설정 새 타입에 맞는 리소스입니다.
	 */
	std::map<ConfigManager::EBird, RUID> birdIDs_;
};