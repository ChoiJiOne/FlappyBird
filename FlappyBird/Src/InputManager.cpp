#include <SDL.h>

#include "Assertion.h"
#include "InputManager.h"

InputManager& InputManager::Get()
{
	static InputManager instance;
	return instance;
}

void InputManager::Startup()
{
	CHECK(!bIsStartup_);

	bIsStartup_ = true;
}

void InputManager::Shutdown()
{
	CHECK(bIsStartup_);

	bIsStartup_ = false;
}

void InputManager::Tick()
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		EWindowEvent windowEvent = static_cast<EWindowEvent>(e.window.event);

		for (std::size_t index = 0; index < windowEventActionSize_; ++index)
		{
			if (windowEvent == windowEventActions_[index].windowEvent && windowEventActions_[index].bIsActive)
			{
				windowEventActions_[index].windowEventAction();
			}
		}
	}

	const void* currKeyboardState = reinterpret_cast<const void*>(SDL_GetKeyboardState(nullptr));

	std::memcpy(prevKeyboardState_.keybordState.data(), currKeyboardState_.keybordState.data(), KeyboardState::BUFFER_SIZE);
	std::memcpy(currKeyboardState_.keybordState.data(), currKeyboardState, KeyboardState::BUFFER_SIZE);

	prevMouseState_ = currMouseState_;
	currMouseState_.state = SDL_GetMouseState(&currMouseState_.position.x, &currMouseState_.position.y);
}

EPressState InputManager::GetVKeyPressState(const EVirtualKey& keyCode) const
{
	EPressState pressState = EPressState::None;

	if (IsPressKey(prevKeyboardState_, keyCode))
	{
		if (IsPressKey(currKeyboardState_, keyCode))
		{
			pressState = EPressState::Held;
		}
		else
		{
			pressState = EPressState::Released;
		}
	}
	else
	{
		if (IsPressKey(currKeyboardState_, keyCode))
		{
			pressState = EPressState::Pressed;
		}
		else
		{
			pressState = EPressState::None;
		}
	}

	return pressState;
}

EPressState InputManager::GetMousePressState(const EMouseButton& mouseButton) const
{
	EPressState pressState = EPressState::None;

	if (IsPressMouse(prevMouseState_, mouseButton))
	{
		if (IsPressMouse(currMouseState_, mouseButton))
		{
			pressState = EPressState::Held;
		}
		else
		{
			pressState = EPressState::Released;
		}
	}
	else
	{
		if (IsPressMouse(currMouseState_, mouseButton))
		{
			pressState = EPressState::Pressed;
		}
		else
		{
			pressState = EPressState::None;
		}
	}

	return pressState;
}

WINDOW_EVENT_UID InputManager::AddWindowEventAction(const EWindowEvent& windowEvent, const std::function<void()>& eventAction, bool bIsActive)
{
	CHECK(0 <= windowEventActionSize_ && windowEventActionSize_ < MAX_EVENT_ACTION_SIZE);

	WINDOW_EVENT_UID windowEventID = windowEventActionSize_++;

	windowEventActions_[windowEventID].windowEvent = windowEvent;
	windowEventActions_[windowEventID].windowEventAction = eventAction;
	windowEventActions_[windowEventID].bIsActive = bIsActive;

	return windowEventID;
}

void InputManager::DeleteWindowEventAction(const WINDOW_EVENT_UID& windowEventID)
{
	CHECK(0 <= windowEventID && windowEventID < MAX_EVENT_ACTION_SIZE);

	windowEventActions_[windowEventID].windowEvent = EWindowEvent::NONE;
	windowEventActions_[windowEventID].windowEventAction = nullptr;
	windowEventActions_[windowEventID].bIsActive = false;
}

void InputManager::SetActiveWindowEventAction(const WINDOW_EVENT_UID& windowEventID, bool bIsActive)
{
	CHECK(0 <= windowEventID && windowEventID < MAX_EVENT_ACTION_SIZE);

	windowEventActions_[windowEventID].bIsActive = bIsActive;
}

bool InputManager::IsPressKey(const KeyboardState& keyboardState, const EVirtualKey& keyCode) const
{
	return keyboardState.keybordState.at(static_cast<int32_t>(keyCode)) == 0 ? false : true;
}

bool InputManager::IsPressMouse(const MouseState& mouseState, const EMouseButton& mouseButton) const
{
	return (mouseState.state & static_cast<uint32_t>(mouseButton)) == 0 ? false : true;
}