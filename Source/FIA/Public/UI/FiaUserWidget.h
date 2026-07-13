// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FiaUserWidget.generated.h"

struct FQuizData;
enum class EQuizAnswer : uint8;
class UEventManagerSubsystem;
/**
 * 
 */
UCLASS()
class FIA_API UFiaUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
public:
	void BindEventManager();
	void UnBindEventManager();
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayerOpenedChest(int32 PlayerIndex);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayerMissed(int32 PlayerIndex);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayerAnswered(int32 PlayerIndex);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnScoreChanged(int32 PlayerIndex, int32 NewScore);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnWarmUpMessage(const FText& WarmUpText);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnAnnouncementMessage(const FText& AnnouncementText);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnQuizResultsBroadcast(const TArray<EQuizAnswer>& Results);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnQuizLoaded(const FQuizData& Results);
	
	// Listen to CountDown Time Changes
	UFUNCTION(BlueprintImplementableEvent)
	void OnCountDownTimeChanged(const FText& NewTime);
	
	// Listen to Adventure Time Changes
	UFUNCTION(BlueprintImplementableEvent)
	void OnAdventureTimeChanged(const FText& NewTime);
	
	// Listen to Quiz Time Changes
	UFUNCTION(BlueprintImplementableEvent)
	void OnQuizTimeChanged(const FText& NewTime);
private:
	UEventManagerSubsystem* EventManagerSubsystem;
};
