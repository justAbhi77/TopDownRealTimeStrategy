//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TopDownPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

/**
 *
 */
UCLASS()
class TOPDOWNUTILITIES_API ATopDownPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ATopDownPlayerController();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TopDownUtils|Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
protected:
	virtual void SetupInputComponent() override;

	void Select(const FInputActionValue& Value);
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TopDownUtils|Input|Select", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> SelectAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TopDownUtils|Input|Select", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;

	UPROPERTY()
	TObjectPtr<AActor> LastActor;
};
