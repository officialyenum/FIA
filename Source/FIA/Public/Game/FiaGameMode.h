// Chukwuyenum Opone Copyright 2026

#pragma once

#include "CoreMinimal.h"
#include "Components/GameRuleComponent.h"
#include "GameFramework/GameModeBase.h"
#include "FiaGameMode.generated.h"

class UTimeManagerComponent;
class UGameRuleComponent;
class UGameSetupComponent;
class UGameDataDefinition;
/**
 * 
 */
UCLASS()
class FIA_API AFiaGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AFiaGameMode();
	
	virtual void PostLogin(APlayerController* NewPlayer) override;
protected:
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UGameSetupComponent* GameSetup;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UGameRuleComponent* GameRule;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UTimeManagerComponent* CountdownTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UTimeManagerComponent* AdventureTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UTimeManagerComponent* QuizTimer;

	UFUNCTION()
	void HandleAllPlayersReady();
	UFUNCTION(BlueprintCallable, Category = "Game|Data")
	void AddGameScore(const int32 PlayerIndex, const int32 Points) const;
	
	// UFUNCTION(BlueprintCallable, Category = "Game|Data")
	// FORCEINLINE UGameDataDefinition* GetGameDataDefinition() const { return GameDataDefinition; }
};
