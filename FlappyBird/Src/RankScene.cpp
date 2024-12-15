#include "Assertion.h"
#include "AudioManager.h"
#include "Background.h"
#include "Button.h"
#include "ConfigManager.h"
#include "EntityManager.h"
#include "Land.h"
#include "Panel.h"
#include "Pipe.h"
#include "PipeController.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "RankViewer.h"
#include "RankScene.h"
#include "Sound.h"
#include "TTFont.h"

void RankScene::Tick(float deltaSeconds)
{
	EntityManager::Get().UpdateBatch(entityIDs_, deltaSeconds);

	RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
	EntityManager::Get().RenderBatch(entityIDs_);
	RenderManager::Get().EndFrame();
}

void RankScene::Enter()
{
	CHECK(!bIsEnter_);

	static Sound* clickSound = ResourceManager::Get().GetResource<Sound>(ResourceManager::Get().GetGlobalResource("ClickSound"));

	static auto resetEvent = [&]()
	{
		clickSound->Reset();
		clickSound->SetLooping(false);
		clickSound->Play();

		link_ = startScene_;
		bDetectSwitch_ = true;
	};

	RUID fontID = ResourceManager::Get().GetGlobalResource("Font32");
	
	static EUID resetButton = EntityManager::Get().CreateID<Button>("Resource/Button/Reset.json", fontID, EMouseButton::Left, resetEvent);
	static EUID quitButton = EntityManager::Get().CreateID<Button>("Resource/Button/Quit.json", fontID, EMouseButton::Left, quitLoopEvent_);
	static EUID rankViewer = EntityManager::Get().CreateID<RankViewer>(fontID);

	std::vector<Pipe*> pipes = EntityManager::Get().GetEntity<PipeController>(pipeController_)->GetPipes();

	entityIDs_ = 
	{
		backgroundID_,
		pipes[0]->GetID(),
		pipes[1]->GetID(),
		pipes[2]->GetID(),
		pipes[3]->GetID(),
		pipeController_,
		landID_,
		rankViewer,
		resetButton,
		quitButton,
	};

	bIsEnter_ = true;
}

void RankScene::Exit()
{
	CHECK(bIsEnter_);

	std::vector<Pipe*> pipes = EntityManager::Get().GetEntity<PipeController>(pipeController_)->GetPipes();
	for (Pipe* pipe : pipes)
	{
		EntityManager::Get().Destroy(pipe->GetID());
	}

	EntityManager::Get().Destroy(backgroundID_);
	EntityManager::Get().Destroy(pipeController_);
	EntityManager::Get().Destroy(landID_);
	EntityManager::Get().Destroy(backgroundID_);

	bDetectSwitch_ = false;
	bIsEnter_ = false;
}