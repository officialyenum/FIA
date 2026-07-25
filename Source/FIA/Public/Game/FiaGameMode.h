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
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
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
	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	TSubclassOf<AActor> StartupClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	TSubclassOf<AActor> RespawnClass;
	
	TArray<FVector> StartupPoints;
	TArray<FVector> RespawnPoints;
	
	UFUNCTION(BlueprintImplementableEvent)
	void HideChestInPool_BP();
	UFUNCTION(BlueprintImplementableEvent)
	void RespawnChest_BP();
	UFUNCTION(BlueprintImplementableEvent)
	void OpenQuizWidget_BP(FQuizData QuizData);
	UFUNCTION(BlueprintImplementableEvent)
	void CloseQuizWidget_BP();

	UFUNCTION()
	void HandleAllPlayersReady();
};
