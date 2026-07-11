// Chukwuyenum Opone Copyright 2026

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameSetupComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllPlayersReady);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerJoined, APlayerController*, NewPlayer);


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
	void SetMaxPlayers(const int32 NewMax) { MaxPlayers = FMath::Clamp(NewMax, 2, 4); }

	UFUNCTION(BlueprintPure, Category = "Setup")
	bool HasReachedMaxPlayers() const { return RegisteredPlayers.Num() >= MaxPlayers; }

	UFUNCTION(BlueprintPure, Category = "Setup")
	int32 GetPlayerCount() const { return RegisteredPlayers.Num(); }
};
