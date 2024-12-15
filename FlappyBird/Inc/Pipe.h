#pragma once

#include "BoundBox2D.h"
#include "IEntity.h"
#include "IResource.h"


/**
 * @brief 파이프 엔티티입니다.
 */
class Pipe : public IEntity
{
public:
	/**
	 * @brief 파이프의 상태를 나타내는 열거형입니다.
	 */
	enum class EStatus : int32_t
	{
		Wait   = 0x00, // 대기 상태입니다.
		Active = 0x01, // 움직이고 있는 상태입니다.
	};


public:
	/**
	 * @brief 파이프 엔티티의 생성자입니다.
	 * 
	 * @param speed 파이프의 움직임 속도입니다.
	 */
	explicit Pipe(float speed);


	/**
	 * @brief 파이프 엔티티의 가상 소멸자입니다.
	 */
	virtual ~Pipe();


	/**
	 * @brief 파이프 엔티티의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Pipe);


	/**
	 * @brief 파이프를 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief 파이프를 화면에 그립니다.
	 */
	virtual void Render() override;


	/**
	 * @brief 파이프 내의 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


	/**
	 * @brief 파이프가 움직일 수 있는지 확인합니다.
	 *
	 * @return 파이프가 움직일 수 있다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool CanMove() const { return bCanMove_; }


	/**
	 * @brief 파이프의 움직임 여부를 설정합니다.
	 *
	 * @param bCanMove 설정할 파이프 움직임 여부입니다.
	 */
	void SetCanMove(bool bCanMove) { bCanMove_ = bCanMove; }


	/**
	 * @brief 파이프의 상태를 얻습니다.
	 * 
	 * @return 파이프의 상태값을 반환합니다.
	 */
	EStatus GetStatus() const { return status_; }


	/**
	 * @brief 파이프의 상태를 설정합니다.
	 * 
	 * @param status 파이프의 상태를 설정합니다.
	 */
	void SetStatus(const EStatus& status) { status_ = status; }


	/**
	 * @brief 파이프의 위치를 재설정합니다.
	 */
	void ResetLocation();


	/**
	 * @brief 다른 파이프와의 간격을 얻습니다.
	 */
	float GetGapPipe(const Pipe* pipe);


	/**
	 * @brief 파이프의 상단 경계 영역을 얻습니다.
	 * 
	 * @return 파이프의 상단 경계 영역 포인터를 반환합니다.
	 */
	const IBound2D* GetTopBound() const { return &topBound_; }


	/**
	 * @brief 파이프의 하단 경계 영역을 얻습니다.
	 * 
	 * @return 파이프의 하단 경계 영역 포인터를 반환합니다.
	 */
	const IBound2D* GetBottomBound() const { return &bottomBound_; }


	/**
	 * @brief 파이프의 점수 처리를 위한 스코어 경계 영역을 파괴합니다.
	 */
	void DestroyScoreBound() { bIsDestroy_ = true; }


	/**
	 * @brief 파이프의 점수 처리를 위한 경계 영역을 얻습니다.
	 * 
	 * @return 파이프의 점수 처리를 위한 경계 영역의 포인터를 반환합니다.
	 */
	const IBound2D* GetScoreBound() const;
	

	/**
	 * @brief 파이프의 시작 위치를 설정합니다.
	 * 
	 * @param startLocation 설정할 파이프의 시작 위치입니다.
	 */
	static void SetStartLocation(const Vec2f& startLocation) { startLocation_ = startLocation; }


	/**
	 * @brief 파이프의 끝 위치를 설정합니다.
	 * 
	 * @param endLocation 설정할 파이프의 끝 위치입니다.
	 */
	static void SetEndLocation(const Vec2f& endLocation) { endLocation_ = endLocation; }
	

private:
	/**
	 * @brief 파이프가 움직일 수 있는지 확인합니다.
	 */
	bool bCanMove_ = false;


	/**
	 * @brief 스코어 보드가 파괴되었는지 확인합니다.
	 */
	bool bIsDestroy_ = false;


	/**
	 * @brief 파이프의 움직임 속도입니다.
	 */
	float speed_ = 0.0f;


	/**
	 * @brief 현재 파이프의 상태입니다.
	 */
	EStatus status_ = EStatus::Wait;


	/**
	 * @brief 상단 파이프의 경계 영역입니다.
	 */
	BoundBox2D topBound_;


	/**
	 * @brief 하단 파이프의 경계 영역입니다.
	 */
	BoundBox2D bottomBound_;


	/**
	 * @brief 파이프의 점수 처리를 위한 경계 영역입니다.
	 */
	BoundBox2D scoreBound_;


	/**
	 * @brief 파이프의 텍스처 리소스입니다.
	 */
	RUID textureID_ = -1;

	
	/**
	 * @brief 파이프의 시작 위치입니다.
	 */
	static Vec2f startLocation_;


	/**
	 * @brief 파이프의 끝 위치입니다.
	 */
	static Vec2f endLocation_;
};