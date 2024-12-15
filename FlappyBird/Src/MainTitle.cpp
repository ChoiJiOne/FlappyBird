#include "MathModule.h"

#include "Assertion.h"
#include "MainTitle.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "Texture2D.h"

MainTitle::MainTitle(const RUID& fontID) : Panel("Resource/Panel/MainTitle.json", fontID)
{
	colors_ = 
	{
		Vec4f(0.5f, 0.5f, 0.5f, 1.0f),
		Vec4f(1.0f, 0.5f, 0.5f, 1.0f),
		Vec4f(0.5f, 1.0f, 0.5f, 1.0f),
		Vec4f(0.5f, 0.5f, 1.0f, 1.0f),
		Vec4f(0.5f, 1.0f, 1.0f, 1.0f),
		Vec4f(1.0f, 0.5f, 1.0f, 1.0f),
		Vec4f(1.0f, 1.0f, 0.5f, 1.0f),
		Vec4f(1.0f, 1.0f, 1.0f, 1.0f),
	};

	birdPosition_ = layout_.center;
	birdPosition_.y += 100.0f;

	birdWidth_ = 60.0f;
	birdHeight_ = 40.0f;

	RUID birdDown = ResourceManager::Get().CreateID<Texture2D>("Resource/Texture/YellowBird_Down.png");
	RUID birdMid = ResourceManager::Get().CreateID<Texture2D>("Resource/Texture/YellowBird_Mid.png");
	RUID birdUp = ResourceManager::Get().CreateID<Texture2D>("Resource/Texture/YellowBird_Up.png");

	birds_ = 
	{
		birdDown,
		birdMid,
		birdUp,
		birdMid,
		birdDown
	};
}

MainTitle::~MainTitle()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void MainTitle::Tick(float deltaSeconds)
{
	accumulateFlyTime_ += deltaSeconds;
	accumulateTime_ += deltaSeconds;
	updateAccumulateTime_ += deltaSeconds;

	if (updateAccumulateTime_ >= maxAccumulateTime_)
	{
		updateAccumulateTime_ = 0.0f;

		Vec4f color = colors_[0];
		for (std::size_t index = 1; index < colors_.size(); ++index)
		{
			colors_[index - 1] = colors_[index];
		}
		colors_.back() = color;
	}

	if (accumulateFlyTime_ >= flyTime_)
	{
		accumulateFlyTime_ -= flyTime_;
		birdIndex_ = (birdIndex_ + 1) % birds_.size();
	}
}

void MainTitle::Render()
{
	RenderManager::Get().RenderRoundRectangle2D(layout_.center, layout_.width, layout_.height, layout_.side, 0.0f, layout_.backgroundColor);
	RenderManager::Get().RenderWireframeRoundRectangle2D(layout_.center, layout_.width, layout_.height, layout_.side, 0.0f, layout_.outlineColor);

	if (!layout_.text.empty())
	{
		RenderManager::Get().RenderText2D(fontID_, layout_.text, layout_.center + Vec2f(bias_), Vec4f(0.3f, 0.3f, 0.3f, 1.0f));
		RenderManager::Get().RenderText2D(fontID_, layout_.text, layout_.center, colors_);
	}

	RenderManager::Get().RenderSprite2D(birds_[birdIndex_], birdPosition_, birdWidth_, birdHeight_, 0.0f);
}

void MainTitle::Release()
{
	if (bIsInitialized_)
	{
		bIsInitialized_ = false;
	}
}