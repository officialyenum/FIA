#include "System/QuizManagerSubsystem.h"

#include "Game/FiaGameState.h"
#include "Player/FiaPlayerState.h"

void UQuizManagerSubsystem::Deinitialize()
{
	if (GetWorld())
	{
		GetWorld()
			->GetTimerManager()
			.ClearTimer(
				QuizTimerHandle
			);
	}
	PlayerResults.Empty();
	CurrentQuizData = FQuizData();
	CurrentCorrectAnswer = EQuizAnswer::None;
	ChestFoundBy = nullptr;
	ActiveChest = nullptr;
	
	Super::Deinitialize();
}

bool UQuizManagerSubsystem::StartQuiz(AActor* Chest, AFiaPlayerState* InChestFoundBy, const int32 QuestionID,
	const FQuizData QuizData, const float Duration)
{
	if (!IsServer()) return false;
	if (!Chest) return false;
	
	AFiaGameState* FiaGameState = GetFiaGameState();
	if (!FiaGameState) return false;
	// Already in quiz mode
	if (FiaGameState->FiaGameMode == EFiaGameMode::Quiz) return false;
	// Reset previous state
	PlayerResults.Empty();
	ActiveChest = Chest;
	ChestFoundBy = InChestFoundBy;
	CurrentQuizData = QuizData;
	CurrentCorrectAnswer = QuizData.CorrectAnswer;
	
	// Get all players currently
	// participating in this quiz
	BuildPlayerList();
	
	

	// Start replicated quiz state
	FiaGameState->StartQuiz(
		QuestionID,
		Duration
	);
	
	// Start server timer
	GetWorld()
		->GetTimerManager()
		.SetTimer(
			QuizTimerHandle,
			this,
			&UQuizManagerSubsystem::
				HandleQuizTimerExpired,
			Duration,
			false
		);
	
	// Notify server-side listeners
	OnQuizStarted.Broadcast();
	return true;
}

void UQuizManagerSubsystem::SubmitAnswer(AFiaPlayerState* PlayerState, EQuizAnswer Answer)
{
	if (!IsServer()) return;
	if (!PlayerState) return;
	if (!IsQuizActive()) return;
	if (!IsValidPlayer(PlayerState)) return;
	
	FQuizPlayerResult* Result = PlayerResults.Find(PlayerState);
	if (!Result) return;
	// Player Already answered
	if (Result->bAnswered) return;
		
	// ============================
	// RECORD ANSWER
	// ============================

	Result->bAnswered = true;
	Result->Answer = Answer;
	Result->bCorrect = Answer == CurrentCorrectAnswer;
	
	// ============================
	// SCORE
	// ============================

	const float PointsAdded = Result->bOpenedChest
			? (Result->bCorrect ? 3 : 1)
			: (Result->bCorrect ? 1 : 0);
	
	PlayerState->AddScore(
		PointsAdded
	);
	PlayerState->RecordQuizAnswered();
	
	// ============================
	// EVENTS
	// ============================
	OnPlayerAnswered.Broadcast(
		PlayerState,
		Answer
	);
	
	OnPlayerScored.Broadcast(
		PlayerState,
		PointsAdded,
		PlayerState
			->GetQuizScoreData()
			.Score
	);

	// ============================
	// CHECK COMPLETION
	// ============================
	CheckEveryoneAnswered();
}

void UQuizManagerSubsystem::FinishQuiz()
{
	if (!IsServer())
	{
		return;
	}

	FinishQuizInternal(
		false
	);
}

bool UQuizManagerSubsystem::IsQuizActive() const
{
	const AFiaGameState* FiaGameState = GetFiaGameState();
	
	if (!FiaGameState) return false;
	
	return FiaGameState->FiaGameMode == EFiaGameMode::Quiz;
}

EFiaGameMode UQuizManagerSubsystem::GetGameMode() const
{
	const AFiaGameState* FiaGameState = GetFiaGameState();
	
	if (!FiaGameState) return EFiaGameMode::Adventure;
	
	return FiaGameState->FiaGameMode;
}

bool UQuizManagerSubsystem::IsServer() const
{
	const UWorld* World = GetWorld();
	if (!World) return false;
	return World->GetNetMode() != NM_Client;
}

AFiaGameState* UQuizManagerSubsystem::GetFiaGameState() const
{
	if (!GetWorld()) return nullptr;
	return GetWorld()->GetGameState<AFiaGameState>();
}

void UQuizManagerSubsystem::BuildPlayerList()
{
	AFiaGameState* FiaGameState = GetFiaGameState();
	if (!FiaGameState) return ;
	for (TObjectPtr<APlayerState> PlayerState : FiaGameState->PlayerArray)
	{
		TObjectPtr<AFiaPlayerState> FiaPlayerState = Cast<AFiaPlayerState>(PlayerState);
		if (!FiaPlayerState) continue ;
		
		FQuizPlayerResult NewPlayerResult;
		if (FiaPlayerState == ChestFoundBy) NewPlayerResult.bOpenedChest = true;
		PlayerResults.Add(FiaPlayerState, NewPlayerResult);
		
	}
}

void UQuizManagerSubsystem::HandleQuizTimerExpired()
{
	if (!IsServer())
	{
		return;
	}

	FinishQuizInternal(
		true
	);
}

void UQuizManagerSubsystem::CheckEveryoneAnswered()
{
	for (const auto& Pair :
		PlayerResults)
	{
		const FQuizPlayerResult&
			Result = Pair.Value;

		if (!Result.bAnswered)
		{
			return;
		}
	}


	// Everybody answered
	FinishQuizInternal(
		false
	);
}

void UQuizManagerSubsystem::FinishQuizInternal(const bool bTimedOut)
{
	if (!IsServer()) return;
	if (!IsQuizActive()) return;
	
	// Stop timer
	GetWorld()->GetTimerManager().ClearTimer(QuizTimerHandle);
	
	// ============================
	// HANDLE MISSED PLAYERS
	// ============================

	if (bTimedOut)
	{
		for (auto& Pair : PlayerResults)
		{
			AFiaPlayerState* PlayerState = Pair.Key;
			const FQuizPlayerResult& Result = Pair.Value;

			if (!PlayerState) continue;
			
			if (!Result.bAnswered) PlayerState->RecordQuizMissed();
		}
	}
	// ============================
	// CHANGE MODE
	// ============================

	if (AFiaGameState* FiaGameState = GetFiaGameState()) FiaGameState->FinishQuiz(bTimedOut);
	
	// ============================
	// EVENT
	// ============================

	OnQuizFinished.Broadcast(bTimedOut);

	// ============================
	// CLEANUP
	// ============================

	PlayerResults.Empty();
	ActiveChest = nullptr;
	ChestFoundBy = nullptr;
	CurrentQuizData = FQuizData();
	CurrentCorrectAnswer = EQuizAnswer::None;
}

bool UQuizManagerSubsystem::IsValidPlayer(AFiaPlayerState* PlayerState) const
{
	return PlayerResults.Contains(
		PlayerState
	);
}
