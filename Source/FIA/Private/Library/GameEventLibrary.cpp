// Chukwuyenum Opone Copyright 2026

#include "Library/GameEventLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "System/EventManagerSubsystem.h"

UEventManagerSubsystem* UGameEventLibrary::GetEventManagerSubsystem(const UObject* WorldContextObject)
{
	if (!WorldContextObject) return nullptr;
	const UWorld* World = WorldContextObject->GetWorld();
	if (!World) return nullptr;
	UEventManagerSubsystem* EventSubsystem = World->GetSubsystem<UEventManagerSubsystem>();
	return EventSubsystem;
}

void UGameEventLibrary::NotifyPlayerChestOpened(const UObject* WorldContextObject, const int32 PlayerId)
{
	if (!WorldContextObject) return;
	if (GetEventManagerSubsystem(WorldContextObject))
	{
		GetEventManagerSubsystem(WorldContextObject)->OnPlayerOpenedChest.Broadcast(PlayerId);
	}
}

void UGameEventLibrary::NotifyQuizLoaded(const UObject* WorldContextObject, const FQuizData& LoadedQuizData)
{
	if (!WorldContextObject) return;
	if (GetEventManagerSubsystem(WorldContextObject))
	{
		GetEventManagerSubsystem(WorldContextObject)->OnQuizLoaded.Broadcast(LoadedQuizData);
	}
}

void UGameEventLibrary::NotifyPlayerMissed(const UObject* WorldContextObject, const int32 PlayerId)
{
	if (!WorldContextObject) return;
	if (GetEventManagerSubsystem(WorldContextObject))
	{
		GetEventManagerSubsystem(WorldContextObject)->OnPlayerMissed.Broadcast(PlayerId);
	}
}

void UGameEventLibrary::NotifyPlayerAnswered(const UObject* WorldContextObject, const int32 PlayerId)
{
	if (!WorldContextObject) return;
	if (GetEventManagerSubsystem(WorldContextObject))
	{
		GetEventManagerSubsystem(WorldContextObject)->OnPlayerAnswered.Broadcast(PlayerId);
	}
}

void UGameEventLibrary::NotifyPlayerAnsweredQuiz(const UObject* WorldContextObject, const int32 PlayerId,
	const EQuizAnswer Answer)
{
	if (!WorldContextObject) return;
	if (GetEventManagerSubsystem(WorldContextObject))
	{
		GetEventManagerSubsystem(WorldContextObject)->OnPlayerAnsweredQuiz.Broadcast(PlayerId, Answer);
	}
}

void UGameEventLibrary::NotifyGameStateChanged(const UObject* WorldContextObject, EGameFlowState NewState)
{
	if (GetEventManagerSubsystem(WorldContextObject))
	{
		GetEventManagerSubsystem(WorldContextObject)->OnGameStateChanged.Broadcast(NewState);
	}
}

void UGameEventLibrary::NotifyScoreChanged(const UObject* WorldContextObject, const int32 PlayerId, int32 NewScore)
{
	if (GetEventManagerSubsystem(WorldContextObject))
	{
		GetEventManagerSubsystem(WorldContextObject)->OnScoreChanged.Broadcast(PlayerId, NewScore);
	}
}

void UGameEventLibrary::NotifyQuizResultsBroadcast(const UObject* WorldContextObject,
	const TArray<EQuizAnswer>& Results)
{
	if (!WorldContextObject) return;
	if (GetEventManagerSubsystem(WorldContextObject))
	{
		GetEventManagerSubsystem(WorldContextObject)->OnQuizResultsBroadcast.Broadcast(Results);
	}
}

void UGameEventLibrary::NotifyGameResultBroadcast(const UObject* WorldContextObject, const TArray<FPlayerData>& Results)
{
	if (!WorldContextObject) return;
	if (GetEventManagerSubsystem(WorldContextObject))
	{
		GetEventManagerSubsystem(WorldContextObject)->OnLeaderboardBroadcast.Broadcast(Results);
	}
}

void UGameEventLibrary::NotifyGameEnded(const UObject* WorldContextObject, const int32 WinnerId)
{
	if (!WorldContextObject) return;
	if (GetEventManagerSubsystem(WorldContextObject))
	{
		GetEventManagerSubsystem(WorldContextObject)->OnGameEnded.Broadcast(WinnerId);
	}
}

void UGameEventLibrary::NotifyWarmUpMessage(const UObject* WorldContextObject, const int32 PlayerId, const FText WarmUpText)
{
	if (!WorldContextObject) return;
	if (GetEventManagerSubsystem(WorldContextObject))
	{
		GetEventManagerSubsystem(WorldContextObject)->OnWarmUpMessage.Broadcast(WarmUpText);
	}
}

void UGameEventLibrary::NotifyAnnouncementMessage(const UObject* WorldContextObject, const int32 PlayerId,
	const FText AnnouncementText)
{
	if (!WorldContextObject) return;
	if (GetEventManagerSubsystem(WorldContextObject))
	{
		GetEventManagerSubsystem(WorldContextObject)->OnAnnouncementMessage.Broadcast(AnnouncementText);
	}
}

void UGameEventLibrary::NotifyCountDownTimer(const UObject* WorldContextObject, const FText& NewTime)
{
	if (!WorldContextObject) return;
	if (GetEventManagerSubsystem(WorldContextObject))
	{
		GetEventManagerSubsystem(WorldContextObject)->OnCountDownTimeChanged.Broadcast(NewTime);
	}
}

void UGameEventLibrary::NotifyAdventureTimer(const UObject* WorldContextObject, const FText& NewTime)
{
	if (!WorldContextObject) return;
	if (GetEventManagerSubsystem(WorldContextObject))
	{
		GetEventManagerSubsystem(WorldContextObject)->OnAdventureTimeChanged.Broadcast(NewTime);
	}
}

void UGameEventLibrary::NotifyQuizTimer(const UObject* WorldContextObject, const FText& NewTime)
{
	if (!WorldContextObject) return;
	if (GetEventManagerSubsystem(WorldContextObject))
	{
		GetEventManagerSubsystem(WorldContextObject)->OnQuizTimeChanged.Broadcast(NewTime);
	}
}
