//

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FTopDownUtilitiesModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	static void PrintString(const FString& InString)
	{
		UE_LOG(LogTemp, Log, TEXT("%s"), *InString);

		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, InString);
	}
};
