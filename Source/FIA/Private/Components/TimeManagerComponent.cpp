// Chukwuyenum Opone.


#include "FIA/Public/Components/TimeManagerComponent.h"


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

	OnTimeTick.Broadcast(TimeRemaining); // fire immediately so UI shows the starting value
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
		OnTimeTick.Broadcast(TimeRemaining);
	}

	if (TimeRemaining <= 0.f)
	{
		StopTimer();
		OnTimeExpired.Broadcast();
	}
}

