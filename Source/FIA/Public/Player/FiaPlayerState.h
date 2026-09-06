

#pragma once

#include "CoreMinimal.h"
#include "Data/QuizDataDefinition.h"
#include "GameFramework/PlayerState.h"
#include "FiaPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnPlayerScoreDataChanged,
	const FQuizScoreData&, ScoreData
);

/**
 * 
 */
UCLASS()
class FIA_API AFiaPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AFiaPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(ReplicatedUsing = OnRep_ScoreData,BlueprintReadOnly,Category = "Quiz")
	FQuizScoreData ScoreData;
	UFUNCTION()
	void OnRep_ScoreData();
	UFUNCTION(BlueprintPure, Category = "Quiz")
	FQuizScoreData GetQuizScoreData() const;
	
	
	// SERVER ONLY FUNCTIONS

	void AddScore(int32 Amount);
	void RecordChestOpened();
	void RecordQuizAnswered();
	void RecordQuizMissed();
	
	UPROPERTY(BlueprintAssignable, Category = "Quiz")
	FOnPlayerScoreDataChanged OnScoreDataChanged;
	
};
