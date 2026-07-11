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
	
	// Notify Player Missed in so anybody listening can update
	UFUNCTION(BlueprintCallable, Category = "Event Library", meta=(WorldContext="WorldContextObject"))
	static void NotifyPlayerMissed(const UObject* WorldContextObject, const int32 PlayerId);
	
	// Notify Player Answered so any object listening can update
	UFUNCTION(BlueprintCallable, Category = "Event Library", meta=(WorldContext="WorldContextObject"))
	static void NotifyPlayerAnswered(const UObject* WorldContextObject, const int32 PlayerId);
	
	// Notify Game Rules when player answers question
	UFUNCTION(BlueprintCallable, Category = "Event Library", meta=(WorldContext="WorldContextObject"))
	static void NotifyPlayerAnsweredQuiz(const UObject* WorldContextObject, const int32 PlayerId, const EQuizAnswer Answer);
	
	// Notify Warm Up Count Down to UI Listening
	UFUNCTION(BlueprintCallable, Category = "Event Library", meta=(WorldContext="WorldContextObject"))
	static void NotifyWarmUpMessage(const UObject* WorldContextObject, const int32 PlayerId, FText WarmUpText);
	
	// Notify Warm Up Count Down to UI Listening
	UFUNCTION(BlueprintCallable, Category = "Event Library", meta=(WorldContext="WorldContextObject"))
	static void NotifyAnnouncementMessage(const UObject* WorldContextObject, const int32 PlayerId, FText AnnouncementText);
	
};
