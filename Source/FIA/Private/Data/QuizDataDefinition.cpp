// Chukwuyenum Opone Copyright 2026


#include "Data/QuizDataDefinition.h"

void UQuizDataDefinition::InitializeQuizData()
{
	QuizArray.Empty();

	if (!QuizBank)
	{
		return;
	}

	static const FString Context(TEXT("QuizData"));

	TArray<FQuizData*> Rows;
	QuizBank->GetAllRows(Context, Rows);

	for (const FQuizData* Row : Rows)
	{
		if (Row)
		{
			QuizArray.Add(*Row);
		}
	}
}

bool UQuizDataDefinition::GetRandomQuiz(FQuizData& OutQuiz)
{
	if (QuizArray.IsEmpty())
	{
		return false;
	}

	const int32 Index = FMath::RandRange(0, QuizArray.Num() - 1);

	OutQuiz = QuizArray[Index];

	QuizArray.RemoveAtSwap(Index);

	return true;
}
