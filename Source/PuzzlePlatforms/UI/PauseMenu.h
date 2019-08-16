

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "PauseMenu.generated.h"

class UButton;

UCLASS()
class PUZZLEPLATFORMS_API UPauseMenu : public UMenuWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void ShowPauseMenu();

	UFUNCTION(BlueprintCallable)
	void HidePauseMenu();

protected:

	virtual bool Initialize() override;

private:
	
	UFUNCTION()
	void ResumeButtonClicked();
	
	UFUNCTION()
	void QuitToMenuButtonClicked();

	UPROPERTY(meta = (BindWidget))
	UButton* ResumeButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitToMenuButton;
};
