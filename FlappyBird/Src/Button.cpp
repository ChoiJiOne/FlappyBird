#include <json/json.h>

#include "FileModule.h"

#include "Assertion.h"
#include "Button.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "StringUtils.h"

Button::Button(const std::string& path, const RUID& fontID, const EMouseButton& mouseButton, const std::function<void()>& clickEvent)
	: fontID_(fontID)
	, mouseButton_(mouseButton)
	, clickEvent_(clickEvent)
{
	std::vector<uint8_t> jsonBuffer;
	ASSERT(FileModule::ReadBufferFromFile(path, jsonBuffer), "failed to read %s file", path.c_str());

	std::string jsonString(jsonBuffer.begin(), jsonBuffer.end());

	Json::Value root;
	Json::Reader reader;
	CHECK(reader.parse(jsonString, root));

	CHECK(root["width"].asFloat() && !root["width"].isNull());
	CHECK(root["height"].asFloat() && !root["height"].isNull());
	CHECK(root["side"].asFloat() && !root["side"].isNull());
	CHECK(root["x"].asFloat() && !root["x"].isNull());
	CHECK(root["y"].asFloat() && !root["y"].isNull());
	CHECK(root["text"].isString() && !root["text"].isNull());

	CHECK(root["outlineColor"].isArray() && !root["outlineColor"].isNull());
	CHECK(root["textColor"].isArray() && !root["textColor"].isNull());
	CHECK(root["disableColor"].isArray() && !root["disableColor"].isNull());
	CHECK(root["enableColor"].isArray() && !root["enableColor"].isNull());
	CHECK(root["pressColor"].isArray() && !root["pressColor"].isNull());
	CHECK(root["releaseColor"].isArray() && !root["releaseColor"].isNull());

	layout_.width = root["width"].asFloat();
	layout_.height = root["height"].asFloat();
	layout_.side = root["side"].asFloat();
	layout_.center.x = root["x"].asFloat();
	layout_.center.y = root["y"].asFloat();
	layout_.text = StringUtils::Convert(std::string(root["text"].asCString()));
	layout_.outlineColor = Vec4f(root["outlineColor"][0].asFloat(), root["outlineColor"][1].asFloat(), root["outlineColor"][2].asFloat(), root["outlineColor"][3].asFloat());
	layout_.textColor = Vec4f(root["textColor"][0].asFloat(), root["textColor"][1].asFloat(), root["textColor"][2].asFloat(), root["textColor"][3].asFloat());
	layout_.disableColor = Vec4f(root["disableColor"][0].asFloat(), root["disableColor"][1].asFloat(), root["disableColor"][2].asFloat(), root["disableColor"][3].asFloat());
	layout_.enableColor = Vec4f(root["enableColor"][0].asFloat(), root["enableColor"][1].asFloat(), root["enableColor"][2].asFloat(), root["enableColor"][3].asFloat());
	layout_.pressColor = Vec4f(root["pressColor"][0].asFloat(), root["pressColor"][1].asFloat(), root["pressColor"][2].asFloat(), root["pressColor"][3].asFloat());
	layout_.releaseColor = Vec4f(root["releaseColor"][0].asFloat(), root["releaseColor"][1].asFloat(), root["releaseColor"][2].asFloat(), root["releaseColor"][3].asFloat());
	
	bIsInitialized_ = true;
}

Button::Button(const Layout& layout, const RUID& fontID, const EMouseButton& mouseButton, const std::function<void()>& clickEvent)
	: layout_(layout)
	, fontID_(fontID)
	, mouseButton_(mouseButton)
	, clickEvent_(clickEvent)
{
	bIsInitialized_ = true;
}

Button::~Button()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Button::Tick(float deltaSeconds)
{
	EPressState pressState = InputManager::Get().GetMousePressState(mouseButton_);
	state_ = GetMouseButtonState(pressState, state_);
	if (state_ == EState::Released)
	{
		clickEvent_();
	}
}

void Button::Render()
{
	Vec4f backgroundColor;
	switch (state_)
	{
	case EState::Disabled:
		backgroundColor = layout_.disableColor;
		break;

	case EState::Enabled:
		backgroundColor = layout_.enableColor;
		break;

	case EState::Pressed:
		backgroundColor = layout_.pressColor;
		break;

	case EState::Released:
		backgroundColor = layout_.releaseColor;
		break;
	}
	
	RenderManager::Get().RenderRoundRectangle2D(layout_.center, layout_.width, layout_.height, layout_.side, 0.0f, backgroundColor);
	RenderManager::Get().RenderWireframeRoundRectangle2D(layout_.center, layout_.width, layout_.height, layout_.side, 0.0f, layout_.outlineColor);
	if (!layout_.text.empty())
	{
		RenderManager::Get().RenderText2D(fontID_, layout_.text, layout_.center, layout_.textColor);
	}
}

void Button::Release()
{
	if (bIsInitialized_)
	{
		bIsInitialized_ = false;
	}
}

Button::EState Button::GetMouseButtonState(const EPressState& pressState, const EState& state)
{
	if (DetectMouseCursorInButton())
	{
		if (state == EState::Disabled)
		{
			if (pressState == EPressState::Held || pressState == EPressState::Pressed)
			{
				return EState::Disabled;
			}
			else // pressState == EPressState::None || pressState == EPressState::Released
			{
				return EState::Enabled;
			}
		}
		else if (state == EState::Enabled)
		{
			if (pressState == EPressState::Held || pressState == EPressState::Pressed)
			{
				return EState::Pressed;
			}
			else
			{
				return EState::Enabled;
			}
		}
		else if (state == EState::Pressed)
		{
			if (pressState == EPressState::Released)
			{
				return EState::Released;
			}
			else if (pressState == EPressState::Held || pressState == EPressState::Pressed)
			{
				return EState::Pressed;
			}
			else // pressState == EPressState::None
			{
				return EState::Enabled;
			}
		}
		else // state == EState::Released
		{
			if (pressState == EPressState::None || pressState == EPressState::Released)
			{
				return EState::Enabled;
			}
			else // pressState == EPressState::Held || pressState == EPressState::Pressed
			{
				return EState::Pressed;
			}
		}
	}
	else
	{
		if (state == EState::Pressed && pressState == EPressState::Held)
		{
			return EState::Pressed;
		}
		else
		{
			return EState::Disabled;
		}
	}

	return EState::Disabled;
}

bool Button::DetectMouseCursorInButton()
{
	Vec2i cursorPos = InputManager::Get().GetCurrMousePosition();

	Vec2f minPosition = layout_.center - Vec2f(layout_.width, layout_.height) * 0.5f;
	Vec2f maxPosition = layout_.center + Vec2f(layout_.width, layout_.height) * 0.5f;
	Vec2f currentCursorPosition = Vec2f(static_cast<float>(cursorPos.x), static_cast<float>(cursorPos.y));

	return (minPosition.x <= currentCursorPosition.x && currentCursorPosition.x <= maxPosition.x)
		&& (minPosition.y <= currentCursorPosition.y && currentCursorPosition.y <= maxPosition.y);
}