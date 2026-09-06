

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Data//QuizDataDefinition.h"
#include "QuizManagerSubsystem.generated.h"

class AFiaPlayerState;
class AFiaGameState;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(
	FQuizSubsystemQuizStarted
);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FQuizSubsystemQuizFinished,
	bool,
	bTimedOut
);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FQuizSubsystemPlayerAnswered,
	AFiaPlayerState*,
	PlayerState,
	EQuizAnswer,
	Answer
);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(
	FQuizSubsystemPlayerScored,
	AFiaPlayerState*,
	PlayerState,
	int32,
	PointsAdded,
	int32,
	NewScore
);
/**
 * 
 */
UCLASS()
class FIA_API UQuizManagerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Deinitialize() override;
	
	// =============================
	// QUIZ
	// =============================
	UFUNCTION(BlueprintCallable, Category = "Quiz")
	bool StartQuiz(AActor* Chest, AFiaPlayerState* InChestFoundBy, const int32 QuestionID, const FQuizData QuizData, const float Duration);
	
	UFUNCTION(BlueprintCallable,Category = "Quiz")
	void SubmitAnswer(AFiaPlayerState* PlayerState,EQuizAnswer Answer);
	
	UFUNCTION(BlueprintCallable,Category = "Quiz")
	void FinishQuiz();
	UFUNCTION(BlueprintPure,Category = "Quiz")
	bool IsQuizActive() const;


	UFUNCTION(BlueprintPure,Category = "Quiz")
	EFiaGameMode GetGameMode() const;
	
	
	// =============================
	// EVENTS
	// =============================

	UPROPERTY(BlueprintAssignable,Category = "Quiz|Events")
	FQuizSubsystemQuizStarted OnQuizStarted;
	UPROPERTY(BlueprintAssignable,Category = "Quiz|Events")
	FQuizSubsystemQuizFinished OnQuizFinished;
	UPROPERTY(BlueprintAssignable,Category = "Quiz|Events")
	FQuizSubsystemPlayerAnswered OnPlayerAnswered;
	UPROPERTY(BlueprintAssignable,Category = "Quiz|Events")
	FQuizSubsystemPlayerScored OnPlayerScored;
private:
	// =============================
	// STATE
	// =============================
	UPROPERTY()
	TObjectPtr<AActor> ActiveChest;
	UPROPERTY()
	TObjectPtr<AFiaPlayerState> ChestFoundBy;
	UPROPERTY()
	FQuizData CurrentQuizData;
	UPROPERTY()
	EQuizAnswer CurrentCorrectAnswer = EQuizAnswer::None;
	
	UPROPERTY()
	TMap<TObjectPtr<AFiaPlayerState>, FQuizPlayerResult> PlayerResults;
	FTimerHandle QuizTimerHandle;
	
	// =============================
	// INTERNAL
	// =============================

	bool IsServer() const;

	AFiaGameState* GetFiaGameState() const;
	void BuildPlayerList();

	void HandleQuizTimerExpired();
	void CheckEveryoneAnswered();

	void FinishQuizInternal(const bool bTimedOut);
	bool IsValidPlayer(AFiaPlayerState* PlayerState) const;
};
