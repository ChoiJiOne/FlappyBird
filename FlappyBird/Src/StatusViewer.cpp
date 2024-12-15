#include "Assertion.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "StatusViewer.h"
#include "StringUtils.h"
#include "Texture2D.h"

StatusViewer::StatusViewer(const RUID& fontID)
	: fontID_(fontID)
{
	levels_ =
	{
		{ ConfigManager::ELevel::Easy,   L"Easy"   },
		{ ConfigManager::ELevel::Normal, L"Normal" },
		{ ConfigManager::ELevel::Hard,   L"Hard"   },
	};

	birdIDs_ =
	{
		{ ConfigManager::EBird::Blue,   ResourceManager::Get().CreateID<Texture2D>("Resource/Texture/BlueBird_Mid.png")   },
		{ ConfigManager::EBird::Red,    ResourceManager::Get().CreateID<Texture2D>("Resource/Texture/RedBird_Mid.png")    },
		{ ConfigManager::EBird::Yellow, ResourceManager::Get().CreateID<Texture2D>("Resource/Texture/YellowBird_Mid.png") },
	};
	
	bIsInitialized_ = true;
}

StatusViewer::~StatusViewer()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void StatusViewer::Tick(float deltaSeconds)
{
}

void StatusViewer::Render()
{
	const std::wstring& level = levels_.at(ConfigManager::Get().GetCurrentLevel());
	const RUID& textureID = birdIDs_.at(ConfigManager::Get().GetCurrentBird());

	RenderManager::Get().RenderText2D(fontID_, StringUtils::PrintF(L"LEVEL : %s", level.c_str()), Vec2f(50.0f, 650.0f), Vec4f(0.0f, 0.0f, 0.0f, 1.0f), false);
	RenderManager::Get().RenderText2D(fontID_, L"BIRD :", Vec2f(50.0f, 700.0f), Vec4f(0.0f, 0.0f, 0.0f, 1.0f), false);
	RenderManager::Get().RenderSprite2D(textureID, Vec2f(170.0f, 710.0f), 40.0f, 30.0f, 0.0f);
}

void StatusViewer::Release()
{
	if (bIsInitialized_)
	{
		bIsInitialized_ = false;
	}
}