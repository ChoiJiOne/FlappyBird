#include "Assertion.h"
#include "Background.h"
#include "Button.h"
#include "ConfigManager.h"
#include "EntityManager.h"
#include "Panel.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "StatusViewer.h"
#include "SettingScene.h"
#include "TTFont.h"

void SettingScene::Tick(float deltaSeconds)
{
	EntityManager::Get().UpdateBatch(entities_, deltaSeconds);

	RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

	EntityManager::Get().RenderBatch(entities_);

	RenderManager::Get().EndFrame();
}

void SettingScene::Enter()
{
	CHECK(!bIsEnter_);

	RUID font32ID = ResourceManager::Get().GetGlobalResource("Font32");
	RUID font64ID = ResourceManager::Get().GetGlobalResource("Font64");

	static EUID background = EntityManager::Get().CreateID<Background>();

	static EUID settingPanel = EntityManager::Get().CreateID<Panel>("Resource/Panel/Setting.json", font64ID);
	static EUID backgroundPanel = EntityManager::Get().CreateID<Panel>("Resource/Panel/Background.json", font32ID);
	static EUID levelPanel = EntityManager::Get().CreateID<Panel>("Resource/Panel/Level.json", font32ID);
	static EUID birdPanel = EntityManager::Get().CreateID<Panel>("Resource/Panel/Bird.json", font32ID);

	static EUID dayButton = EntityManager::Get().CreateID<Button>("Resource/Button/Day.json", font32ID, EMouseButton::Left, 
		[&]() 
		{
			ConfigManager::Get().SetCurrentBackgroundID(ConfigManager::EBackground::Day);
		}
	);

	static EUID nightButton = EntityManager::Get().CreateID<Button>("Resource/Button/Night.json", font32ID, EMouseButton::Left,
		[&]()
		{
			ConfigManager::Get().SetCurrentBackgroundID(ConfigManager::EBackground::Night);
		}
	);

	static EUID easyButton = EntityManager::Get().CreateID<Button>("Resource/Button/Easy.json", font32ID, EMouseButton::Left,
		[&]()
		{
			ConfigManager::Get().SetCurrentLevel(ConfigManager::ELevel::Easy);
		}
	);

	static EUID normalButton = EntityManager::Get().CreateID<Button>("Resource/Button/Normal.json", font32ID, EMouseButton::Left,
		[&]()
		{
			ConfigManager::Get().SetCurrentLevel(ConfigManager::ELevel::Normal);
		}
	);

	static EUID hardButton = EntityManager::Get().CreateID<Button>("Resource/Button/Hard.json", font32ID, EMouseButton::Left,
		[&]()
		{
			ConfigManager::Get().SetCurrentLevel(ConfigManager::ELevel::Hard);
		}
	);

	static EUID blueButton = EntityManager::Get().CreateID<Button>("Resource/Button/Blue.json", font32ID, EMouseButton::Left, 
		[&]() 
		{
			ConfigManager::Get().SetCurrentBird(ConfigManager::EBird::Blue);
		}
	);

	static EUID redButton = EntityManager::Get().CreateID<Button>("Resource/Button/Red.json", font32ID, EMouseButton::Left, 
		[&]() 
		{
			ConfigManager::Get().SetCurrentBird(ConfigManager::EBird::Red);
		}
	);

	static EUID yellowButton = EntityManager::Get().CreateID<Button>("Resource/Button/Yellow.json", font32ID, EMouseButton::Left, 
		[&]() 
		{
			ConfigManager::Get().SetCurrentBird(ConfigManager::EBird::Yellow);
		}
	);

	static EUID backButton = EntityManager::Get().CreateID<Button>("Resource/Button/Back.json", font32ID, EMouseButton::Left, 
		[&]() 
		{
			link_ = startScene_;
			bDetectSwitch_ = true;
		}
	);

	static EUID statusViewer = EntityManager::Get().CreateID<StatusViewer>(font32ID);

	entities_ =
	{
		background,
		settingPanel,
		backgroundPanel,
		levelPanel,
		birdPanel,
		dayButton,
		nightButton,
		easyButton,
		normalButton,
		hardButton,
		blueButton,
		redButton,
		yellowButton,
		backButton,
		statusViewer,
	};

	bIsEnter_ = true;
}

void SettingScene::Exit()
{
	CHECK(bIsEnter_);

	bDetectSwitch_ = false;
	bIsEnter_ = false;
}