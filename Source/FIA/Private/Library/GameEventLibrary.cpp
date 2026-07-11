// Chukwuyenum Opone Copyright 2026

#include "Library/GameEventLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "System/EventManagerSubsystem.h"

UEventManagerSubsystem* UGameEventLibrary::GetEventManagerSubsystem(const UObject* WorldContextObject)
{
	if (!WorldContextObject) return nullptr;
	const UGameInstance* GI = UGameplayStatics::GetGameInstance(WorldContextObject);
	if (!GI) return nullptr;
	UEventManagerSubsystem* EventSubsystem = GI->GetSubsystem<UEventManagerSubsystem>();
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

void UGameEventLibrary::NotifyPlayerScoreUpdate(const UObject* WorldContextObject, const int32 PlayerId, const int32 NewScore)
{
	if (!WorldContextObject) return;
	if (GetEventManagerSubsystem(WorldContextObject))
	{
		GetEventManagerSubsystem(WorldContextObject)->OnPlayerScoreUpdate.Broadcast(PlayerId, NewScore);
	}
}

void UGameEventLibrary::NotifyGameStateChanged(const UObject* WorldContextObject, const EGameFlowState NewState)
{
	if (!WorldContextObject) return;
	if (GetEventManagerSubsystem(WorldContextObject))
	{
		GetEventManagerSubsystem(WorldContextObject)->OnGameStateChanged.Broadcast(NewState);
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

void UGameEventLibrary::NotifyGameEnded(const UObject* WorldContextObject, const int32 PlayerId)
{
	if (!WorldContextObject) return;
	if (GetEventManagerSubsystem(WorldContextObject))
	{
		GetEventManagerSubsystem(WorldContextObject)->OnGameEnded.Broadcast(PlayerId);
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
