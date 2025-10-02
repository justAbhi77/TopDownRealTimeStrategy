//

#include "TopDownControllerPawn.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraTypes.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "EnhancedInputComponent.h"
#include "TopDownUtilities.h"

ATopDownControllerPawn::ATopDownControllerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	// create components
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SetRootComponent(ToRawPtr(CapsuleComponent));

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	// Attach necessary components
	SpringArmComponent->SetupAttachment(GetRootComponent());
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	CameraComponent->SetProjectionMode(ECameraProjectionMode::Orthographic);

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
}

void ATopDownControllerPawn::BeginPlay()
{
	Super::BeginPlay();

	ZoomDesired = CameraComponent->OrthoWidth;
}

void ATopDownControllerPawn::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(IsValid(Controller) && IsValid(SpringArmComponent))
		CameraComponent->OrthoWidth = FMath::FInterpTo(CameraComponent->OrthoWidth, ZoomDesired, DeltaTime, ZoomInterp);
}

void ATopDownControllerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
		// FTopDownUtilitiesModule::PrintString("Bound to Move action on Player Pawn");

		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ThisClass::Zoom);
	}
}

void ATopDownControllerPawn::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	if(IsValid(Controller))
	{
		const FRotator ControlRotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, ControlRotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(RightDirection, MovementVector.X);
		AddMovementInput(ForwardDirection, MovementVector.Y);
	}
}

void ATopDownControllerPawn::Zoom(const FInputActionValue& Value)
{
	const float ZoomValue = Value.Get<float>();
	if(IsValid(Controller) && IsValid(SpringArmComponent))
	{
		ZoomDesired = ZoomDesired + ZoomValue * ZoomMultiplier;
		ZoomDesired = FMath::Clamp(ZoomDesired, ZoomMin, ZoomMax);
	}
}
