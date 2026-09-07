// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/QuizManagerLibrary.h"

#include "Data/QuizDataDefinition.h"
#include "Kismet/GameplayStatics.h"
#include "Player/FiaPlayerState.h"
#include "System/QuizManagerSubsystem.h"

EFiaGameMode UQuizManagerLibrary::GetFiaGameMode(const UObject* WorldContextObject)
{
	if (!WorldContextObject) return EFiaGameMode::Adventure;
	const UQuizManagerSubsystem* QuizSystem = GetQuizSystem(WorldContextObject);
	if (!QuizSystem) return EFiaGameMode::Adventure;
	return QuizSystem->GetGameMode();
}

UQuizManagerSubsystem* UQuizManagerLibrary::GetQuizSystem(const UObject* WorldContextObject)
{
	if (!WorldContextObject) return nullptr;
	const UWorld* World = WorldContextObject->GetWorld();
	if (!World) return nullptr;
	return World->GetSubsystem<UQuizManagerSubsystem>();
}

void UQuizManagerLibrary::StartQuiz(const UObject* WorldContextObject, AActor* Chest, AFiaPlayerState* InChestFoundBy,
                                    const int32 QuestionID, const FQuizData& QuizData, const float Duration)
{
	if (!WorldContextObject) return;
	UQuizManagerSubsystem* QuizSystem = GetQuizSystem(WorldContextObject);
	if (!QuizSystem) return ;
	QuizSystem->StartQuiz(Chest, InChestFoundBy, QuestionID, QuizData, Duration);
}

void UQuizManagerLibrary::SubmitAnswer(const UObject* WorldContextObject, const APawn* Player,
	const EQuizAnswer Answer)
{
	AFiaPlayerState* PlayerState = Cast<AFiaPlayerState>(Player->GetPlayerState());
	if (!WorldContextObject) return;
	UQuizManagerSubsystem* QuizSystem = GetQuizSystem(WorldContextObject);
	if (!QuizSystem) return ;
	QuizSystem->SubmitAnswer(PlayerState, Answer);
}
