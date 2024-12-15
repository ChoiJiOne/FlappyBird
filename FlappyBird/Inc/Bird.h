#pragma once

#include <array>

#include "BoundCircle2D.h"
#include "IEntity.h"
#include "IResource.h"


/**
 * @brief 새 엔티티입니다.
 */
class Bird : public IEntity
{
public:
	/**
	 * @brief 새의 상태를 나타내는 열거형입니다.
	 */
	enum class EStatus : int32_t
	{
		Ready = 0x00,
		Fly   = 0x01,
		Dead  = 0x02,
		Done  = 0x03,
	};


public:
	/**
	 * @brief 새 엔티티의 생성자입니다.
	 */
	explicit Bird();


	/**
	 * @brief 새 엔티티의 가상 소멸자입니다.
	 */
	virtual ~Bird();


	/**
	 * @brief 새 엔티티의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Bird);


	/**
	 * @brief 새를 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief 새를 화면에 그립니다.
	 */
	virtual void Render() override;


	/**
	 * @brief 새 엔티티 내의 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


	/**
	 * @brief 새 엔티티의 상태를 얻습니다.
	 * 
	 * @return 새 엔티티의 상태를 반환합니다.
	 */
	EStatus GetStatus() const { return status_; }


	/**
	 * @brief 파이프 컨트롤러 ID를 설정합니다.
	 * 
	 * @param pipeControllerID 설정할 파이프 컨트롤러 ID입니다.
	 */
	void SetPipeControllerID(const EUID& pipeControllerID) { pipeControllerID_ = pipeControllerID; }


	/**
	 * @brief 바닥 ID를 설정합니다.
	 * 
	 * @param landID 설정할 바닥 ID입니다.
	 */
	void SetLandID(const EUID& landID) { landID_ = landID; }


	/**
	 * @brief 백그라운드 ID를 설정합니다.
	 * 
	 * @param backgroundID 설정할 백그라운드 ID입니다.
	 */
	void SetBackgroundID(const EUID& backgroundID) { backgroundID_ = backgroundID; }


	/**
	 * @brief 새의 스코어를 얻습니다.
	 * 
	 * @return 새의 스코어를 반환합니다.
	 */
	int32_t GetScore() const { return score_; }


	/**
	 * @brief 새의 시작 위치를 설정합니다.
	 * 
	 * @param startLocation 설정할 시작 위치입니다.
	 */
	static void SetStartLocation(const Vec2f& startLocation) { startLocation_ = startLocation; }


private:
	/**
	 * @brief 새의 Ready 상태를 업데이트합니다.
	 * 
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	void TickReadyStatus(float deltaSeconds);


	/**
	 * @brief 새의 Fly 상태를 업데이트합니다.
	 * 
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	void TickFlyStatus(float deltaSeconds);


	/**
	 * @brief 새의 Dead 상태를 업데이트합니다.
	 * 
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	void TickDeadStatus(float deltaSeconds);


private:
	/**
	 * @brief 현재 새의 상태입니다.
	 */
	EStatus status_ = EStatus::Ready;


	/**
	 * @brief 새의 가로 크기입니다.
	 */
	float width_ = 0.0f;


	/**
	 * @brief 새의 세로 크기입니다.
	 */
	float height_ = 0.0f;


	/**
	 * @brief 새의 최소 회전 각도입니다.
	 */
	float minRotate_ = 0.0f;


	/**
	 * @brief 새의 최대 회전 각도입니다.
	 */
	float maxRotate_ = 0.0f;


	/**
	 * @brief 새의 회전 각도입니다.
	 */
	float rotate_ = 0.0f;


	/**
	 * @brief 새의 최대 속도입니다.
	 */
	float maxSpeed_ = 0.0f;


	/**
	 * @brief 새의 현재 속도입니다.
	 */
	float currentSpeed_ = 0.0f;


	/**
	 * @brief 새의 감속 속도입니다.
	 */
	float dampingSpeed_ = 0.0f;


	/**
	 * @brief 새의 경계 영역입니다.
	 */
	BoundCircle2D bound_;


	/**
	 * @brief 새의 애니메이션 시간입니다.
	 */
	float animationTime_ = 0.0f;


	/**
	 * @brief 새의 최대 애니메이션 시간입니다.
	 */
	float maxAnimationTime_ = 0.0f;


	/**
	 * @brief 현재 새의 텍스처 리소스 인덱스입니다.
	 */
	std::size_t index_ = 0;


	/**
	 * @brief 새의 텍스처입니다.
	 */
	std::array<RUID, 4> textureIDs_;


	/**
	 * @brief 새의 스코어입니다.
	 */
	int32_t score_ = 0;


	/**
	 * @brief 파이프 컨트롤러의 ID입니다.
	 */
	EUID pipeControllerID_ = -1;


	/**
	 * @brief 바닥의 ID 입니다.
	 */
	EUID landID_ = -1;


	/**
	 * @brief 백그라운드의 ID입니다.
	 */
	EUID backgroundID_ = -1;


	/**
	 * @brief 새가 날개짓을 했을 때 출력할 사운드 리소스 ID입니다.
	 */
	RUID wingSoundID_ = -1;


	/**
	 * @brief 새가 파이프를 통과했을 때 출력할 사운드 리소스 ID입니다.
	 */
	RUID pointSoundID_ = -1;


	/**
	 * @brief 새가 파이프나 바닥과 부딪혔을 때 출력할 사운드 리소스입니다.
	 */
	RUID hitSoundID_ = -1;


	/**
	 * @brief 새가 죽었을 때 출력할 사운드 리소스입니다.
	 */
	RUID dieSoundID_ = -1;
	

	/**
	 * @brief 새의 시작 위치입니다.
	 */
	static Vec2f startLocation_;
};