// Chukwuyenum Opone Copyright 2026

#pragma once

#include "CoreMinimal.h"
#include "Data/QuizDataDefinition.h"
#include "Subsystems/WorldSubsystem.h"
#include "EventManagerSubsystem.generated.h"

struct FPlayerData;
enum class EQuizAnswer : uint8;
enum class EGameFlowState : uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerOpenedChest, int32, PlayerId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuizLoaded, const FQuizData&, ActiveQuiz);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerMissed, int32, PlayerId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerAnswered, int32, PlayerId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerAnsweredQuiz, int32, PlayerId, EQuizAnswer, Answer);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameStateChanged, EGameFlowState, NewState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnScoreChanged, int32, Player, int32, NewScore);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuizResultsBroadcast, const TArray<EQuizAnswer>&, Results);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLeaderboardBroadcast, const TArray<FPlayerData>&, PlayerResults);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameEnded, int32, Winner);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWarmUpMessage, const FText&, WarmUpText);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnnouncementMessage, const FText&, AnnouncementText);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCountDownTimeChanged, const FText&, NewTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAdventureTimeChanged, const FText&, NewTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuizTimeChanged, const FText&, NewTime);
/**
 * 
 */
UCLASS()
class FIA_API UEventManagerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	// Update Player Chests Opened in Game Rule and UI
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnPlayerOpenedChest OnPlayerOpenedChest;
	
	// Update Quiz UI when Opened in Game Rule and UI
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnQuizLoaded OnQuizLoaded;
	
	// Update Player Answered Missed in UI
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnPlayerMissed OnPlayerMissed;
	
	// Update Player Answered Score in UI
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnPlayerAnswered OnPlayerAnswered;

	// Notify Game Rules when player answers question
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnPlayerAnsweredQuiz OnPlayerAnsweredQuiz;
	
	// Notify Game State Changed
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnGameStateChanged OnGameStateChanged;
	
	// Notify Player Score Changed
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnScoreChanged OnScoreChanged;
	
	// Notify Quiz Result of all players
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnQuizResultsBroadcast OnQuizResultsBroadcast;
	
	// Notify Game Results for all player
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnLeaderboardBroadcast OnLeaderboardBroadcast;
	
	
	// Notify Game Has Ended
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnGameEnded OnGameEnded;
	
	// Broadcast Warmup countdown to UI
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnWarmUpMessage OnWarmUpMessage;
	
	// Broadcast Announcements to UI
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnAnnouncementMessage OnAnnouncementMessage;
	
	// Broadcast CountDown Time in Text Format to UI
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnCountDownTimeChanged OnCountDownTimeChanged;
	
	// Broadcast Adventure Time in Text Format to UI
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnAdventureTimeChanged OnAdventureTimeChanged;
	
	// Broadcast Quiz Time in Text Format to UI
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnQuizTimeChanged OnQuizTimeChanged;
	
};
