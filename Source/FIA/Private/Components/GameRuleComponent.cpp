// Chukwuyenum Opone Copyright 2026


#include "Components/GameRuleComponent.h"

#include "Components/TimeManagerComponent.h"
#include "Data/QuizDataDefinition.h"
#include "FIA/FIA.h"
#include "Kismet/GameplayStatics.h"
#include "Library/GameEventLibrary.h"


// Sets default values for this component's properties
UGameRuleComponent::UGameRuleComponent()
{
	PrimaryComponentTick.bCanEverTick = false; // timers do the ticking, not this component
}

void UGameRuleComponent::Initialize(UTimeManagerComponent* InCountdownTimer, UTimeManagerComponent* InAdventureTimer,
UTimeManagerComponent* InQuizTimer)
{
	if (bInitialized) return; // guard against double-binding if called more than once
	if (GetGameDataDefinition() == nullptr)
	{
		FIA_ERROR("Ensure Game Data Definition is set in Game Mode -> Game Rule Component");
		return;
	}
	if (GetQuizDataDefinition() == nullptr)
	{
		FIA_ERROR("Ensure Quiz Data Definition is set in Game Mode -> Game Rule Component");
		return;
	}

	CountdownTimer = InCountdownTimer;
	AdventureTimer = InAdventureTimer;
	QuizTimer = InQuizTimer;

	check(CountdownTimer && AdventureTimer && QuizTimer);
	CountdownTimer->SetTimerType(ETimerType::Countdown);
	AdventureTimer->SetTimerType(ETimerType::Adventure);
	QuizTimer->SetTimerType(ETimerType::Quiz);

	CountdownTimer->OnTimeExpired.AddDynamic(this, &UGameRuleComponent::HandleCountdownExpired);
	AdventureTimer->OnTimeExpired.AddDynamic(this, &UGameRuleComponent::HandleAdventureExpired);
	QuizTimer->OnTimeExpired.AddDynamic(this, &UGameRuleComponent::HandleQuizExpired);

	bInitialized = true;
}


void UGameRuleComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UGameRuleComponent::StartCountdown()
{
	SetState(EGameFlowState::Countdown);
	CountdownTimer->StartCountdown(CountdownDuration, 1.0f);
}

void UGameRuleComponent::OnChestFound(const int32 FinderPlayerIndex)
{
	if (CurrentState != EGameFlowState::Adventure) return;

	AdventureTimer->PauseTimer(); // freeze the 2-minute clock during the quiz
	AnsweredThisQuiz.Empty();
	ResetChestTracker();
	PendingAnswers.Empty();

	OpenedChestTracker[FinderPlayerIndex] = true;
	QuizDataDefinition->GetRandomQuiz(ActiveQuiz);
	SetState(EGameFlowState::Quiz);
	UGameEventLibrary::NotifyQuizLoaded(GetOwner(), ActiveQuiz);
	QuizTimer->StartCountdown(QuizDuration, 1.0f);
}

void UGameRuleComponent::SubmitQuizAnswer(const int32 PlayerIndex, const EQuizAnswer Answer)
{
	if (CurrentState != EGameFlowState::Quiz || !PlayerIndex) return;
	if (AnsweredThisQuiz.Contains(PlayerIndex)) return;

	AnsweredThisQuiz.Add(PlayerIndex);
	PendingAnswers.Add(PlayerIndex, Answer);

	if (AnsweredThisQuiz.Num() >= Players.Num())
	{
		FinishQuiz();
	}
}

void UGameRuleComponent::AddGameScore(const int32 PlayerIndex, const int32 Points)
{
	GetGameDataDefinition()->AddPlayerScore(PlayerIndex, Points, OpenedChestTracker[PlayerIndex]);
	const int32 Score = GetGameDataDefinition()->GetPlayerScore(PlayerIndex);
	FIA_LOG_F("AddScore: Player %i score updated", Score);
	UGameEventLibrary::NotifyScoreChanged(GetOwner(), PlayerIndex, Score);

	if (Score >= WinScore)
	{
		EndGame(PlayerIndex);
	}
}

void UGameRuleComponent::ResetChestTracker()
{
	for (const int32 PlayerIndex : Players)
	{
		OpenedChestTracker[PlayerIndex] = false;
	}
}

void UGameRuleComponent::RestartGame() const
{
	if (const UWorld* World = GetWorld())
	{
		UGameplayStatics::OpenLevel(World, FName(*World->GetName()));
	}
}

