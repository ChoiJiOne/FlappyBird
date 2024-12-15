#pragma once

#include <array>
#include <vector>
#include <cstdint>
#include <memory>

#include "IManager.h"
#include "IEntity.h"


/**
 * @brief 엔티티 관리를 수행하는 매니저입니다.
 * 
 * @note 이 클래스는 싱글턴입니다.
 */
class EntityManager : public IManager
{
public:
	/**
	 * @brief 엔티티 관리를 수행하는 매니저의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(EntityManager);


	/**
	 * @brief 엔티티 관리를 수행하는 매니저의 참조 인스턴스를 얻습니다.
	 * 
	 * @return 엔티티 관리를 수행하는 매니저의 참조 인스턴스를 반환합니다.
	 */
	static EntityManager& Get();


	/**
	 * @brief 엔티티 관리를 수행하는 매니저의 사용을 시작합니다.
	 *
	 * @note 이 메서드는 한 번만 호출되어야 합니다.
	 */
	virtual void Startup() override;


	/**
	 * @brief 엔티티 관리를 수행하는 매니저의 사용을 종료합니다.
	 *
	 * @note
	 * - 애플리케이션 종료 전에 이 메서드를 반드시 호출하여 내부를 정리해야 합니다.
	 * - 이 메서드는 반드시 한 번만 호출되어야 합니다.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief 엔티티를 생성합니다.
	 *
	 * @param args 엔티티의 생성자에 전달한 인자들입니다.
	 *
	 * @return 생성된 엔티티의 ID를 반환합니다.
	 */
	template <typename TEntity, typename... Args>
	EUID CreateID(Args&&... args)
	{
		CHECK(0 <= cacheSize_ && cacheSize_ < MAX_RESOURCE_SIZE);

		EUID entityID = -1;
		for (int32_t index = 0; index < cacheSize_; ++index)
		{
			if (!cache_[index])
			{
				entityID = static_cast<EUID>(index);
				break;
			}
		}

		if (entityID == -1)
		{
			entityID = cacheSize_++;
		}

		cache_[entityID] = std::make_unique<TEntity>(args...);
		cache_[entityID]->SetID(entityID);

		return entityID;
	}


	/**
	 * @brief 엔티티를 생성합니다.
	 *
	 * @param args 엔티티의 생성자에 전달한 인자들입니다.
	 *
	 * @return 생성된 엔티티의 ID를 반환합니다.
	 */
	template <typename TEntity, typename... Args>
	TEntity* CreateEntity(Args&&... args)
	{
		CHECK(0 <= cacheSize_ && cacheSize_ < MAX_RESOURCE_SIZE);

		EUID entityID = -1;
		for (int32_t index = 0; index < cacheSize_; ++index)
		{
			if (!cache_[index])
			{
				entityID = static_cast<EUID>(index);
				break;
			}
		}

		if (entityID == -1)
		{
			entityID = cacheSize_++;
		}

		cache_[entityID] = std::make_unique<TEntity>(args...);
		cache_[entityID]->SetID(entityID);

		return reinterpret_cast<TEntity*>(cache_[entityID].get());
	}


	/**
	 * @brief 엔티티 매니저가 관리하는 엔티티를 얻습니다.
	 *
	 * @param entityID 엔티티 ID입니다.
	 *
	 * @return 엔티티의 포인터를 얻습니다.
	 */
	template <typename TEntity>
	TEntity* GetEntity(const EUID& entityID)
	{
		CHECK(0 <= entityID && entityID < cacheSize_);

		TEntity* entity = reinterpret_cast<TEntity*>(cache_[entityID].get());
		CHECK(entity != nullptr);

		return entity;
	}

	
	/**
	 * @brief 엔티티를 매니저가 관리하는 엔티티를를 삭제합니다.
	 *
	 * @param entityID 삭제할 엔티티 ID입니다.
	 */
	void Destroy(const EUID& entityID);


	/**
	 * @brief 엔티티를 업데이트합니다.
	 * 
	 * @param entityID 업데이트할 엔티티 ID 입니다.
	 * @param deltaSeconds 초단위 델타 시간값입니다.
	 */
	void UpdateBatch(const EUID& entityID, float deltaSeconds);


	/**
	 * @brief 엔티티를 일괄 업데이트합니다.
	 * 
	 * @param entityIDs 일괄 업데이트할 엔티티 ID 목록입니다.
	 * @param deltaSeconds 초단위 델타 시간값입니다.
	 */
	void UpdateBatch(const std::vector<EUID>& entityIDs, float deltaSeconds);


	/**
	 * @brief 엔티티를 렌더링합니다.
	 *
	 * @param entityID 렌더링할 엔티티 ID 입니다.
	 */
	void RenderBatch(const EUID& entityID);


	/**
	 * @brief 엔티티를 일괄 렌더링합니다.
	 * 
	 * @param entityIDs 일괄 렌더링할 엔티티 ID 목록입니다.
	 */
	void RenderBatch(const std::vector<EUID>& entityIDs);
	

private:
	/**
	 * @brief 엔티티 관리를 수행하는 매니저에 디폴트 생성자와 빈 가상 소멸자를 삽입합니다.
	 */
	DEFAULT_CONSTRUCTOR_AND_VIRTUAL_DESTRUCTOR(EntityManager);


private:
	/**
	 * @brief 엔티티 매니저가 관리하는 최대 엔티티를 수입니다.
	 */
	static const uint32_t MAX_RESOURCE_SIZE = 1000;


	/**
	 * @brief 엔티티 캐시의 크기입니다.
	 */
	uint32_t cacheSize_ = 0;


	/**
	 * @brief 엔티티 매니저 내의 엔티티 캐시입니다.
	 */
	std::array<std::unique_ptr<IEntity>, MAX_RESOURCE_SIZE> cache_;
};