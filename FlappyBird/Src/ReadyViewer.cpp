#include "MathModule.h"

#include "Assertion.h"
#include "ReadyViewer.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "Texture2D.h"

ReadyViewer::ReadyViewer()
{
	static RUID infoID = ResourceManager::Get().CreateID<Texture2D>("Resource/Texture/GameInfo.png");
	infoID_ = infoID;
	infoLocation_ = Vec2f(300.0f, 400.0f);
	infoWidth_ = 150.0f;
	infoHeight_ = 140.0f;

	static RUID getReadyID = ResourceManager::Get().CreateID<Texture2D>("Resource/Texture/GetReady.png");
	getReadyID_ = getReadyID;
	getReadyLocation_ = Vec2f(300.0f, 200.0f);
	getReadyWidth_ = 350.0f;
	getReadyHeight_ = 100.0f;

	bIsInitialized_ = true;
}

ReadyViewer::~ReadyViewer()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void ReadyViewer::Tick(float deltaSeconds)
{
	accumulateTime_ += deltaSeconds;
}

void ReadyViewer::Render()
{
	RenderManager::Get().RenderSprite2D(getReadyID_, getReadyLocation_ + Vec2f(0.0f, 20.0f * MathModule::Sin(accumulateTime_ * 2.0f)), getReadyWidth_, getReadyHeight_, 0.0f);
	RenderManager::Get().RenderSprite2D(infoID_, infoLocation_, infoWidth_, infoHeight_, 0.0f);
}

void ReadyViewer::Release()
{
	if (bIsInitialized_)
	{
		bIsInitialized_ = false;
	}
}
