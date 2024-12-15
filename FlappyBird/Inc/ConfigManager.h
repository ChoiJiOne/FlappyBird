#pragma once

#include <map>

#include "IManager.h"
#include "IResource.h"


/**
 * @brief 전체 설정을 관리하는 매니저입니다.
 * 
 * @note 이 클래스는 싱글턴입니다.
 */
class ConfigManager : public IManager
{
public:
	/**
	 * @brief 게임의 백그라운드 종류입니다.
	 */
	enum class EBackground : int32_t
	{
		Day   = 0x00,
		Night = 0x01,
	};


	/**
	 * @brief 게임의 레벨입니다.
	 */
	enum class ELevel : int32_t
	{
		Easy   = 0x00,
		Normal = 0x01,
		Hard   = 0x02,
	};


	/**
	 * @brief 새 종류입니다.
	 */
	enum class EBird : int32_t
	{
		Blue   = 0x01,
		Red    = 0x02,
		Yellow = 0x03,
	};


public:
	/**
	 * @brief 전체 설정을 관리하는 매니저의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(ConfigManager);


	/**
	 * @brief 전체 설정을 관리하는 매니저의 참조 인스턴스를 얻습니다.
	 *
	 * @return 전체 설정을 관리하는 매니저의 참조 인스턴스를 반환합니다.
	 */
	static ConfigManager& Get();


	/**
	 * @brief 전체 설정을 관리하는 매니저의 사용을 시작합니다.
	 *
	 * @note 이 메서드는 한 번만 호출되어야 합니다.
	 */
	virtual void Startup() override;


	/**
	 * @brief 전체 설정을 관리하는 매니저의 사용을 종료합니다.
	 *
	 * @note
	 * - 애플리케이션 종료 전에 이 메서드를 반드시 호출하여 내부를 정리해야 합니다.
	 * - 이 메서드는 반드시 한 번만 호출되어야 합니다.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief 현재 배경 리소스의 ID 값을 얻습니다.
	 * 
	 * @return 현재 배경 리소스의 ID 값을 반환합니다.
	 */
	RUID GetCurrentBackgroundID() const { return currentBackgroundID_; }


	/**
	 * @brief 현재 배경을 설정합니다.
	 * 
	 * @param background 설정할 백그라운드입니다.
	 */
	void SetCurrentBackgroundID(const EBackground& background);


	/**
	 * @brief 현재 게임 난이도를 얻습니다.
	 * 
	 * @return 현재 게임 난이도를 반환합니다.
	 */
	ELevel GetCurrentLevel() const { return currentLevel_; }


	/**
	 * @brief 현재 게임 난이도를 설정합니다.
	 * 
	 * @param level 설정할 게임 난이도입니다.
	 */
	void SetCurrentLevel(const ELevel& level);


	/**
	 * @brief 현재 새를 얻습니다.
	 * 
	 * @return 현재 새를 반환합니다.
	 */
	EBird GetCurrentBird() const { return currentBird_; }


	/**
	 * @brief 현재 새를 설정합니다.
	 * 
	 * @param brid 설정할 새입니다.
	 */
	void SetCurrentBird(const EBird& bird);


	/**
	 * @brief 점수를 등록합니다.
	 * 
	 * @param score 등록할 점수입니다.
	 */
	void RecordScore(int32_t score);


	/**
	 * @brief 현재 레벨의 최근 점수를 얻습니다.
	 * 
	 * @return 현재 레벨의 최근 점수를 반환합니다.
	 */
	int32_t GetRecentScore();


	/**
	 * @brief 현재 레벨의 최고 점수를 얻습니다.
	 * 
	 * @return 현재 레벨의 최고 점수를 반환합니다.
	 */
	int32_t GetBestScore();


	/**
	 * @brief 최고 기록이 갱신되었는지 확인합니다.
	 * 
	 * @return 최고 기록이 갱신되었다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsUpdateBestScore() { return bIsUpdateBestScore_; }


private:
	/**
	 * @brief 전체 설정을 관리하는 매니저에 디폴트 생성자와 빈 가상 소멸자를 삽입합니다.
	 */
	DEFAULT_CONSTRUCTOR_AND_VIRTUAL_DESTRUCTOR(ConfigManager);


private:
	/**
	 * @brief 현재 배경 리소스의 ID 값입니다.
	 */
	RUID currentBackgroundID_ = -1;

	
	/**
	 * @brief 낮 배경 리소스의 ID 값입니다.
	 */
	RUID dayBackgroundID_ = -1;


	/**
	 * @brief 밤 배경 리소스의 ID 값입니다.
	 */
	RUID nightBackgroundID_ = -1;


	/**
	 * @brief 현재 게임 난이도입니다.
	 */
	ELevel currentLevel_ = ELevel::Easy;


	/**
	 * @brief 현재 새 종류입니다.
	 */
	EBird currentBird_ = EBird::Yellow;


	/**
	 * @brief 최고 기록이 갱신되었는지 확인합니다.
	 */
	bool bIsUpdateBestScore_ = false;


	/**
	 * @brief 최근 기록된 레벨에 따른 스코어입니다.
	 */
	std::map<ELevel, int32_t> recentScore_;


	/**
	 * @brief 레벨에 따른 최고 스코어입니다.
	 */
	std::map<ELevel, int32_t> bestScore_;
};