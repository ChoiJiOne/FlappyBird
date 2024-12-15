#include "Assertion.h"
#include "ResourceManager.h"

ResourceManager& ResourceManager::Get()
{
	static ResourceManager instance;
	return instance;
}

void ResourceManager::Startup()
{
	CHECK(!bIsStartup_);
	
	bIsStartup_ = true;
}

void ResourceManager::Shutdown()
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

void ResourceManager::Destroy(const RUID& resourceID)
{
	CHECK(0 <= resourceID && resourceID < cacheSize_);

	if (cache_[resourceID] && cache_[resourceID]->IsInitialized())
	{
		cache_[resourceID]->Release();
		cache_[resourceID].reset();
	}
}

void ResourceManager::RegisterGlobalResource(const std::string& signature, const RUID& resourceID)
{
	CHECK(!IsAlreadyExistSignature(signature));
	globalResources_.insert({ signature, resourceID });
}

RUID ResourceManager::GetGlobalResource(const std::string& signature)
{
	CHECK(IsAlreadyExistSignature(signature));
	return globalResources_.at(signature);
}

void ResourceManager::UnregisterGlobalResource(const std::string& signature)
{
	if (IsAlreadyExistSignature(signature))
	{
		globalResources_.erase(signature);
	}
}

bool ResourceManager::IsAlreadyExistSignature(const std::string& signature) const
{
	return globalResources_.find(signature) != globalResources_.end();
}