//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SelectableInterface.h"
#include "TopDownBasePawn.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class UFloatingPawnMovement;
class UStaticMeshComponent;

/**
 *
 */
UCLASS()
class ATopDownBasePawn : public APawn, public ISelectableInterface
{
	GENERATED_BODY()
public:
	ATopDownBasePawn();

	virtual void Tick(float DeltaTime) override;

	virtual void Select_Implementation() override;
	virtual void Deselect_Implementation() override;
	virtual void ToggleSelection_Implementation(const bool bIsSelected) override;
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TopDownUtils|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TopDownUtils|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TopDownUtils|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFloatingPawnMovement> FloatingPawnMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TopDownUtils|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> SelectedIndicator;
};