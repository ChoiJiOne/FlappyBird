#pragma once

#include "Macro.h"


/**
 * @brief 리소스의 고유 아이디(Resource Unique Identity)입니다.
 */
using RUID = int32_t;


/**
 * @brief 리소스 매니저 클래스의 전방 선언입니다.
 */
class ResourceManager;


/**
 * @brief 게임 내의 리소스 인터페이스입니다.
 *
 * @note
 * - 게임 내의 리소스(셰이더, 텍스처, 폰트, 사운드 등)는 이 클래스를 상속받아야 합니다.
 * - 이 인터페이스에는 해제는 있지만, 초기화는 없습니다.
 * - 이 인터페이스를 상속받는 클래스는 생성자 혹은 그 외의 메서드에서 적절한 초기화를 수행해야 합니다.
 */
class IResource
{
public:
	/**
	 * @brief 리소스 인터페이스의 디폴트 생성자입니다.
	 */
	IResource() = default;


	/**
	 * @brief 리소스 인터페이스의 가상 소멸자입니다.
	 *
	 * @note 리소스 인터페이스의 내부에서 할당된 요소를 해제하기 위해서는 반드시 Release를 호출해야 합니다.
	 */
	virtual ~IResource() {}


	/**
	 * @brief 리소스 인터페이스의 복사 생성자외 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(IResource);


	/**
	 * @brief 리소스 인터페이스 내부 리소스를 할당 해제합니다.
	 *
	 * @note 리소스 인터페이스를 상속받는 하위 클래스에서 반드시 구현해야 합니다.
	 */
	virtual void Release() = 0;


	/**
	 * @brief 리소스가 초기화된 적이 있는지 확인합니다.
	 *
	 * @return 리소스가 초기화된 적이 있다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsInitialized() const { return bIsInitialized_; }


	/**
	 * @brief 리소스의 ID 값을 얻습니다.
	 * 
	 * @return 리소스의 ID 값을 반환합니다.
	 */
	const RUID& GetID() const { return id_; }


private:
	/**
	 * @brief 리소스 매니저에서 리소스 인터페이스에 접근할 수 있도록 선언합니다.
	 */
	friend ResourceManager;


	/**
	 * @brief 리소스의 ID 값을 설정합니다.
	 * 
	 * @param id 설정할 리소스의 ID 값입니다.
	 * 
	 * @note 이 기능은 ResourceManager에서만 사용하는 기능입니다.
	 */
	void SetID(const RUID& id) { id_ = id; }

	
	/**
	 * @brief 리소스의 ID 값입니다.
	 */
	RUID id_ = -1;


protected:
	/**
	 * @brief 리소스가 초기화되었는지 확인합니다.
	 */
	bool bIsInitialized_ = false;
};