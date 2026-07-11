// Chukwuyenum Opone Copyright 2026


#include "FIA/Public/Game/FiaGameMode.h"

#include "Components/GameRuleComponent.h"
#include "Components/TimeManagerComponent.h"
#include "Components/GameSetupComponent.h"
#include "FIA/FIA.h"
#include "Kismet/GameplayStatics.h"

AFiaGameMode::AFiaGameMode()
{
	GameSetup = CreateDefaultSubobject<UGameSetupComponent>(TEXT("GameSetup"));
	GameRule = CreateDefaultSubobject<UGameRuleComponent>(TEXT("GameRule"));

	CountdownTimer = CreateDefaultSubobject<UTimeManagerComponent>(TEXT("CountdownTimer"));
	AdventureTimer = CreateDefaultSubobject<UTimeManagerComponent>(TEXT("AdventureTimer"));
	QuizTimer = CreateDefaultSubobject<UTimeManagerComponent>(TEXT("QuizTimer"));
}

void AFiaGameMode::BeginPlay()
{
	Super::BeginPlay();
	// All components already exist and have had their own BeginPlay called by this point,
	// so wiring references here is safe - no ordering ambiguity.
	GameRule->Initialize(CountdownTimer, AdventureTimer, QuizTimer);
	//TODO: Remove later for testing use the handle players initialize players
	TArray<int32> Players;
	Players.Add(0);
	Players.Add(1);
	GameRule->InitializePlayers(Players);

	GameSetup->RegisterDefaultPlayer(0);
	GameSetup->OnAllPlayersReady.AddDynamic(this, &AFiaGameMode::HandleAllPlayersReady);
}

void AFiaGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	FIA_LOG_F("Logged In as %s", *NewPlayer->GetName());
}

void AFiaGameMode::HandleAllPlayersReady()
{
	GameRule->InitializePlayers(GameSetup->RegisteredPlayers);
	GameRule->StartCountdown();
}

void AFiaGameMode::AddGameScore(const int32 PlayerIndex, const int32 Points) const
{
	GameRule->AddGameScore(PlayerIndex, Points);
}
