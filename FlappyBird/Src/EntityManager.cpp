#include "Assertion.h"
#include "EntityManager.h"

EntityManager& EntityManager::Get()
{
	static EntityManager instance;
	return instance;
}

void EntityManager::Startup()
{
	CHECK(!bIsStartup_);

	bIsStartup_ = true;
}

void EntityManager::Shutdown()
{
	CHECK(bIsStartup_);

	for (auto& cache : cache_)
	{
		if (cache && cache->IsInitialized())
		{
			cache->Release();
			cache.reset();
		}
	}

	bIsStartup_ = false;
}

void EntityManager::Destroy(const EUID& entityID)
{
	CHECK(0 <= entityID && entityID < cacheSize_);

	if (cache_[entityID] && cache_[entityID]->IsInitialized())
	{
		cache_[entityID]->Release();
		cache_[entityID].reset();
	}
}

void EntityManager::UpdateBatch(const EUID& entityID, float deltaSeconds)
{
	CHECK(0 <= entityID && entityID < cacheSize_);

	if (cache_[entityID]->IsInitialized())
	{
		cache_[entityID]->Tick(deltaSeconds);
	}
}

void EntityManager::UpdateBatch(const std::vector<EUID>& entityIDs, float deltaSeconds)
{
	for (const EUID& entityID : entityIDs)
	{
		CHECK(0 <= entityID && entityID < cacheSize_);

		if (cache_[entityID]->IsInitialized())
		{
			cache_[entityID]->Tick(deltaSeconds);
		}
	}
}

void EntityManager::RenderBatch(const EUID& entityID)
{
	CHECK(0 <= entityID && entityID < cacheSize_);

	if (cache_[entityID]->IsInitialized())
	{
		cache_[entityID]->Render();
	}
}

void EntityManager::RenderBatch(const std::vector<EUID>& entityIDs)
{
	for (const EUID& entityID : entityIDs)
	{
		CHECK(0 <= entityID && entityID < cacheSize_);

		if (cache_[entityID]->IsInitialized())
		{
			cache_[entityID]->Render();
		}
	}
}