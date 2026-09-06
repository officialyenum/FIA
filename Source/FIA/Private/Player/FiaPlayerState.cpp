#include "Player/FiaPlayerState.h"

#include "Net/UnrealNetwork.h"

AFiaPlayerState::AFiaPlayerState()
{
	bReplicates = true;
}

void AFiaPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(
		AFiaPlayerState,
		ScoreData
	);
}

void AFiaPlayerState::OnRep_ScoreData()
{
	OnScoreDataChanged.Broadcast(ScoreData);
}

FQuizScoreData AFiaPlayerState::GetQuizScoreData() const
{
	return ScoreData;
}

void AFiaPlayerState::AddScore(const int32 Amount)
{
	if (!HasAuthority())
	{
		return;
	}

	ScoreData.AddScore(Amount);

	OnScoreDataChanged.Broadcast(ScoreData);
}

void AFiaPlayerState::RecordChestOpened()
{
	if (!HasAuthority())
	{
		return;
	}

	ScoreData.RecordChestOpened();

	OnScoreDataChanged.Broadcast(ScoreData);
}

void AFiaPlayerState::RecordQuizAnswered()
{
	if (!HasAuthority())
	{
		return;
	}

	ScoreData.RecordQuizAnswered();

	OnScoreDataChanged.Broadcast(ScoreData);
}

void AFiaPlayerState::RecordQuizMissed()
{
	if (!HasAuthority())
	{
		return;
	}

	ScoreData.RecordQuizMissed();

	OnScoreDataChanged.Broadcast(ScoreData);
}


