// Chukwuyenum Opone Copyright 2026


#include "FIA/Public/Components/TimeManagerComponent.h"

#include "Library/GameEventLibrary.h"


UTimeManagerComponent::UTimeManagerComponent()
{
	
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false; // only ticks while a countdown is active
}

void UTimeManagerComponent::StartCountdown(const float DurationSeconds, const float InTickInterval)
{
	TimeRemaining = DurationSeconds;
	TickInterval = FMath::Max(0.01f, InTickInterval);
	AccumulatedTime = 0.f;
	bIsActive = true;
	bPaused = false;
	SetComponentTickEnabled(true);

	OnTimeTick.Broadcast(TimerType, TimeRemaining); // fire immediately so UI shows the starting value
}

void UTimeManagerComponent::StopTimer()
{
	bIsActive = false;
	bPaused = false;
	SetComponentTickEnabled(false);
}


// Called every frame
void UTimeManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsActive || bPaused) return;

	TimeRemaining = FMath::Max(0.f, TimeRemaining - DeltaTime);
	AccumulatedTime += DeltaTime;

	if (AccumulatedTime >= TickInterval)
	{
		AccumulatedTime = 0.f;
		switch (TimerType)
		{
		case ETimerType::Countdown:
			UGameEventLibrary::NotifyCountDownTimer(GetOwner(), GetTimeTextFormat(TimeRemaining));
			break;
		case ETimerType::Adventure:
			UGameEventLibrary::NotifyAdventureTimer(GetOwner(), GetTimeTextFormat(TimeRemaining));
			break;
		case ETimerType::Quiz:
			UGameEventLibrary::NotifyQuizTimer(GetOwner(), GetTimeTextFormat(TimeRemaining));
			break;
		}
		OnTimeTick.Broadcast(TimerType, TimeRemaining);
	}

	if (TimeRemaining <= 0.f)
	{
		StopTimer();
		OnTimeExpired.Broadcast(TimerType);
	}
}

FText UTimeManagerComponent::GetTimeTextFormat(const float TimeInSeconds)
{
	const int32 TotalSeconds = FMath::Max(0, FMath::FloorToInt(TimeInSeconds));

	const int32 Minutes = TotalSeconds / 60;
	const int32 Seconds = TotalSeconds % 60;

	return FText::Format(
		FText::FromString(TEXT("{0}:{1}")),
		FText::AsNumber(Minutes),
		FText::AsNumber(
			Seconds,
			&FNumberFormattingOptions()
				.SetMinimumIntegralDigits(2)
				.SetMaximumIntegralDigits(2))
	);
}

