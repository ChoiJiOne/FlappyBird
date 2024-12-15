#include "MathModule.h"

#include "Assertion.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "PauseViewer.h"

PauseViewer::PauseViewer(const RUID& fontID)
	: fontID_(fontID)
{
	center_ = Vec2f(300.0f, 400.0f);
	text_ = L"PRESS MOUSE BUTTON";

	bIsInitialized_ = true;
}

PauseViewer::~PauseViewer()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void PauseViewer::Tick(float deltaSeconds)
{
	if (InputManager::Get().GetMousePressState(EMouseButton::Left) == EPressState::Released)
	{
		continueEvent_();
	}
}

void PauseViewer::Render()
{
	RenderManager::Get().RenderText2D(fontID_, text_, center_ + Vec2f(5.0f), Vec4f(0.3f, 0.3f, 0.3f, 1.0f));
	RenderManager::Get().RenderText2D(fontID_, text_, center_, Vec4f(1.0f, 0.0f, 0.0f, 1.0f));
}

void PauseViewer::Release()
{
	if (bIsInitialized_)
	{
		bIsInitialized_ = false;
	}
}