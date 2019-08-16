

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

class IMenuInterface;

UCLASS()
class PUZZLEPLATFORMS_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UMenuWidget(const FObjectInitializer& ObjectInitializer);

	void SetMenuInterface(IMenuInterface* MenuInterface);

	void Setup();

protected:

	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

	IMenuInterface* MenuInterface;
};
