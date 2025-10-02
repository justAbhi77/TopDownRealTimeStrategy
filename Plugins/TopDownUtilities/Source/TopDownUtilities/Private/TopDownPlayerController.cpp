//

#include "TopDownPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "TopDownUtilities.h"
#include "EnhancedInputComponent.h"
#include "SelectableInterface.h"
#include "Engine/HitResult.h"
#include "UObject/Object.h"
#include "NavigableInterface.h"

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
	{
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Completed, this, &ThisClass::Select);
		EnhancedInputComponent->BindAction(CommandAction, ETriggerEvent::Completed, this, &ThisClass::CommandSelectedActor);
	}
}

void ATopDownPlayerController::Select(const FInputActionValue& Value)
{
	FHitResult HitResult;
	GetHitResultUnderCursor(TraceChannel, false, HitResult);

	if(ThisActor = HitResult.GetActor(); ThisActor)
	{
		FTopDownUtilitiesModule::PrintString("Selected Actor: " + ThisActor->GetName());
		if(IsValid(LastActor))
		{
			ISelectableInterface::Execute_Deselect(LastActor);
			LastActor = nullptr;
		}

		if(ThisActor->Implements<USelectableInterface>())
		{
			ISelectableInterface::Execute_Select(ThisActor);
			LastActor = ThisActor;
		}
	}
}

void ATopDownPlayerController::CommandSelectedActor(const FInputActionValue& Value)
{
	if(IsValid(ThisActor) && ThisActor->Implements<UNavigableInterface>())
	{
		FHitResult HitResult;
		GetHitResultUnderCursor(TraceChannel, false, HitResult);

		if(HitResult.bBlockingHit)
		{
			INavigableInterface::Execute_MoveToLocation(ThisActor, HitResult.Location);
			FTopDownUtilitiesModule::PrintString("Commanded Actor: " + ThisActor->GetName());
		}
	}
	else
	{
		FTopDownUtilitiesModule::PrintString("No Actor Selected to Command");
	}
}
