// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FiaUserWidget.generated.h"

class AFiaPlayerState;
class UQuizManagerSubsystem;
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
	void OnAnnouncementMessage(const FText& AnnouncementText);
	// Listen to CountDown Time Changes
	UFUNCTION(BlueprintImplementableEvent)
	void OnCountDownTimeChanged(const FText& NewTime);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnQuizStarted();
	UFUNCTION(BlueprintImplementableEvent)
	void OnQuizFinished(bool bTimedOut);
	UFUNCTION(BlueprintImplementableEvent)
	void OnQuizPlayerAnswered( AFiaPlayerState* PlayerState, EQuizAnswer Answer);
	UFUNCTION(BlueprintImplementableEvent)
	void OnQuizPlayerScored(AFiaPlayerState* PlayerState, int32 PointsAdded, int32 NewScore);
	
	UPROPERTY(BlueprintReadOnly)
	UQuizManagerSubsystem* QuizManagerSubsystem;
	UPROPERTY(BlueprintReadOnly)
	UEventManagerSubsystem* EventManagerSubsystem;
};
