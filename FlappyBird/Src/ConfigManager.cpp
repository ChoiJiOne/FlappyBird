#include "FileModule.h"

#include "Assertion.h"
#include "ConfigManager.h"
#include "ResourceManager.h"
#include "Texture2D.h"

/**
 * @brief 레벨에 따른 최고 스코어를 기록하는 파일의 포멧입니다.
 */
struct BestScoreFileFormat
{
	ConfigManager::ELevel easy;
	int32_t easyScore;
	ConfigManager::ELevel normal;
	int32_t normalScore;
	ConfigManager::ELevel hard;
	int32_t hardScore;
};

ConfigManager& ConfigManager::Get()
{
	static ConfigManager instance;
	return instance;
}

void ConfigManager::Startup()
{
	CHECK(!bIsStartup_);

	dayBackgroundID_ = ResourceManager::Get().CreateID<Texture2D>("Resource/Texture/Background_Day.png");
	nightBackgroundID_ = ResourceManager::Get().CreateID<Texture2D>("Resource/Texture/Background_Night.png");

	currentBackgroundID_ = dayBackgroundID_;

	bIsUpdateBestScore_ = false;

	recentScore_ = 
	{
		{ ELevel::Easy,   -1 },
		{ ELevel::Normal, -1 },
		{ ELevel::Hard,   -1 },
	};

	if (FileModule::IsValidPath("Resource/Cache"))
	{
		if (FileModule::IsValidPath("Resource/Cache/Best.bin"))
		{
			std::vector<uint8_t> buffer;
			CHECK(FileModule::ReadBufferFromFile("Resource/Cache/Best.bin", buffer));

			BestScoreFileFormat* bestScoreFilePtr = reinterpret_cast<BestScoreFileFormat*>(buffer.data());

			bestScore_ =
			{
				{ bestScoreFilePtr->easy,   bestScoreFilePtr->easyScore   },
				{ bestScoreFilePtr->normal, bestScoreFilePtr->normalScore },
				{ bestScoreFilePtr->hard,   bestScoreFilePtr->hardScore   },
			};
		}
		else
		{
			bestScore_ =
			{
				{ ELevel::Easy,   -1 },
				{ ELevel::Normal, -1 },
				{ ELevel::Hard,   -1 },
			};
		}
	}
	else
	{
		CHECK(FileModule::MakeDirectory("Resource/Cache"));

		bestScore_ =
		{
			{ ELevel::Easy,   -1 },
			{ ELevel::Normal, -1 },
			{ ELevel::Hard,   -1 },
		};
	}

	bIsStartup_ = true;
}

void ConfigManager::Shutdown()
{
	CHECK(bIsStartup_);

	if (!FileModule::IsValidPath("Resource/Cache"))
	{
		CHECK(FileModule::MakeDirectory("Resource/Cache"));
	}

	BestScoreFileFormat bestScoreFile;
	bestScoreFile.easy = ELevel::Easy;
	bestScoreFile.easyScore = bestScore_[ELevel::Easy];
	bestScoreFile.normal = ELevel::Normal;
	bestScoreFile.normalScore = bestScore_[ELevel::Normal];
	bestScoreFile.hard = ELevel::Hard;
	bestScoreFile.hardScore = bestScore_[ELevel::Hard];

	BestScoreFileFormat* bestScoreFilePtr = &bestScoreFile;
	std::size_t bufferSize = sizeof(bestScoreFile);

	std::vector<uint8_t> buffer(bufferSize);
	std::memcpy(buffer.data(), bestScoreFilePtr, bufferSize);

	CHECK(FileModule::WriteBufferToFile("Resource/Cache/Best.bin", buffer));

	bIsStartup_ = false;
}

void ConfigManager::SetCurrentBackgroundID(const EBackground& background)
{
	if (background == EBackground::Day)
	{
		currentBackgroundID_ = dayBackgroundID_;
	}
	else // background == EBackground::Night
	{
		currentBackgroundID_ = nightBackgroundID_;
	}
}

void ConfigManager::SetCurrentLevel(const ELevel& level)
{
	currentLevel_ = level;
}

void ConfigManager::SetCurrentBird(const EBird& bird)
{
	currentBird_ = bird;
}

void ConfigManager::RecordScore(int32_t score)
{
	if (score > bestScore_[currentLevel_])
	{
		bIsUpdateBestScore_ = true;
		bestScore_[currentLevel_] = score;
	}
	else
	{
		bIsUpdateBestScore_ = false;
	}

	recentScore_[currentLevel_] = score;
}

int32_t ConfigManager::GetRecentScore()
{
	return recentScore_[currentLevel_];
}

int32_t ConfigManager::GetBestScore()
{
	return bestScore_[currentLevel_];
}