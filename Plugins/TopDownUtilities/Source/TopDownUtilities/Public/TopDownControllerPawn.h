//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TopDownControllerPawn.generated.h"

class UCapsuleComponent;
class UCameraComponent;
class USpringArmComponent;
class UInputAction;
class UFloatingPawnMovement;
struct FInputActionValue;

/**
 *
 */
UCLASS()
class ATopDownControllerPawn : public APawn
{
	GENERATED_BODY()

public:
	ATopDownControllerPawn();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);

	void Zoom(const FInputActionValue& Value);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TopDownUtils|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TopDownUtils|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TopDownUtils|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TopDownUtils|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFloatingPawnMovement> FloatingPawnMovement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TopDownUtils|Input|Move", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TopDownUtils|Input|Zoom", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ZoomAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TopDownUtils|Input|Zoom", meta = (AllowPrivateAccess = "true"))
	float ZoomInterp = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TopDownUtils|Input|Zoom", meta = (AllowPrivateAccess = "true"))
	float ZoomMultiplier = 20.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TopDownUtils|Input|Zoom", meta = (AllowPrivateAccess = "true"))
	float ZoomMin = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TopDownUtils|Input|Zoom", meta = (AllowPrivateAccess = "true"))
	float ZoomMax = 2500.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TopDownUtils|Input|Zoom", meta = (AllowPrivateAccess = "true"))
	float ZoomDesired;
};
