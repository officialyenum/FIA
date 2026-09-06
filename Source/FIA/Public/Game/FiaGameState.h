

#pragma once

#include "CoreMinimal.h"
#include "FiaGameMode.h"
#include "GameFramework/GameStateBase.h"
#include "FiaGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnFiaGameModeChanged,
	EFiaGameMode,
	NewMode
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(
	FOnQuizStarted
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnQuizFinished,
	bool,
	bTimedOut
);
/**
 * 
 */
UCLASS()
class FIA_API AFiaGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	AFiaGameState();
	virtual void GetLifetimeReplicatedProps(
		TArray<FLifetimeProperty>& OutLifetimeProps
	) const override;


	UPROPERTY(ReplicatedUsing = OnRep_FiaGameMode, BlueprintReadOnly, Category = "Game")
	EFiaGameMode FiaGameMode = EFiaGameMode::Adventure;
	UFUNCTION()
	void OnRep_FiaGameMode() const;
	
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Quiz")
	float QuizEndServerTime = 0.0f;
	
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Quiz")
	int32 QuizQuestionID = INDEX_NONE;
	
	
	UPROPERTY(BlueprintAssignable)
	FOnFiaGameModeChanged OnFiaGameModeChanged;

	UPROPERTY(BlueprintAssignable)
	FOnQuizStarted OnQuizStarted;

	UPROPERTY(BlueprintAssignable)
	FOnQuizFinished OnQuizFinished;
	
	void SetQuizMode(EFiaGameMode NewMode);
	void StartQuiz(int32 QuestionID, float QuizDuration);
	void FinishQuiz(bool bTimedOut);

private:
	bool bLastFinishTimedOut = false;
};
