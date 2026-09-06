#include "Player/FiaPlayerController.h"

#include "Player/FiaPlayerState.h"
#include "System/QuizManagerSubsystem.h"

void AFiaPlayerController::SubmitAnswer_Implementation(EQuizAnswer Answer)
{
	
	AFiaPlayerState* FiaPlayerState = GetPlayerState<AFiaPlayerState>();
	if (!FiaPlayerState) return;
	
	UWorld* World = GetWorld();
	if (!World) return;
	
	UQuizManagerSubsystem* QuizSystem = World->GetSubsystem<UQuizManagerSubsystem>();
	if (!QuizSystem) return;
	
	QuizSystem->SubmitAnswer(FiaPlayerState, Answer);
}
