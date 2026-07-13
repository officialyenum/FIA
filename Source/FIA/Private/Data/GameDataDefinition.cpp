// Chukwuyenum Opone Copyright 2026


#include "Data/GameDataDefinition.h"


void UGameDataDefinition::Initialize()
{
	GetGameData().PerPlayerSplitscreenData.SetNum(TotalPlayers);
	for (int i = 0; i < TotalPlayers; ++i)
	{
		GetGameData().PerPlayerSplitscreenData[i].PlayerIndex = i;
		GetGameData().PerPlayerSplitscreenData[i].Score = 0;
		GetGameData().PerPlayerSplitscreenData[i].ChestOpened = 0;
		GetGameData().PerPlayerSplitscreenData[i].QuizAnswered = 0;
		GetGameData().PerPlayerSplitscreenData[i].QuizMissed = 0;
	}
}

void UGameDataDefinition::SetGameSessionID(const FName GameID)
{
	GetGameData().ID = GameID;
}

void UGameDataDefinition::SetPlayerName(const int32 PlayerIndex, const FName PlayerName)
{
	GetGameData().PerPlayerSplitscreenData[PlayerIndex].SetName(PlayerName);
}

void UGameDataDefinition::AddPlayerScore(const int32 PlayerIndex, const int32 Score, const bool bOpenedChest)
{
	const int32 ChestScore = bOpenedChest
		? (Score > 0 ? 2 : 1)
		: 0;
	GetGameData().PerPlayerSplitscreenData[PlayerIndex].AddScore(Score + ChestScore);
}

void UGameDataDefinition::AddChestOpened(const int32 PlayerIndex, const int32 Score)
{
	GetGameData().PerPlayerSplitscreenData[PlayerIndex].AddChestOpened(Score);
}

void UGameDataDefinition::AddQuizAnswered(const int32 PlayerIndex, const int32 Score)
{
	GetGameData().PerPlayerSplitscreenData[PlayerIndex].AddQuizAnswered(Score);
}

void UGameDataDefinition::AddQuizMissed(const int32 PlayerIndex, const int32 Score)
{
	GetGameData().PerPlayerSplitscreenData[PlayerIndex].AddQuizMissed(Score);
}

TSubclassOf<APawn> UGameDataDefinition::GetPlayerClass(const int32 PlayerIndex)
{
	return CharacterClasses[PlayerIndex];
}

int32 UGameDataDefinition::GetPlayerScore(const int32 PlayerIndex)
{
	return GetGameData().PerPlayerSplitscreenData[PlayerIndex].Score;
}

int32 UGameDataDefinition::GetChestOpened(const int32 PlayerIndex)
{
	return GetGameData().PerPlayerSplitscreenData[PlayerIndex].ChestOpened;
}

int32 UGameDataDefinition::GetQuizAnswered(const int32 PlayerIndex)
{
	return GetGameData().PerPlayerSplitscreenData[PlayerIndex].QuizAnswered;
}

int32 UGameDataDefinition::GetQuizMissed(const int32 PlayerIndex)
{
	return GetGameData().PerPlayerSplitscreenData[PlayerIndex].QuizMissed;
}

FPlayerData UGameDataDefinition::HandleBestScore(const int32 InTotalPlayers)
{
	FPlayerData BestData;
	for (int i = 0; i < TotalPlayers - 1; ++i)
	{
		if (GetGameData().PerPlayerSplitscreenData[i].Score > BestData.Score) 
			BestData = GetGameData().PerPlayerSplitscreenData[i];
	}
	return BestData;
}

TArray<FPlayerData> UGameDataDefinition::GetAllPlayerScores(const int32 InTotalPlayers)
{
	return GetGameData().PerPlayerSplitscreenData;
}