void UGameRuleComponent::ReturnToMainMenu(const FString& MainMenuMapName) const
{
	if (const UWorld* World = GetWorld())
	{
		UGameplayStatics::OpenLevel(World, FName(*MainMenuMapName));
	}
}

void UGameRuleComponent::InitializePlayers(const TArray<int32>& InPlayers)
{
	Players = InPlayers;
	if (GetGameDataDefinition() == nullptr)
	{
		FIA_ERROR_F("GameRuleComponent::InitializePlayers: GameDataDefinition is nullptr");
		return;
	}
	GameDataDefinition->Initialize();
	for (const int32 PlayerIndex : Players)
	{
		GameDataDefinition->SetPlayerName(PlayerIndex, FName("Player %i", PlayerIndex + 1));
		GameDataDefinition->AddPlayerScore(PlayerIndex, 0, false);
		GameDataDefinition->AddChestOpened(PlayerIndex, 0);
		GameDataDefinition->AddQuizMissed(PlayerIndex, 0);
		UGameEventLibrary::NotifyScoreChanged(GetOwner(), PlayerIndex, 0);
	}
}

void UGameRuleComponent::SetState(const EGameFlowState NewState)
{
	CurrentState = NewState;
	UGameEventLibrary::NotifyGameStateChanged(GetOwner(), NewState);
}

void UGameRuleComponent::EnterAdventure()
{
	SetState(EGameFlowState::Adventure);

	// Enable input for every registered local player
	for (const int32 PlayerIndex : Players)
	{
		if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), PlayerIndex))
		{
			PC->SetIgnoreMoveInput(false);
			PC->SetIgnoreLookInput(false);
		}
	}
	
	// Fresh 2-minute clock only when coming from Countdown; resumes automatically
	// if already running (see OnChestFound, which pauses rather than stops).
	if (!AdventureTimer->IsTimerActive() && AdventureTimer->GetTimeRemaining() <= 0.f)
	{
		AdventureTimer->StartCountdown(AdventureDuration, 1.0f);
	}
	else
	{
		AdventureTimer->ResumeTimer();
	}
}

void UGameRuleComponent::FinishQuiz()
{
	QuizTimer->StopTimer();

	TArray<EQuizAnswer> Results;
	Results.Reserve(PendingAnswers.Num());
	for (const auto& Pair : PendingAnswers)
	{
		// Quiz Check Logic
		if (ActiveQuiz.CorrectAnswer == Pair.Value)
		{
			AddGameScore(Pair.Key, 1);
			UGameEventLibrary::NotifyPlayerAnswered(GetOwner(), Pair.Key);
		}
		else
		{
			AddGameScore(Pair.Key, 0);
			UGameEventLibrary::NotifyPlayerMissed(GetOwner(), Pair.Key);
		}
		Results[Pair.Key] = Pair.Value;
	}
	UGameEventLibrary::NotifyQuizResultsBroadcast(GetOwner(), Results);

	EnterAdventure(); // resumes the paused adventure timer
}

void UGameRuleComponent::EndGame(const int32 Winner)
{
	AdventureTimer->StopTimer();
	QuizTimer->StopTimer();

	SetState(EGameFlowState::EndGame);
	UGameEventLibrary::NotifyGameResultBroadcast(GetOwner(),
		GetGameDataDefinition()->GetAllPlayerScores(Players.Num()));
	UGameEventLibrary::NotifyGameEnded(GetOwner(), Winner);
}

void UGameRuleComponent::HandleCountdownExpired(ETimerType InTimerType)
{
	EnterAdventure();
}

void UGameRuleComponent::HandleAdventureExpired(ETimerType InTimerType)
{
	// Time ran out before anyone hit 20 points — end game with whoever has the highest score
	const FPlayerData BestPlayer = GetGameDataDefinition()->HandleBestScore(Players.Num());
	//TODO: Implement Result Handler Here
	EndGame(BestPlayer.PlayerIndex);
}

void UGameRuleComponent::HandleQuizExpired(ETimerType InTimerType)
{
	// Fill in blanks for anyone who didn't answer in time
	for (int32 PC : Players)
	{
		if (!AnsweredThisQuiz.Contains(PC))
		{
			PendingAnswers.Add(PC, EQuizAnswer::None);
			AnsweredThisQuiz.Add(PC);
		}
	}
	FinishQuiz();
}


// Called every frame
void UGameRuleComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

