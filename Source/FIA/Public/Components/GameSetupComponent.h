// Chukwuyenum Opone Copyright 2026

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameSetupComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllPlayersReady);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerJoined, int32, PlayerIndex);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FIA_API UGameSetupComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UGameSetupComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta = (ClampMin = "2", ClampMax = "4"))
	int32 MaxPlayers = 4;

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	TArray<int32> RegisteredPlayers;

	UPROPERTY(BlueprintAssignable)
	FOnAllPlayersReady OnAllPlayersReady;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerJoined OnPlayerJoined;
	
	// Call once, e.g. from GameMode::BeginPlay, to register the default Player 1
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void RegisterDefaultPlayer(int32 PlayerIndex);

	// Call when a new controller presses "Start" during character select
	UFUNCTION(BlueprintCallable, Category = "Setup")
	bool TryJoinLocalPlayer(int32 ControllerId);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	FORCEINLINE void SetMaxPlayers(const int32 NewMax) { MaxPlayers = FMath::Clamp(NewMax, 2, 4); }
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	FORCEINLINE int32 GetMaxPlayers() const { return MaxPlayers; }

	UFUNCTION(BlueprintPure, Category = "Setup")
	FORCEINLINE bool HasReachedMaxPlayers() const { return RegisteredPlayers.Num() >= MaxPlayers; }

	UFUNCTION(BlueprintPure, Category = "Setup")
	FORCEINLINE int32 GetRegisteredPlayerCount() const { return RegisteredPlayers.Num(); }
};
