

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FiaPlayerController.generated.h"

enum class EQuizAnswer : uint8;
/**
 * 
 */
UCLASS()
class FIA_API AFiaPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(Server, Reliable)
	void SubmitAnswer(EQuizAnswer Answer);
};
