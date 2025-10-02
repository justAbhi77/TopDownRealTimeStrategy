//

#include "TopDownPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "TopDownUtilities.h"
#include "EnhancedInputComponent.h"
#include "SelectableInterface.h"

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

	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Completed, this, &ThisClass::Select);
}

void ATopDownPlayerController::Select(const FInputActionValue& Value)
{
	FHitResult HitResult;
	GetHitResultUnderCursor(TraceChannel, false, HitResult);

	if(AActor* HitActor = HitResult.GetActor())
	{
		FTopDownUtilitiesModule::PrintString("Selected Actor: " + HitActor->GetName());
		if(IsValid(LastActor))
		{
			ISelectableInterface::Execute_Deselect(LastActor);
			LastActor = nullptr;
		}

		if(HitActor->Implements<USelectableInterface>())
		{
			ISelectableInterface::Execute_Select(HitActor);
			LastActor = HitActor;
		}
	}
}
