// Chukwuyenum Opone Copyright 2026


#include "Components/GameSetupComponent.h"
#include "Engine/World.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"


UGameSetupComponent::UGameSetupComponent()
{
	PrimaryComponentTick.bCanEverTick = false; // event-driven, no tick needed
}

void UGameSetupComponent::RegisterDefaultPlayer(APlayerController* FirstController)
{
	if (!FirstController || RegisteredPlayers.Contains(FirstController)) return;

	RegisteredPlayers.Add(FirstController);
	OnPlayerJoined.Broadcast(FirstController);
}

bool UGameSetupComponent::TryJoinLocalPlayer(int32 ControllerId)
{
	if (HasReachedMaxPlayers()) return false;

	const UWorld* World = GetWorld();
	UGameInstance* GI = World ? World->GetGameInstance() : nullptr;
	if (!GI) return false;
	
	FString Error;
	
	
    const ULocalPlayer* NewLocalPlayer = GI->CreateLocalPlayer(ControllerId, Error, true);
    if (!NewLocalPlayer)
    {
        UE_LOG(LogTemp, Warning, TEXT("GameSetup: failed to create local player - %s"), *Error);
        return false;
    }

    if (APlayerController* NewPC = NewLocalPlayer->PlayerController)
    {
        RegisteredPlayers.AddUnique(NewPC);
        OnPlayerJoined.Broadcast(NewPC);
    }

    if (HasReachedMaxPlayers())
    {
        OnAllPlayersReady.Broadcast();
    }
    return true;
}

