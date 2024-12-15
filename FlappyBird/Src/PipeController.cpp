#include "Assertion.h"
#include "PipeController.h"
#include "Pipe.h"

PipeController::PipeController(const std::vector<Pipe*>& pipes, float gap)
	: pipes_(pipes)
	, gap_(gap)
{
	for (Pipe* pipe : pipes_)
	{
		pipe->SetCanMove(false);
		pipe->SetStatus(Pipe::EStatus::Wait);
	}

	bIsInitialized_ = true;
}

PipeController::~PipeController()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void PipeController::Tick(float deltaSeconds)
{
	if (status_ == EStatus::Wait)
	{
		return;
	}

	for (Pipe* pipe : pipes_)
	{
		if (pipe->GetStatus() == Pipe::EStatus::Active)
		{
			continue;
		}

		bool bActive = true;
		for (Pipe* other : pipes_)
		{
			if (other->GetStatus() == Pipe::EStatus::Active && other->GetGapPipe(pipe) <= gap_)
			{
				bActive = false;
			}
		}

		if (bActive)
		{
			pipe->SetStatus(Pipe::EStatus::Active);
		}
	}
}

void PipeController::Render()
{
}

void PipeController::Release()
{
	if (bIsInitialized_)
	{
		bIsInitialized_ = false;
	}
}

void PipeController::SetStatus(const EStatus& status)
{
	if (status == EStatus::Wait)
	{
		status_ = status;

		for (Pipe* pipe : pipes_)
		{
			pipe->SetCanMove(false);
		}
	}
	else // status == EStatus::Active
	{
		status_ = status;

		for (Pipe* pipe : pipes_)
		{
			pipe->SetCanMove(true);
		}
	}
}
