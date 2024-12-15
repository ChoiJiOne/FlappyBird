#include "Assertion.h"
#include "Background.h"
#include "Bird.h"
#include "ConfigManager.h"
#include "EntityManager.h"
#include "PlayScene.h"
#include "Land.h"
#include "ReadyViewer.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "ReadyScene.h"
#include "TTFont.h"

void ReadyScene::Tick(float deltaSeconds)
{
	EntityManager::Get().UpdateBatch(entityIDs_, deltaSeconds);

	RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
	EntityManager::Get().RenderBatch(entityIDs_);
	RenderManager::Get().EndFrame();

	Bird* bird = EntityManager::Get().GetEntity<Bird>(birdID_);
	if (bird->GetStatus() == Bird::EStatus::Fly)
	{
		bDetectSwitch_ = true;
		link_ = playScene_;
	}
}

void ReadyScene::Enter()
{
	CHECK(!bIsEnter_);
	
	ConfigManager::ELevel level = ConfigManager::Get().GetCurrentLevel();
	switch (level)
	{
	case ConfigManager::ELevel::Easy:
		gameSpeed_ = 150.0f;
		break;

	case ConfigManager::ELevel::Normal:
		gameSpeed_ = 200.0f;
		break;

	case ConfigManager::ELevel::Hard:
		gameSpeed_ = 300.0f;
		break;

	default:
		ASSERT(false, "undefined config level type");
		break;
	}

	int32_t w = 0;
	int32_t h = 0;

	RenderManager::Get().GetRenderTargetWindowSize(w, h);
	Bird::SetStartLocation(Vec2f(static_cast<float>(w) * 0.3f, static_cast<float>(h) * 0.4f));

	backgroundID_ = EntityManager::Get().CreateID<Background>(backgroundScrollSpeed_);
	landID_ = EntityManager::Get().CreateID<Land>(gameSpeed_);
	birdID_ = EntityManager::Get().CreateID<Bird>();
	readyViewer_ = EntityManager::Get().CreateID<ReadyViewer>();

	entityIDs_ =
	{
		backgroundID_,
		landID_,
		birdID_,
		readyViewer_,
	};

	bIsEnter_ = true;
}

void ReadyScene::Exit()
{
	CHECK(bIsEnter_);

	PlayScene* playScene = reinterpret_cast<PlayScene*>(playScene_);
	playScene->SetGameSpeed(gameSpeed_);
	playScene->SetBackgroundID(backgroundID_);
	playScene->SetLandID(landID_);
	playScene->SetBirdID(birdID_);

	bDetectSwitch_ = false;
	bIsEnter_ = false;
}