//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SelectableInterface.h"
#include "NavigableInterface.h"
#include "TopDownBasePawn.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class UFloatingPawnMovement;
class UStaticMeshComponent;

/**
 *
 */
UCLASS()
class ATopDownBasePawn : public APawn, public ISelectableInterface, public INavigableInterface
{
	GENERATED_BODY()

public:
	ATopDownBasePawn();

	virtual void Tick(float DeltaTime) override;

	virtual void Select_Implementation() override;
	virtual void Deselect_Implementation() override;
	virtual void ToggleSelection_Implementation(const bool bIsSelected) override;
	virtual void MoveToLocation_Implementation(const FVector& TargetLocation) override;

protected:
	virtual void BeginPlay() override;

	FVector MoveTargetLocation = FVector::ZeroVector;
	bool bMoving = false;

	void Move();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TopDownUtils|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TopDownUtils|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TopDownUtils|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFloatingPawnMovement> FloatingPawnMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TopDownUtils|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> SelectedIndicator;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TopDownUtils|Movement", meta = (AllowPrivateAccess = "true"))
	float AcceptanceRadius = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TopDownUtils|Movement", meta = (AllowPrivateAccess = "true"))
	float RotationInterpSpeed = 3.f;
};