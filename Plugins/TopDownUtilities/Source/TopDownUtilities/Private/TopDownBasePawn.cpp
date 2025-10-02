//

#include "TopDownBasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/StaticMeshComponent.h"

ATopDownBasePawn::ATopDownBasePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CapsuleComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	SetRootComponent(ToRawPtr(CapsuleComponent));

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));
	SkeletalMeshComp->SetupAttachment(GetRootComponent());

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

	SelectedIndicator = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SelectedIndicator"));
	SelectedIndicator->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	SelectedIndicator->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SelectedIndicator->SetHiddenInGame(true);
	SelectedIndicator->SetupAttachment(GetRootComponent());
}

void ATopDownBasePawn::BeginPlay()
{
	Super::BeginPlay();
}

void ATopDownBasePawn::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATopDownBasePawn::Select_Implementation()
{
	if(IsValid(SelectedIndicator))
		SelectedIndicator->SetHiddenInGame(false);
}

void ATopDownBasePawn::Deselect_Implementation()
{
	if(IsValid(SelectedIndicator))
		SelectedIndicator->SetHiddenInGame(true);
}

void ATopDownBasePawn::ToggleSelection_Implementation(const bool bIsSelected)
{
	if(bIsSelected)
		Select();
	else
		Deselect();
}

void ATopDownBasePawn::MoveToLocation_Implementation(const FVector& TargetLocation)
{
	MoveTargetLocation = TargetLocation + FVector(0.f, 0.f, GetDefaultHalfHeight());
	bMoving = true;

	SetActorLocation(MoveTargetLocation);
}
