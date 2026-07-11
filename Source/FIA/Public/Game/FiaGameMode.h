// Chukwuyenum Opone Copyright 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FiaGameMode.generated.h"

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
private:
	// Leave at default as game mode will start from defaults
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game|Data", meta = (AllowPrivateAccess = "true"))
	UGameDataDefinition* GameDataDefinition;
	
public:
	UFUNCTION(BlueprintCallable, Category = "Game|Data")
	FORCEINLINE UGameDataDefinition* GetGameDataDefinition() const { return GameDataDefinition; }
};
