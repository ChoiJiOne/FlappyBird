#include "Assertion.h"
#include "AudioManager.h"

void AudioManager::Startup()
{
	CHECK(!bIsStartup_);

	audioEngine_ = std::make_unique<ma_engine>();
	CHECK(ma_engine_init(nullptr, audioEngine_.get()) == MA_SUCCESS);

	bIsStartup_ = true;
}

void AudioManager::Shutdown()
{
	CHECK(bIsStartup_);

	ma_engine_uninit(audioEngine_.get());
	audioEngine_.reset();

	bIsStartup_ = false;
}