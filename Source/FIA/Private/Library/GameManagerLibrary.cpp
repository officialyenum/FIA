// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/GameManagerLibrary.h"

#include "Game/FiaGameMode.h"
#include "Kismet/GameplayStatics.h"

AFiaGameMode* UGameManagerLibrary::GetFiaGameMode(const UObject* WorldContextObject)
{
	if (!WorldContextObject) return nullptr;
	return Cast<AFiaGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
}

UGameDataDefinition* UGameManagerLibrary::GetFiaCurrentGameDataDefinition(const UObject* WorldContextObject)
{
	if (!WorldContextObject) return nullptr;
	if (const AFiaGameMode* Game = GetFiaGameMode(WorldContextObject))
		if (const UGameRuleComponent* Rule = Game->GameRule)
			return Rule->GetGameDataDefinition();
	return nullptr;
}

EGameFlowState UGameManagerLibrary::GetGameFlowState(const UObject* WorldContextObject)
{
	if (!WorldContextObject) return EGameFlowState::CharacterSelect;
	if (const AFiaGameMode* Game = GetFiaGameMode(WorldContextObject))
		if (const UGameRuleComponent* Rule = Game->GameRule)
			return Rule->CurrentState;
	return EGameFlowState::CharacterSelect;
}

void UGameManagerLibrary::SetGameFlowState(const UObject* WorldContextObject, const EGameFlowState NewFlowState)
{
	if (!WorldContextObject) return;
	if (const AFiaGameMode* Game = GetFiaGameMode(WorldContextObject))
		if (UGameRuleComponent* GameRule = Game->GameRule)
			GameRule->SetState(NewFlowState);
}
