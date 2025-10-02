//

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SelectableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USelectableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class TOPDOWNUTILITIES_API ISelectableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Select();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Deselect();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ToggleSelection(const bool bIsSelected);
};
