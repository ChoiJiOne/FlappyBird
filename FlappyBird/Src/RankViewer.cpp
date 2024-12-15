#include "MathModule.h"

#include "Assertion.h"
#include "ConfigManager.h"
#include "RankViewer.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "StringUtils.h"
#include "Texture2D.h"

RankViewer::RankViewer(const RUID& fontID)
	: fontID_(fontID)
{
	static RUID gameOverID = ResourceManager::Get().CreateID<Texture2D>("Resource/Texture/GameOver.png");
	gameOverID_ = gameOverID;

	gameOverLocation_ = Vec2f(300.0f, 150.0f);
	gameOverWidth_ = 350.0f;
	gameOverHeight_ = 100.0f;

	currentLevelLocation_ = Vec2f(200.0f, 250.0f);
	currentScoreLocation_ = Vec2f(200.0f, 300.0f);
	bestScoreLocation_ = Vec2f(200.0f, 350.0f);

	bIsInitialized_ = true;
}

RankViewer::~RankViewer()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void RankViewer::Tick(float deltaSeconds)
{
	accumulateTime_ += deltaSeconds;

	switch (ConfigManager::Get().GetCurrentLevel())
	{
	case ConfigManager::ELevel::Easy:
		currentLevel_ = L"LEVEL : EASY";
		break;

	case ConfigManager::ELevel::Normal:
		currentLevel_ = L"LEVEL : NORMAL";
		break;

	case ConfigManager::ELevel::Hard:
		currentLevel_ = L"LEVEL : HARD";
		break;

	default:
		ASSERT(false, "undefined level type");
	}

	currentScore_ = StringUtils::PrintF(L"SCORE : %d", ConfigManager::Get().GetRecentScore());
	bestScore_ = StringUtils::PrintF(L"BEST : %d", ConfigManager::Get().GetBestScore());
	bIsUpdateBest_ = ConfigManager::Get().IsUpdateBestScore();
}

void RankViewer::Render()
{
	RenderManager::Get().RenderSprite2D(gameOverID_, gameOverLocation_ + Vec2f(0.0f, 20.0f * MathModule::Sin(accumulateTime_ * 2.0f)), gameOverWidth_, gameOverHeight_, 0.0f);

	RenderManager::Get().RenderText2D(fontID_, currentLevel_, currentLevelLocation_ + Vec2f(4.0f), Vec4f(0.3f, 0.3f, 0.3f, 1.0f), false);
	RenderManager::Get().RenderText2D(fontID_, currentLevel_, currentLevelLocation_, Vec4f(1.0f, 1.0f, 1.0f, 1.0f), false);

	RenderManager::Get().RenderText2D(fontID_, currentScore_, currentScoreLocation_ + Vec2f(4.0f), Vec4f(0.3f, 0.3f, 0.3f, 1.0f), false);
	RenderManager::Get().RenderText2D(fontID_, currentScore_, currentScoreLocation_, Vec4f(1.0f, 1.0f, 1.0f, 1.0f), false);

	RenderManager::Get().RenderText2D(fontID_, bestScore_, bestScoreLocation_ + Vec2f(4.0f), Vec4f(0.3f, 0.3f, 0.3f, 1.0f), false);
	RenderManager::Get().RenderText2D(fontID_, bestScore_, bestScoreLocation_, bIsUpdateBest_ ? Vec4f(1.0f, 0.0f, 0.0f, 1.0f) : Vec4f(1.0f, 1.0f, 1.0f, 1.0f), false);
}

void RankViewer::Release()
{
	if (bIsInitialized_)
	{
		bIsInitialized_ = false;
	}
}
