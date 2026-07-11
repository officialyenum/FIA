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

	CountdownTimer = InCountdownTimer;
	AdventureTimer = InAdventureTimer;
	QuizTimer = InQuizTimer;

	check(CountdownTimer && AdventureTimer && QuizTimer);

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

void UGameRuleComponent::OnChestFound(int32 FinderPlayer)
{
	if (CurrentState != EGameFlowState::Adventure) return;

	AdventureTimer->PauseTimer(); // freeze the 2-minute clock during the quiz
	AnsweredThisQuiz.Empty();
	PendingAnswers.Empty();

	SetState(EGameFlowState::Quiz);
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
	if (!PlayerIndex || !PlayerScores.Contains(PlayerIndex)) return;

	int32& Score = PlayerScores[PlayerIndex];
	Score += Points;
	FIA_LOG_F("AddScore: Player %i score updated", Score);
	OnScoreChanged.Broadcast(PlayerIndex, Score);
	// UGameEventLibrary::NotifyPlayerScoreUpdate(GetOwner(), PlayerIndex, Score);

	if (Score >= WinScore)
	{
		EndGame(PlayerIndex);
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
	PlayerScores.Empty();
	for (int32 PlayerIndex : Players)
	{
		PlayerScores.Add(PlayerIndex, 0);
		OnScoreChanged.Broadcast(PlayerIndex, 0);
	}
}

void UGameRuleComponent::SetState(const EGameFlowState NewState)
{
	CurrentState = NewState;
	OnGameStateChanged.Broadcast(NewState);
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
		EQuizAnswer Answer = Pair.Value;
		Results.Add(Answer);
	}
	OnQuizResultsBroadcast.Broadcast(Results);
	// UGameEventLibrary::NotifyQuizResultsBroadcast(GetOwner(), Results);
	// Scoring for correct answers is left to quiz-check logic (Blueprint or
	// another component), which should call AddScore() per correct answer.

	EnterAdventure(); // resumes the paused adventure timer
}

void UGameRuleComponent::EndGame(int32 Winner)
{
	AdventureTimer->StopTimer();
	QuizTimer->StopTimer();

	SetState(EGameFlowState::EndGame);
	OnGameEnded.Broadcast(Winner);
	// UGameEventLibrary::NotifyGameEnded(GetOwner(), Winner);
}

void UGameRuleComponent::HandleCountdownExpired(ETimerType InTimerType)
{
	EnterAdventure();
}

void UGameRuleComponent::HandleAdventureExpired(ETimerType InTimerType)
{
	// Time ran out before anyone hit 20 points — end game with whoever has the highest score
	int32 Winner = -1;
	int32 BestScore = -1;
	for (const auto& Pair : PlayerScores)
	{
		if (Pair.Value > BestScore)
		{
			BestScore = Pair.Value;
			Winner = Pair.Key;
		}
	}
	EndGame(Winner);
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

