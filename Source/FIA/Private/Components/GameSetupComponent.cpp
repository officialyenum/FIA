// Chukwuyenum Opone Copyright 2026


#include "Components/GameSetupComponent.h"
#include "Engine/World.h"
#include "Engine/LocalPlayer.h"
#include "FIA/FIA.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"


UGameSetupComponent::UGameSetupComponent()
{
	PrimaryComponentTick.bCanEverTick = false; // event-driven, no tick needed
}

void UGameSetupComponent::RegisterDefaultPlayer(const int32 PlayerIndex)
{
	if (RegisteredPlayers.Contains(PlayerIndex)) return;

	RegisteredPlayers.Add(PlayerIndex);
	OnPlayerJoined.Broadcast(PlayerIndex);
}

bool UGameSetupComponent::TryJoinLocalPlayer(const int32 ControllerId)
{
	if (HasReachedMaxPlayers()) return false;

	const UWorld* World = GetWorld();
	UGameInstance* GI = World ? World->GetGameInstance() : nullptr;
	if (!GI) return false;
	
	FString Error;
	
	
    const ULocalPlayer* NewLocalPlayer = GI->CreateLocalPlayer(ControllerId, Error, true);
    if (!NewLocalPlayer)
    {
        FIA_ERROR_F("GameSetup: failed to create local player - %s", *Error);
        return false;
    }

    if (APlayerController* NewPC = NewLocalPlayer->PlayerController)
    {
        RegisteredPlayers.AddUnique(ControllerId);
        OnPlayerJoined.Broadcast(ControllerId);
    }

    if (HasReachedMaxPlayers())
    {
        OnAllPlayersReady.Broadcast();
    }
    return true;
}

