#include "Game/FiaGameState.h"

#include "Net/UnrealNetwork.h"

AFiaGameState::AFiaGameState()
{
	bReplicates = true;
}

void AFiaGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AFiaGameState, FiaGameMode);
	DOREPLIFETIME(AFiaGameState, QuizEndServerTime);
	DOREPLIFETIME(AFiaGameState, QuizQuestionID);
}

void AFiaGameState::OnRep_FiaGameMode() const
{
	OnFiaGameModeChanged.Broadcast(FiaGameMode);

	if (FiaGameMode == EFiaGameMode::Quiz)
	{
		OnQuizStarted.Broadcast();
	}
	else
	{
		OnQuizFinished.Broadcast(
			bLastFinishTimedOut
		);
	}
}

void AFiaGameState::SetQuizMode(EFiaGameMode NewMode)
{
	if (!HasAuthority())
	{
		return;
	}

	FiaGameMode = NewMode;

	// Important for listen server
	OnRep_FiaGameMode();
}

void AFiaGameState::StartQuiz(int32 QuestionID, float QuizDuration)
{
	if (!HasAuthority())
	{
		return;
	}

	QuizQuestionID = QuestionID;

	QuizEndServerTime =
		GetServerWorldTimeSeconds() + QuizDuration;

	SetQuizMode(EFiaGameMode::Quiz);
}

void AFiaGameState::FinishQuiz(bool bTimedOut)
{
	if (!HasAuthority())
	{
		return;
	}

	bLastFinishTimedOut = bTimedOut;
	SetQuizMode(EFiaGameMode::Adventure);
}
