// Chukwuyenum Opone Copyright 2026

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "QuizDataDefinition.generated.h"

UENUM(BlueprintType)
enum class EFiaGameMode : uint8
{
	Menu UMETA(DisplayName = "Menu"),
	Adventure UMETA(DisplayName = "Adventure"),
	Quiz UMETA(DisplayName = "Quiz")
};

UENUM(BlueprintType)
enum class EQuizAnswer : uint8
{
	None UMETA(DisplayName = "None"),

	A UMETA(DisplayName = "A"),
	B UMETA(DisplayName = "B"),
	X UMETA(DisplayName = "X"),
	Y UMETA(DisplayName = "Y")
};


USTRUCT(BlueprintType)
struct FQuizScoreData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int32 Score = 0;
	UPROPERTY(BlueprintReadOnly)
	int32 ChestOpened = 0;
	UPROPERTY(BlueprintReadOnly)
	int32 QuizAnswered = 0;
	UPROPERTY(BlueprintReadOnly)
	int32 QuizMissed = 0;


	void AddScore(const int32 ScoreToAdd) { Score += ScoreToAdd; }
	void RecordChestOpened() { ++ChestOpened; }
	void RecordQuizAnswered() { ++QuizAnswered; }
	void RecordQuizMissed() { ++QuizMissed; }
};

USTRUCT()
struct FQuizPlayerResult
{
	GENERATED_BODY()
	
	bool bAnswered = false;
	bool bCorrect = false;
	EQuizAnswer Answer = EQuizAnswer::None;
};

USTRUCT(BlueprintType)
struct FQuizData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FQuizData()
		: ID(FName("Q001"))
		  , Question(FText::FromString(""))
		  , OptionA(FText::FromString(""))
		  , OptionB(FText::FromString(""))
		  , OptionX(FText::FromString(""))
		  , OptionY(FText::FromString(""))
		  , CorrectAnswer()
		  , Hint(FText::FromString(""))
	{
	}

	// Question ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quiz Data")
	FName ID;

	// Question Text
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quiz Data")
	FText Question;
	
	// Question Option A
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quiz Data")
	FText OptionA;
	
	// Question Option B
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quiz Data")
	FText OptionB;
	
	// Question Option X
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quiz Data")
	FText OptionX;
	
	// Question Option Y
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quiz Data")
	FText OptionY;
	
	// Question CorrectAnswer
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quiz Data")
	EQuizAnswer CorrectAnswer;
	
	// Question Hint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quiz Data")
	FText Hint;
};
/**
 * 
 */
UCLASS()
class FIA_API UQuizDataDefinition : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Quiz Data")
	TObjectPtr<UDataTable> QuizBank;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Quiz Data")
	TArray<FQuizData> QuizArray;
	
	UFUNCTION(BlueprintCallable)
    void InitializeQuizData();
	
	UFUNCTION(BlueprintCallable)
    bool GetRandomQuiz(FQuizData& OutQuiz);
};
