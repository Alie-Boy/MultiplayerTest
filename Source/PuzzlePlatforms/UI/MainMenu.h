#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class UButton;
class IMenuInterface;

UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void SetMenuInterface(IMenuInterface* MenuInterface);

	void Setup();

protected:

	virtual bool Initialize() override;

	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

private:

	UFUNCTION()
	void HostButtonClick();

	UFUNCTION()
	void JoinButtonClick();

	UPROPERTY(meta = (BindWidget))
	UButton* Host;
	
	UPROPERTY(meta = (BindWidget))
	UButton* Join;

	IMenuInterface* MenuInterface;

};
