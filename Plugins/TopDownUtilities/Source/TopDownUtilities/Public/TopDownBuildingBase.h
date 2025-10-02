//

#pragma once

#include "CoreMinimal.h"
#include "SelectableInterface.h"
#include "GameFramework/Actor.h"
#include "TopDownBuildingBase.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

/**
 *
 */
UCLASS()
class TOPDOWNUTILITIES_API ATopDownBuildingBase : public AActor, public ISelectableInterface
{
	GENERATED_BODY()
public:
	ATopDownBuildingBase();

	virtual void Tick(float DeltaTime) override;

	virtual void Select_Implementation() override;
	virtual void Deselect_Implementation() override;
	virtual void ToggleSelection_Implementation(const bool bIsSelected) override;
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TopDownUtils|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TopDownUtils|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> BuildingMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TopDownUtils|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> SelectedIndicator;
};