#include "Assertion.h"
#include "Background.h"
#include "ConfigManager.h"
#include "RenderManager.h"

Background::Background()
	: bCanMove_(false)
	, scrollSpeed_(0.0f)
{
	int32_t w = 0;
	int32_t h = 0;
	RenderManager::Get().GetRenderTargetWindowSize(w, h);
	
	maxScrollX_ = static_cast<float>(w);

	bound_ = BoundBox2D(Vec2f(static_cast<float>(w) * 0.5f, static_cast<float>(h) * 0.5f), static_cast<float>(w), static_cast<float>(h));

	bIsInitialized_ = true;
}

Background::Background(float scrollSpeed)
	: bCanMove_(true)
	, scrollSpeed_(scrollSpeed)
{
	int32_t w = 0;
	int32_t h = 0;
	RenderManager::Get().GetRenderTargetWindowSize(w, h);

	maxScrollX_ = static_cast<float>(w);

	bound_ = BoundBox2D(Vec2f(static_cast<float>(w) * 0.5f, static_cast<float>(h) * 0.5f), static_cast<float>(w), static_cast<float>(h));

	bIsInitialized_ = true;
}

Background::~Background()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Background::Tick(float deltaSeconds)
{
	textureID_ = ConfigManager::Get().GetCurrentBackgroundID();

	if (bCanMove_)
	{
		scrollX_ += scrollSpeed_ * deltaSeconds;

		if (scrollX_ >= maxScrollX_)
		{
			scrollX_ -= maxScrollX_;
		}
	}
}

void Background::Render()
{
	float rate = scrollX_ / maxScrollX_;
	RenderManager::Get().RenderHorizonScrollSprite2D(textureID_, rate);
}

void Background::Release()
{
	if (bIsInitialized_)
	{
		bIsInitialized_ = false;
	}
}