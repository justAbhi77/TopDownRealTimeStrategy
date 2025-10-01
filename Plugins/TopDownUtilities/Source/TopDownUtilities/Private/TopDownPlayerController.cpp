//

#include "TopDownPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "TopDownUtilities.h"

ATopDownPlayerController::ATopDownPlayerController()
{
	bShowMouseCursor = true;
}

void ATopDownPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(!DefaultMappingContext) return;

	if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
		FTopDownUtilitiesModule::PrintString("Added DefaultMappingContext to PlayerController");
	}
}
