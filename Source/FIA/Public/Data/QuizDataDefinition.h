// Chukwuyenum Opone Copyright 2026

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "QuizDataDefinition.generated.h"

UENUM(BlueprintType)
enum class EQuizAnswer : uint8
{
	None,
	OptionA,
	OptionB,
	OptionX,
	OptionY
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	FText Question;
	
	// Question Option A
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	FText OptionA;
	
	// Question Option B
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	FText OptionB;
	
	// Question Option X
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	FText OptionX;
	
	// Question Option Y
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	FText OptionY;
	
	// Question CorrectAnswer
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	EQuizAnswer CorrectAnswer;
	
	// Question Hint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	FText Hint;
};
/**
 * 
 */
UCLASS()
class FIA_API UQuizDataDefinition : public UDataAsset
{
	GENERATED_BODY()
};
