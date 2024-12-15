#pragma once

#include "BoundBox2D.h"
#include "IEntity.h"
#include "IResource.h"


/**
 * @brief 백그라운드 엔티티입니다.
 */
class Background : public IEntity
{
public:
	/**
	 * @brief 백그라운드 엔티티의 생성자입니다.
	 */
	explicit Background();


	/**
	 * @brief 백그라운드 엔티티의 생성자입니다.
	 * 
	 * @param scrollSpeed 백그라운드의 스크롤 속도입니다.
	 */
	explicit Background(float scrollSpeed);


	/**
	 * @brief 백그라운드 엔티티의 가상 소멸자입니다.
	 */
	virtual ~Background();


	/**
	 * @brief 백그라운드 엔티티의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Background);


	/**
	 * @brief 백그라운드를 업데이트합니다.
	 * 
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief 백그라운드를 화면에 그립니다.
	 */
	virtual void Render() override;


	/**
	 * @brief 백그라운드 내의 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


	/**
	 * @brief 백그라운드가 움직일 수 있는지 확인합니다.
	 * 
	 * @return 백그라운드가 움직일 수 있다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool CanMove() const { return bCanMove_; }


	/**
	 * @brief 백그라운드의 움직임 여부를 설정합니다.
	 * 
	 * @param bCanMove 설정할 백그라운드 움직임 여부입니다.
	 */
	void SetCanMove(bool bCanMove) { bCanMove_ = bCanMove; }


	/**
	 * @brief 백그라운드의 경계 영역을 얻습니다.
	 * 
	 * @return 백그라운드의 경계 영역 포인터를 반환합니다.
	 */
	const IBound2D* GetBound() const { return &bound_; }


private:
	/**
	 * @brief 백그라운드가 움직일 수 있는지 확인합니다.
	 */
	bool bCanMove_ = false;


	/**
	 * @brief 백그라운드의 스크롤 위치입니다.
	 */
	float scrollX_ = 0.0f;


	/**
	 * @brief 백그라운드의 최대 스크롤 위치입니다.
	 */
	float maxScrollX_ = 0.0f;


	/**
	 * @brief 백그라운드의 스크롤 속도입니다.
	 * 
	 * @note 속도의 단위는 픽셀/초 입니다.
	 */
	float scrollSpeed_ = 0.0f;


	/**
	 * @brief 백그라운드 텍스처 리소스의 ID입니다.
	 */
	RUID textureID_ = -1;


	/**
	 * @brief 백그라운드의 경계 영역입니다.
	 */
	BoundBox2D bound_;
};