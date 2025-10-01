// 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TopDownPlayerController.generated.h"

class UInputMappingContext;

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
};
