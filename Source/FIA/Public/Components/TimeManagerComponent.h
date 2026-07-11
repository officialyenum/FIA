// Chukwuyenum Opone Copyright 2026
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimeManagerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimeTick, float, TimeRemaining);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimeExpired);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FIA_API UTimeManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTimeManagerComponent();
	
	UPROPERTY(BlueprintAssignable, Category = "Timer")
	FOnTimeTick OnTimeTick;

	UPROPERTY(BlueprintAssignable, Category = "Timer")
	FOnTimeExpired OnTimeExpired;
	
	UFUNCTION(BlueprintCallable, Category = "Timer")
	void StartCountdown(float DurationSeconds, float InTickInterval = 1.0f);

	UFUNCTION(BlueprintCallable, Category = "Timer")
	void StopTimer();

	UFUNCTION(BlueprintCallable, Category = "Timer")
	void PauseTimer() { bPaused = true; }

	UFUNCTION(BlueprintCallable, Category = "Timer")
	void ResumeTimer() { bPaused = false; }

	UFUNCTION(BlueprintPure, Category = "Timer")
	float GetTimeRemaining() const { return TimeRemaining; }

	UFUNCTION(BlueprintPure, Category = "Timer")
	bool IsTimerActive() const { return bIsActive; }
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
private:
	float TimeRemaining = 0.f;
	float TickInterval = 1.f;
	float AccumulatedTime = 0.f;
	bool bIsActive = false;
	bool bPaused = false;
};
