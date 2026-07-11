// Chukwuyenum Opone Copyright 2026

#pragma once

#include "CoreMinimal.h"
#include "TimeManagerComponent.h"
#include "Components/ActorComponent.h"
#include "Data/GameDataDefinition.h"
#include "GameRuleComponent.generated.h"


enum class EQuizAnswer : uint8;
enum class ETimerType : uint8;
class UTimeManagerComponent;
struct FQuizAnswerResult;
enum class EGameFlowState : uint8;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FIA_API UGameRuleComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UGameRuleComponent();

	UPROPERTY(EditAnywhere, Category = "Rules")
	float CountdownDuration = 3.f;

	UPROPERTY(EditAnywhere, Category = "Rules")
	float AdventureDuration = 120.f;

	UPROPERTY(EditAnywhere, Category = "Rules")
	float QuizDuration = 15.f;

	UPROPERTY(EditAnywhere, Category = "Rules")
	int32 WinScore = 20;

	UPROPERTY(BlueprintReadOnly, Category = "Rules")
	EGameFlowState CurrentState = EGameFlowState::CharacterSelect;
	virtual void BeginPlay() override;

	// --- Flow control, call these from GameSetupComponent / gameplay events ---
	UFUNCTION(BlueprintCallable, Category = "Rules")
	void StartCountdown();

	UFUNCTION(BlueprintCallable, Category = "Rules")
	void OnChestFound(int32 FinderPlayerIndex);

	UFUNCTION(BlueprintCallable, Category = "Rules")
	void SubmitQuizAnswer(int32 PlayerIndex, const EQuizAnswer Answer);

	UFUNCTION(BlueprintCallable, Category = "Rules")
	void AddScore(int32 PlayerIndex, int32 Points);

	UFUNCTION(BlueprintCallable, Category = "Rules")
	void RestartGame() const;

	UFUNCTION(BlueprintCallable, Category = "Rules")
	void ReturnToMainMenu(const FString& MainMenuMapName) const;

	// Register participating players once character select completes
	UFUNCTION(BlueprintCallable, Category = "Rules")
	void InitializePlayers(const TArray<int32>& InPlayers);
	
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
private:
	UPROPERTY() UTimeManagerComponent* CountdownTimer;
	UPROPERTY() UTimeManagerComponent* AdventureTimer;
	UPROPERTY() UTimeManagerComponent* QuizTimer;

	UPROPERTY() TArray<int32> Players;
	TMap<int32, int32> PlayerScores;
	TSet<int32> AnsweredThisQuiz;
	TMap<int32, EQuizAnswer> PendingAnswers;

	void SetState(EGameFlowState NewState);
	void EnterAdventure();
	void FinishQuiz();
	void EndGame(int32 Winner);

	UFUNCTION() void HandleCountdownExpired(ETimerType InTimerType = ETimerType::Countdown);
	UFUNCTION() void HandleAdventureExpired(ETimerType InTimerType = ETimerType::Adventure);
	UFUNCTION() void HandleQuizExpired(ETimerType InTimerType = ETimerType::Quiz);
};
