// Chukwuyenum Opone Copyright 2026

#pragma once

#include "CoreMinimal.h"
#include "TimeManagerComponent.h"
#include "Components/ActorComponent.h"
#include "Data/GameDataDefinition.h"
#include "Data/QuizDataDefinition.h"
#include "GameRuleComponent.generated.h"


struct FQuizData;
class UQuizDataDefinition;
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
	
	UFUNCTION(BlueprintCallable, Category = "Rules")
	void Initialize(UTimeManagerComponent* InCountdownTimer,
					 UTimeManagerComponent* InAdventureTimer,
					 UTimeManagerComponent* InQuizTimer);

	UPROPERTY(EditAnywhere, Category = "Rules")
	float CountdownDuration = 3.f;

	UPROPERTY(EditAnywhere, Category = "Rules")
	float AdventureDuration = 120.f;

	UPROPERTY(EditAnywhere, Category = "Rules")
	float QuizDuration = 15.f;

	UPROPERTY(EditAnywhere, Category = "Rules")
	int32 WinScore = 20;

	UPROPERTY(EditAnywhere, Category = "Rules")
	EGameFlowState CurrentState = EGameFlowState::CharacterSelect;
	
	virtual void BeginPlay() override;

	// --- Flow control, call these from GameSetupComponent / gameplay events ---
	UFUNCTION(BlueprintCallable, Category = "Rules")
	void StartCountdown();

	UFUNCTION(BlueprintCallable, Category = "Rules")
	void OnChestFound(const int32 FinderPlayerIndex);

	UFUNCTION(BlueprintCallable, Category = "Rules")
	void SubmitQuizAnswer(const int32 PlayerIndex, const EQuizAnswer Answer);

	UFUNCTION(BlueprintCallable, Category = "Rules")
	void AddGameScore(const int32 PlayerIndex, const int32 Points);
	
	UFUNCTION(BlueprintCallable, Category = "Rules")
	void ResetChestTracker();

	UFUNCTION(BlueprintCallable, Category = "Rules")
	void RestartGame() const;

	UFUNCTION(BlueprintCallable, Category = "Rules")
	void ReturnToMainMenu(const FString& MainMenuMapName) const;

	UFUNCTION(BlueprintCallable, Category = "Rules")
	void SetState(EGameFlowState NewState);
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

	bool bInitialized = false;
	UPROPERTY() TArray<int32> Players;
	TSet<int32> AnsweredThisQuiz;
	TArray<bool> OpenedChestTracker;
	TArray<EQuizAnswer> PendingAnswers;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game|Data", meta = (AllowPrivateAccess, true))
	UGameDataDefinition* GameDataDefinition;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game|Data", meta = (AllowPrivateAccess, true))
	UQuizDataDefinition* QuizDataDefinition;
	
	FQuizData ActiveQuiz;

	void EnterAdventure();
	void FinishQuiz();
	void EndGame(int32 Winner);

	UFUNCTION() void HandleCountdownExpired(ETimerType InTimerType = ETimerType::Countdown);
	UFUNCTION() void HandleAdventureExpired(ETimerType InTimerType = ETimerType::Adventure);
	UFUNCTION() void HandleQuizExpired(ETimerType InTimerType = ETimerType::Quiz);
	
public:
	FORCEINLINE UGameDataDefinition* GetGameDataDefinition() const { return GameDataDefinition; }
	FORCEINLINE UQuizDataDefinition* GetQuizDataDefinition() const { return QuizDataDefinition; }
};
