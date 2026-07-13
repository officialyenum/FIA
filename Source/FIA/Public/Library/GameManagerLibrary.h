// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GameRuleComponent.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameManagerLibrary.generated.h"

class UGameDataDefinition;
class AFiaGameMode;
/**
 * 
 */
UCLASS()
class FIA_API UGameManagerLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		
public:
	UFUNCTION(Blueprintpure, Category = "FIA Game Library", meta=(WorldContext="WorldContextObject"))
	static AFiaGameMode* GetFiaGameMode(const UObject* WorldContextObject);
	UFUNCTION(Blueprintpure, Category = "FIA Game Library", meta=(WorldContext="WorldContextObject"))
	static UGameDataDefinition* GetFiaCurrentGameDataDefinition(const UObject* WorldContextObject);
	UFUNCTION(Blueprintpure, Category = "FIA Game Library", meta=(WorldContext="WorldContextObject"))
	static EGameFlowState GetGameFlowState(const UObject* WorldContextObject);
};
