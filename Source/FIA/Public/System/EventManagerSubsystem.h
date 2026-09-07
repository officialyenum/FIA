// Chukwuyenum Opone Copyright 2026

#pragma once

#include "CoreMinimal.h"
#include "Data/QuizDataDefinition.h"
#include "Subsystems/WorldSubsystem.h"
#include "EventManagerSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWarmUpMessage, const FText&, WarmUpText);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnnouncementMessage, const FText&, AnnouncementText);
/**
 * 
 */
UCLASS()
class FIA_API UEventManagerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	// Broadcast Warmup countdown to UI
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnWarmUpMessage OnWarmUpMessage;
	
	// Broadcast Announcements to UI
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnAnnouncementMessage OnAnnouncementMessage;
	
};
