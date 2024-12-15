#include <json/json.h>

#include "FileModule.h"

#include "Assertion.h"
#include "Panel.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "StringUtils.h"

Panel::Panel(const std::string& path, const RUID& fontID)
	: fontID_(fontID)
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
	CHECK(root["backgroundColor"].isArray() && !root["backgroundColor"].isNull());
	CHECK(root["textColor"].isArray() && !root["textColor"].isNull());

	layout_.width = root["width"].asFloat();
	layout_.height = root["height"].asFloat();
	layout_.side = root["side"].asFloat();
	layout_.center.x = root["x"].asFloat();
	layout_.center.y = root["y"].asFloat();
	layout_.text = StringUtils::Convert(std::string(root["text"].asCString()));
	layout_.outlineColor = Vec4f(root["outlineColor"][0].asFloat(), root["outlineColor"][1].asFloat(), root["outlineColor"][2].asFloat(), root["outlineColor"][3].asFloat());
	layout_.backgroundColor = Vec4f(root["backgroundColor"][0].asFloat(), root["backgroundColor"][1].asFloat(), root["backgroundColor"][2].asFloat(), root["backgroundColor"][3].asFloat());
	layout_.textColor = Vec4f(root["textColor"][0].asFloat(), root["textColor"][1].asFloat(), root["textColor"][2].asFloat(), root["textColor"][3].asFloat());
	
	bIsInitialized_ = true;
}

Panel::Panel(const Layout& layout, const RUID& fontID)
	: layout_(layout)
	, fontID_(fontID)
{
	bIsInitialized_ = true;
}

Panel::~Panel()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Panel::Tick(float deltaSeconds)
{
}

void Panel::Render()
{
	RenderManager::Get().RenderRoundRectangle2D(layout_.center, layout_.width, layout_.height, layout_.side, 0.0f, layout_.backgroundColor);
	RenderManager::Get().RenderWireframeRoundRectangle2D(layout_.center, layout_.width, layout_.height, layout_.side, 0.0f, layout_.outlineColor);
	if (!layout_.text.empty())
	{
		RenderManager::Get().RenderText2D(fontID_, layout_.text, layout_.center, layout_.textColor);
	}
}

void Panel::Release()
{
	if (bIsInitialized_)
	{
		bIsInitialized_ = false;
	}
}