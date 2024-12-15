#include "Assertion.h"
#include "Background.h"
#include "Bird.h"
#include "ConfigManager.h"
#include "EntityManager.h"
#include "InputManager.h"
#include "Land.h"
#include "PauseViewer.h"
#include "Pipe.h"
#include "PipeController.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "RankScene.h"
#include "PlayScene.h"
#include "ScoreViewer.h"
#include "TTFont.h"

void PlayScene::Tick(float deltaSeconds)
{
	if (bIsPause_)
	{
		EntityManager::Get().UpdateBatch(pauseViewerID_, deltaSeconds);
	}
	else
	{
		EntityManager::Get().UpdateBatch(entityIDs_, deltaSeconds);
	}

	RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
	EntityManager::Get().RenderBatch(entityIDs_);
	if (bIsPause_)
	{
		EntityManager::Get().RenderBatch(pauseViewerID_);
	}
	RenderManager::Get().EndFrame();

	Bird* bird = EntityManager::Get().GetEntity<Bird>(birdID_);
	Bird::EStatus status = bird->GetStatus();
	if (countDown_ >= 0.0f && status == Bird::EStatus::Fly)
	{
		countDown_ -= deltaSeconds;
		
		if (countDown_ <= 0.0f)
		{
			PipeController* pipeController = EntityManager::Get().GetEntity<PipeController>(pipeController_);
			pipeController->SetStatus(PipeController::EStatus::Active);
		}
	}

	if (bird->GetStatus() == Bird::EStatus::Done)
	{
		bDetectSwitch_ = true;
		link_ = rankScene_;
	}
}

void PlayScene::Enter()
{
	CHECK(!bIsEnter_);

	countDown_ = 3.0f;
	bIsPause_ = false;

	if (sceneEvents_.empty())
	{
		auto pauseEvent = [&]()
		{
			bIsPause_ = true;
		};

		sceneEvents_ =
		{
			{ EWindowEvent::HIDDEN,     InputManager::Get().AddWindowEventAction(EWindowEvent::HIDDEN,     pauseEvent, true) },
			{ EWindowEvent::MOVED,      InputManager::Get().AddWindowEventAction(EWindowEvent::MOVED,      pauseEvent, true) },
			{ EWindowEvent::MINIMIZED,  InputManager::Get().AddWindowEventAction(EWindowEvent::MINIMIZED,  pauseEvent, true) },
			{ EWindowEvent::FOCUS_LOST, InputManager::Get().AddWindowEventAction(EWindowEvent::FOCUS_LOST, pauseEvent, true) },
		};
	}
	else
	{
		for (const auto& sceneEvent : sceneEvents_)
		{
			InputManager::Get().SetActiveWindowEventAction(sceneEvent.second, true);
		}
	}

	int32_t w = 0;
	int32_t h = 0;
	float gap = 50.0f;
	RenderManager::Get().GetRenderTargetWindowSize(w, h);

	Pipe::SetStartLocation(Vec2f(static_cast<float>(w) + gap, static_cast<float>(h) * 0.4f));
	Pipe::SetEndLocation(Vec2f(-gap, static_cast<float>(h) * 0.4f));

	std::vector<Pipe*> pipes =
	{
		EntityManager::Get().CreateEntity<Pipe>(gameSpeed_),
		EntityManager::Get().CreateEntity<Pipe>(gameSpeed_),
		EntityManager::Get().CreateEntity<Pipe>(gameSpeed_),
		EntityManager::Get().CreateEntity<Pipe>(gameSpeed_),
	};

	static RUID fontID = ResourceManager::Get().GetGlobalResource("Font32");

	pipeController_ = EntityManager::Get().CreateID<PipeController>(pipes, 300.0f);
	ScoreViewer* scoreViewer = EntityManager::Get().CreateEntity<ScoreViewer>();
	PauseViewer* pasueViewer = EntityManager::Get().CreateEntity<PauseViewer>(fontID);

	scoreViewerID_ = scoreViewer->GetID();
	pauseViewerID_ = pasueViewer->GetID();

	entityIDs_ =
	{
		backgroundID_,
		pipes[0]->GetID(),
		pipes[1]->GetID(),
		pipes[2]->GetID(),
		pipes[3]->GetID(),
		pipeController_,
		landID_,
		birdID_,
		scoreViewerID_,
	};

	Bird* bird = EntityManager::Get().GetEntity<Bird>(birdID_);
	bird->SetPipeControllerID(pipeController_);
	bird->SetLandID(landID_);
	bird->SetBackgroundID(backgroundID_);

	scoreViewer->SetBirdID(birdID_);
	pasueViewer->SetContinueEvent([&]() { bIsPause_ = false; });

	bIsEnter_ = true;
}

void PlayScene::Exit()
{
	CHECK(bIsEnter_);

	EntityManager::Get().Destroy(birdID_);
	EntityManager::Get().Destroy(scoreViewerID_);

	RankScene* rankScene = reinterpret_cast<RankScene*>(rankScene_);
	rankScene->SetBackgroundID(backgroundID_);
	rankScene->SetLandID(landID_);
	rankScene->SetPipeController(pipeController_);

	for (const auto& sceneEvent : sceneEvents_)
	{
		InputManager::Get().SetActiveWindowEventAction(sceneEvent.second, false);
	}

	bDetectSwitch_ = false;
	bIsEnter_ = false;
}