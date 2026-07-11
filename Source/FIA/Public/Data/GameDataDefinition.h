// Chukwuyenum Opone Copyright 2026

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameDataDefinition.generated.h"

UENUM(BlueprintType)
enum class EGameFlowState : uint8
{
	CharacterSelect,
	Countdown,
	Adventure,
	Quiz,
	EndGame
};

USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_BODY()

public:
	FPlayerData()
		: PlayerName(FName("Player 1"))
		  , Score(0)
		  , ChestOpened(0)
		  , QuizAnswered(0)
		  , QuizMissed(0)
	{
	}

	// Player Name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data")
	FName PlayerName;

	// Player Score
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data")
	int32 Score;
	// Player Chest Opened
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data")
	int32 ChestOpened;
	// Player Quiz Answered
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data")
	int32 QuizAnswered;
	// Player Quiz Missed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data")
	int32 QuizMissed;
	
	void SetName(const FName InName) { PlayerName = InName; };
	void AddScore(const int32 ScoreToAdd) { Score += ScoreToAdd; };
	void AddChestOpened(const int32 ChestOpenedToAdd) { ChestOpened += ChestOpenedToAdd; };
	void AddQuizAnswered(const int32 QuizAnsweredToAdd) { QuizAnswered += QuizAnsweredToAdd; };
	void AddQuizMissed(const int32 QuizMissedToAdd) { QuizMissed += QuizMissedToAdd; };
};

USTRUCT(BlueprintType)
struct FGameData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FGameData() {}

	// Game Session ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Data")
	FName ID;
	
	// Player One
	FPlayerData PlayerOne;
	// Player Two
	FPlayerData PlayerTwo;
};
/**
 * 
 */
UCLASS()
class FIA_API UGameDataDefinition : public UDataAsset
{
	GENERATED_BODY()
	
public:
	FGameData& GetGameData() { return GameData; }
	
	UFUNCTION(BlueprintCallable)
	void Reset();
	UFUNCTION(BlueprintCallable)
	void SetGameSessionID(const FName GameID);
	UFUNCTION(BlueprintCallable)
	void SetPlayerName(const int32 PlayerIndex, const FName PlayerName);
	UFUNCTION(BlueprintCallable)
	void AddPlayerScore(const int32 PlayerIndex, const int32 Score);
	UFUNCTION(BlueprintCallable)
	void AddChestOpened(const int32 PlayerIndex, const int32 Score);
	UFUNCTION(BlueprintCallable)
	void AddQuizAnswered(const int32 PlayerIndex, const int32 Score);
	UFUNCTION(BlueprintCallable)
	void AddQuizMissed(const int32 PlayerIndex, const int32 Score);
	UFUNCTION(BlueprintCallable)
	int32 GetPlayerScore(const int32 PlayerIndex);
	UFUNCTION(BlueprintCallable)
	int32 GetChestOpened(const int32 PlayerIndex);
	UFUNCTION(BlueprintCallable)
	int32 GetQuizAnswered(const int32 PlayerIndex);
	UFUNCTION(BlueprintCallable)
	int32 GetQuizMissed(const int32 PlayerIndex);
private:
	FGameData GameData;
};
