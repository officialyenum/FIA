// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/QuizDataDefinition.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "QuizManagerLibrary.generated.h"

class UQuizManagerSubsystem;
class AFiaPlayerState;
class UGameDataDefinition;
class AFiaGameMode;
/**
 * 
 */
UCLASS()
class FIA_API UQuizManagerLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		
public:
	UFUNCTION(Blueprintpure, Category = "FIA Game Library|Quiz", meta=(WorldContext="WorldContextObject"))
	static UQuizManagerSubsystem* GetQuizSystem(const UObject* WorldContextObject);
	UFUNCTION(Blueprintpure, Category = "FIA Game Library", meta=(WorldContext="WorldContextObject"))
	static EFiaGameMode GetFiaGameMode(const UObject* WorldContextObject);
	UFUNCTION(BlueprintCallable, Category = "FIA Game Library|Quiz", meta=(WorldContext="WorldContextObject"))
	static void StartQuiz(const UObject* WorldContextObject, AActor* Chest, AFiaPlayerState* InChestFoundBy, const int32 QuestionID, const FQuizData& QuizData, const float Duration);
	UFUNCTION(BlueprintCallable, Category = "FIA Game Library|Quiz", meta=(WorldContext="WorldContextObject"))
	static void SubmitAnswer(const UObject* WorldContextObject, const APawn* Player, const EQuizAnswer Answer);
	
};
