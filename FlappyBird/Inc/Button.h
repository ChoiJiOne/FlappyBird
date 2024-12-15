#pragma once

#include <functional>
#include <string>

#include "Vec2.h"
#include "Vec4.h"

#include "IEntity.h"
#include "IResource.h"
#include "InputManager.h"


/**
 * @brief 마우스 버튼 엔티티입니다.
 */
class Button : public IEntity
{
public:
	/**
	 * @brief 마우스 버튼의 상태입니다.
	 */
	enum class EState : int32_t
	{
		Disabled = 0x00,
		Enabled = 0x01,
		Pressed = 0x02,
		Released = 0x03,
	};


	/**
	 * @brief 버튼의 레이아웃입니다.
	 */
	struct Layout
	{
		float width;
		float height;
		float side;
		Vec2f center;
		std::wstring text;
		Vec4f outlineColor;
		Vec4f textColor;
		Vec4f disableColor;
		Vec4f enableColor;
		Vec4f pressColor;
		Vec4f releaseColor;
	};


public:
	/**
	 * @brief 마우스 버튼의 생성자입니다.
	 *
	 * @param path 마우스 버튼의 레이아웃 리소스 경로입니다.
	 * @param fontID 마우스 버튼의 폰트 리소스 ID입니다.
	 * @param mouseButton 마우스 버튼의 종류입니다.
	 * @param clickEvent 마우스 버튼 클릭 시 실행할 이벤트입니다.
	 */
	explicit Button(const std::string& path, const RUID& fontID, const EMouseButton& mouseButton, const std::function<void()>& clickEvent);


	/**
	 * @brief 마우스 버튼의 생성자입니다.
	 * 
	 * @param layout 마우스 버튼의 레이아웃입니다.
	 * @param fontID 마우스 버튼의 폰트 리소스 ID입니다.
	 * @param mouseButton 마우스 버튼의 종류입니다.
	 * @param clickEvent 마우스 버튼 클릭 시 실행할 이벤트입니다.
	 */
	explicit Button(const Layout& layout, const RUID& fontID, const EMouseButton& mouseButton, const std::function<void()>& clickEvent);


	/**
	 * @brief 마우스 버튼의 가상 소멸자입니다.
	 */
	virtual ~Button();


	/**
	 * @brief 마우스 버튼의 복사 생성자 및 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Button);


	/**
	 * @brief 마우스 버튼을 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief 마우스 버튼을 화면에 그립니다.
	 */
	virtual void Render() override;


	/**
	 * @brief 마우스 버튼 내의 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


private:
	/**
	 * @brief 마우스 버튼의 상태를 얻습니다.
	 *
	 * @param pressState 키 입력 상태입니다.
	 * @param state 이전 버튼의 상태입니다.
	 *
	 * @return 새롭게 업데이트된 버튼의 상태를 얻습니다.
	 */
	EState GetMouseButtonState(const EPressState& pressState, const EState& state);


	/**
	 * @brief 마우스가 버튼 내에 있는지 확인합니다.
	 *
	 * @return 마우스가 버튼 내에 있다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool DetectMouseCursorInButton();

	
protected:
	/**
	 * @brief 마우스 버튼의 레이아웃입니다.
	 */
	Layout layout_;


	/**
	 * @brief 마우스 버튼에 표시할 텍스트의 폰트 리소스 ID입니다.
	 */
	RUID fontID_ = -1;


	/**
	 * @brief UI 버튼의 가상 키 값입니다.
	 */
	EMouseButton mouseButton_ = EMouseButton::Left;


	/**
	 * @brief UI 버튼을 클릭했을 때 실행할 이벤트입니다.
	 */
	std::function<void()> clickEvent_;


	/**
	 * @brief 현재 마우스 버튼의 상태입니다.
	 */
	EState state_ = EState::Disabled;
};