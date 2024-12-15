#pragma once

#include <vector>

#include "IEntity.h"
#include "IResource.h"

class Pipe;


/**
 * @brief 파이프를 제어하는 컨트롤러 엔티티입니다.
 */
class PipeController : public IEntity
{
public:
	/**
	 * @brief 파이프를 제어하는 컨트롤러의 상태입니다.
	 */
	enum class EStatus : int32_t
	{
		Wait   = 0x00,
		Active = 0x01,
	};


public:
	/**
	 * @brief 파이프를 제어하는 컨트롤러 엔티티의 생성자입니다.
	 *
	 */
	explicit PipeController(const std::vector<Pipe*>& pipes, float gap);


	/**
	 * @brief 파이프를 제어하는 컨트롤러 엔티티의 가상 소멸자입니다.
	 */
	virtual ~PipeController();


	/**
	 * @brief 파이프를 제어하는 컨트롤러 엔티티의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(PipeController);


	/**
	 * @brief 파이프를 제어하는 컨트롤러를 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief 파이프를 제어하는 컨트롤러를 화면에 그립니다.
	 * 
	 * @note 이 엔티티는 아무 그리기도 수행하지 않습니다.
	 */
	virtual void Render() override;


	/**
	 * @brief 파이프를 제어하는 컨트롤러 내의 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


	/**
	 * @brief 파이프 컨트롤러의 상태를 설정합니다.
	 * 
	 * @param status 설정할 파이프 컨트롤러의 상태입니다.
	 */
	void SetStatus(const EStatus& status);


	/**
	 * @brief 파이프 컨트롤러가 제어하는 파이프 목록을 얻습니다.
	 * 
	 * @return 파이프 컨트롤러가 제어하는 파이프의 목록을 반환합니다.
	 */
	const std::vector<Pipe*>& GetPipes() const { return pipes_; }


private:
	/**
	 * @brief 파이프 컨트롤러의 상태입니다.
	 */
	EStatus status_ = EStatus::Wait;


	/**
	 * @brief 파이프 컨트롤러가 제어하는 파이프 목록입니다.
	 */
	std::vector<Pipe*> pipes_;


	/**
	 * @brief 파이프 간의 간격입니다.
	 */
	float gap_ = 0.0f;
};