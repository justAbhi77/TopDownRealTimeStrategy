//


#include "TopDownBuildingBase.h"
#include "Components/BoxComponent.h"


ATopDownBuildingBase::ATopDownBuildingBase()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	SetRootComponent(ToRawPtr(BoxComponent));

	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	BuildingMesh->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	BuildingMesh->SetupAttachment(GetRootComponent());

	SelectedIndicator = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SelectedIndicator"));
	SelectedIndicator->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	SelectedIndicator->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SelectedIndicator->SetupAttachment(GetRootComponent());
	SelectedIndicator->SetHiddenInGame(true);
}

void ATopDownBuildingBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATopDownBuildingBase::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATopDownBuildingBase::Select_Implementation()
{
	if(IsValid(SelectedIndicator))
		SelectedIndicator->SetHiddenInGame(false);
}

void ATopDownBuildingBase::Deselect_Implementation()
{
	if(IsValid(SelectedIndicator))
		SelectedIndicator->SetHiddenInGame(true);
}

void ATopDownBuildingBase::ToggleSelection_Implementation(const bool bIsSelected)
{
	if(bIsSelected)
		Select();
	else
		Deselect();
}

