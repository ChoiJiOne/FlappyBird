#include "Assertion.h"
#include "Bird.h"
#include "EntityManager.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "ScoreViewer.h"
#include "Texture2D.h"

ScoreViewer::ScoreViewer()
{
	static RUID number0 = ResourceManager::Get().CreateID<Texture2D>("Resource/Texture/0.png");
	static RUID number1 = ResourceManager::Get().CreateID<Texture2D>("Resource/Texture/1.png");
	static RUID number2 = ResourceManager::Get().CreateID<Texture2D>("Resource/Texture/2.png");
	static RUID number3 = ResourceManager::Get().CreateID<Texture2D>("Resource/Texture/3.png");
	static RUID number4 = ResourceManager::Get().CreateID<Texture2D>("Resource/Texture/4.png");
	static RUID number5 = ResourceManager::Get().CreateID<Texture2D>("Resource/Texture/5.png");
	static RUID number6 = ResourceManager::Get().CreateID<Texture2D>("Resource/Texture/6.png");
	static RUID number7 = ResourceManager::Get().CreateID<Texture2D>("Resource/Texture/7.png");
	static RUID number8 = ResourceManager::Get().CreateID<Texture2D>("Resource/Texture/8.png");
	static RUID number9 = ResourceManager::Get().CreateID<Texture2D>("Resource/Texture/9.png");

	numberIDs_ =
	{
		number0,
		number1,
		number2,
		number3,
		number4,
		number5,
		number6,
		number7,
		number8,
		number9,
	};

	center_ = Vec2f(300.0f, 100.0f);

	numberWidth_ = 30.0f;
	numberHeight_ = 50.0f;
	numberGap_ = 10.0f;

	scoreCache_ = -1;

	bIsInitialized_ = true;
}

ScoreViewer::~ScoreViewer()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void ScoreViewer::Tick(float deltaSeconds)
{
	int32_t score = EntityManager::Get().GetEntity<Bird>(birdID_)->GetScore();

	if (scoreCache_ != score)
	{
		scoreCache_ = score;
		number_ = std::vector<int32_t>();

		if (score == 0)
		{
			number_.push_back(0);
		}
		else
		{
			while (score > 0)
			{
				number_.push_back(score % 10);
				score /= 10;
			}
		}

		std::reverse(number_.begin(), number_.end());
	}
}

void ScoreViewer::Render()
{
	float totalWidth = (numberWidth_ + numberGap_) * static_cast<float>(number_.size() - 1);
	Vec2f center = center_ - Vec2f(totalWidth * 0.5f, 0.0f);

	for (const auto& n : number_)
	{
		RenderManager::Get().RenderSprite2D(numberIDs_[n], center, numberWidth_, numberHeight_, 0.0f);
		center.x += (numberWidth_ + numberGap_);
	}
}

void ScoreViewer::Release()
{
	if (bIsInitialized_)
	{
		bIsInitialized_ = false;
	}
}
