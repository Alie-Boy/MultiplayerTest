#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class UButton;

UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
private:

	UPROPERTY(meta = (BindWidget))
	UButton* Host;
	
	UPROPERTY(meta = (BindWidget))
	UButton* Join;

};
