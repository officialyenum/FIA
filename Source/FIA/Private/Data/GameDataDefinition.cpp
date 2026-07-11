// Chukwuyenum Opone Copyright 2026


#include "Data/GameDataDefinition.h"


void UGameDataDefinition::Reset()
{
	// Reset Player One
	GetGameData().PlayerOne.Score = 0;
	GetGameData().PlayerOne.ChestOpened = 0;
	GetGameData().PlayerOne.QuizAnswered = 0;
	GetGameData().PlayerOne.QuizMissed = 0;
	
	// Reset Player Two
	GetGameData().PlayerTwo.Score = 0;
	GetGameData().PlayerTwo.ChestOpened = 0;
	GetGameData().PlayerTwo.QuizAnswered = 0;
	GetGameData().PlayerTwo.QuizMissed = 0;
}

void UGameDataDefinition::SetGameSessionID(const FName GameID)
{
	GetGameData().ID = GameID;
}

void UGameDataDefinition::SetPlayerName(const int32 PlayerIndex, const FName PlayerName)
{
	switch (PlayerIndex)
	{
	case 0: GetGameData().PlayerOne.SetName(PlayerName); break;
	case 1: GetGameData().PlayerTwo.SetName(PlayerName); break;
	default: break;
	}
}

void UGameDataDefinition::AddPlayerScore(const int32 PlayerIndex, const int32 Score)
{
	switch (PlayerIndex)
	{
		case 0: GetGameData().PlayerOne.AddScore(Score); break;
		case 1: GetGameData().PlayerTwo.AddScore(Score); break;
		default: break;
	}
}

void UGameDataDefinition::AddChestOpened(const int32 PlayerIndex, const int32 Score)
{
	switch (PlayerIndex)
	{
		case 0: GetGameData().PlayerOne.AddChestOpened(Score); break;
		case 1: GetGameData().PlayerTwo.AddChestOpened(Score); break;
		default: break;
	}
}

void UGameDataDefinition::AddQuizAnswered(const int32 PlayerIndex, const int32 Score)
{
	switch (PlayerIndex)
	{
		case 0: GetGameData().PlayerOne.AddQuizAnswered(Score); break;
		case 1: GetGameData().PlayerTwo.AddQuizAnswered(Score); break;
		default: break;
	}
}

void UGameDataDefinition::AddQuizMissed(const int32 PlayerIndex, const int32 Score)
{
	switch (PlayerIndex)
	{
		case 0: GetGameData().PlayerOne.AddQuizMissed(Score); break;
		case 1: GetGameData().PlayerTwo.AddQuizMissed(Score); break;
		default: break;
	}
}

int32 UGameDataDefinition::GetPlayerScore(const int32 PlayerIndex)
{
	switch (PlayerIndex)
	{
	case 0: return GetGameData().PlayerOne.Score;
	case 1: return GetGameData().PlayerTwo.Score;
	default: return 0;
	}
}

int32 UGameDataDefinition::GetChestOpened(const int32 PlayerIndex)
{
	switch (PlayerIndex)
	{
	case 0: return GetGameData().PlayerOne.ChestOpened;
	case 1: return GetGameData().PlayerTwo.ChestOpened;
	default: return 0;
	}
}

int32 UGameDataDefinition::GetQuizAnswered(const int32 PlayerIndex)
{
	switch (PlayerIndex)
	{
	case 0: return GetGameData().PlayerOne.QuizAnswered;
	case 1: return GetGameData().PlayerTwo.QuizAnswered;
	default: return 0;
	}
}

int32 UGameDataDefinition::GetQuizMissed(const int32 PlayerIndex)
{
	switch (PlayerIndex)
	{
	case 0: return GetGameData().PlayerOne.QuizMissed;
	case 1: return GetGameData().PlayerTwo.QuizMissed;
	default: return 0;
	}
}
