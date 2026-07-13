// Chukwuyenum Opone Copyright 2026

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "System/EventManagerSubsystem.h"
#include "GameEventLibrary.generated.h"

enum class EQuizAnswer : uint8;
class UEventManagerSubsystem;
/**
 * 
 */
UCLASS()
class FIA_API UGameEventLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(Blueprintpure, Category = "Event Library", meta=(WorldContext="WorldContextObject"))
	static UEventManagerSubsystem* GetEventManagerSubsystem(const UObject* WorldContextObject);
	
	// Notify player has opened chest so any object  listening can update
	UFUNCTION(BlueprintCallable, Category = "Event Library", meta=(WorldContext="WorldContextObject"))
	static void NotifyPlayerChestOpened(const UObject* WorldContextObject, const int32 PlayerId);
	
	// Notify player has opened chest so any object  listening can update
	UFUNCTION(BlueprintCallable, Category = "Event Library", meta=(WorldContext="WorldContextObject"))
	static void NotifyQuizLoaded(const UObject* WorldContextObject, const FQuizData& LoadedQuizData);
	
	// Notify Player Missed in so anybody listening can update
	UFUNCTION(BlueprintCallable, Category = "Event Library", meta=(WorldContext="WorldContextObject"))
	static void NotifyPlayerMissed(const UObject* WorldContextObject, const int32 PlayerId);
	
	// Notify Player Answered so any object listening can update
	UFUNCTION(BlueprintCallable, Category = "Event Library", meta=(WorldContext="WorldContextObject"))
	static void NotifyPlayerAnswered(const UObject* WorldContextObject, const int32 PlayerId);
	
	// Notify Game Rules when player answers question
	UFUNCTION(BlueprintCallable, Category = "Event Library", meta=(WorldContext="WorldContextObject"))
	static void NotifyPlayerAnsweredQuiz(const UObject* WorldContextObject, const int32 PlayerId, const EQuizAnswer Answer);
	
	// Notify Player Score has changed
	UFUNCTION(BlueprintCallable, Category = "Event Library", meta=(WorldContext="WorldContextObject"))
	static void NotifyGameStateChanged(const UObject* WorldContextObject, EGameFlowState NewState);
	
	// Notify Player Score has changed
	UFUNCTION(BlueprintCallable, Category = "Event Library", meta=(WorldContext="WorldContextObject"))
	static void NotifyScoreChanged(const UObject* WorldContextObject, const int32 PlayerId, int32 NewScore);
	// Notify Quiz Timeout or all players answered result
	UFUNCTION(BlueprintCallable, Category = "Event Library", meta=(WorldContext="WorldContextObject"))
	static void NotifyQuizResultsBroadcast(const UObject* WorldContextObject, const TArray<EQuizAnswer>& Results);
	
	// Notify Game Results for Leaderboard
	UFUNCTION(BlueprintCallable, Category = "Event Library", meta=(WorldContext="WorldContextObject"))
	static void NotifyGameResultBroadcast(const UObject* WorldContextObject, const TArray<FPlayerData>& Results);
	
	// Notify Game has Ended
	UFUNCTION(BlueprintCallable, Category = "Event Library", meta=(WorldContext="WorldContextObject"))
	static void NotifyGameEnded(const UObject* WorldContextObject, const int32 WinnerId);
	
	// Notify Warm Up Count Down to UI Listening
	UFUNCTION(BlueprintCallable, Category = "Event Library", meta=(WorldContext="WorldContextObject"))
	static void NotifyWarmUpMessage(const UObject* WorldContextObject, const int32 PlayerId, FText WarmUpText);
	
	// Notify Warm Up Count Down to UI Listening
	UFUNCTION(BlueprintCallable, Category = "Event Library", meta=(WorldContext="WorldContextObject"))
	static void NotifyAnnouncementMessage(const UObject* WorldContextObject, const int32 PlayerId, FText AnnouncementText);
	
	
	// Notify CountDown Timer
	UFUNCTION(BlueprintCallable, Category = "Event Library", meta=(WorldContext="WorldContextObject"))
	static void NotifyCountDownTimer(const UObject* WorldContextObject, const FText& NewTime);
	// Notify Adventure Timer
	UFUNCTION(BlueprintCallable, Category = "Event Library", meta=(WorldContext="WorldContextObject"))
	static void NotifyAdventureTimer(const UObject* WorldContextObject, const FText& NewTime);
	// Notify Quiz Timer
	UFUNCTION(BlueprintCallable, Category = "Event Library", meta=(WorldContext="WorldContextObject"))
	static void NotifyQuizTimer(const UObject* WorldContextObject, const FText& NewTime);
	
};
