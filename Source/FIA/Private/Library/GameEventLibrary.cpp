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
