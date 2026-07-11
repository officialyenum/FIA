// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EventManagerSubsystem.generated.h"

UENUM(BlueprintType)
enum class EQuizAnswer : uint8
{
	None,
	OptionA,
	OptionB,
	OptionX,
	OptionY
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerOpenedChest, int32, PlayerId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerMissed, int32, PlayerId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerAnswered, int32, PlayerId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerAnsweredQuiz, int32, PlayerId, EQuizAnswer, Answer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerScoreUpdate, int32, PlayerId, int32, NewScore);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWarmUpMessage, FText, WarmUpText);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnnouncementMessage, FText, AnnouncementText);
/**
 * 
 */
UCLASS()
class FIA_API UEventManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	// Update Player Chests Opened in Game Rule and UI
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnPlayerOpenedChest OnPlayerOpenedChest;

	// Update Player Answered Missed in UI
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnPlayerMissed OnPlayerMissed;
	
	// Update Player Answered Score in UI
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnPlayerAnswered OnPlayerAnswered;

	// Notify Game Rules when player answers question
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnPlayerAnsweredQuiz OnPlayerAnsweredQuiz;
	
	// Update Player new Score in UI
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnPlayerScoreUpdate OnPlayerScoreUpdate;
	
	// Broadcast Warmup countdown to UI
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnWarmUpMessage OnWarmUpMessage;
	
	// Broadcast Announcements to UI
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnAnnouncementMessage OnAnnouncementMessage;
};
