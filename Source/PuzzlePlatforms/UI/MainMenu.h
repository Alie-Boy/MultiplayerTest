#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "MainMenu.generated.h"

class UButton;
class IMenuInterface;
class UWidgetSwitcher;
class UEditableText;
class UScrollBox;
class USessionListSingleRow;

UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()
	
public:

	UMainMenu(const FObjectInitializer& ObjectInitializer);

	void SetServerList(TArray<FString> ServerNames);

protected:

	virtual bool Initialize() override;

private:

	UFUNCTION()
	void HostServerButtonClick();

	UFUNCTION()
	void JoinMenuButtonClick();

	UFUNCTION()
	void BackToMainButtonClick();

	UFUNCTION()
	void JoinServerButtonClick();

	UFUNCTION()
	void QuitToOSButtonClick();

	UPROPERTY(meta = (BindWidget))
	UButton* HostServerButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* JoinMenuButton;

	UPROPERTY(meta = (BindWidget))
	UButton* BackToMainButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinServerButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitToOSButton;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* IPAddressScrollBox;

	//UPROPERTY(meta = (BindWidget))
	//UEditableText* IPAddressInput;

	TSubclassOf<USessionListSingleRow> ServerRowClass;

};
