

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SessionListSingleRow.generated.h"

class UTextBlock;
class UMainMenu;
class UButton;

UCLASS()
class PUZZLEPLATFORMS_API USessionListSingleRow : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ServerName;

	void Setup(UMainMenu* MainMenu, uint32 index);

protected:

	virtual bool Initialize() override;

private:

	UFUNCTION()
	void ServerSelectButtonClicked();

	UPROPERTY(meta = (BindWidget))
	UButton* ServerSelectButton;

	UMainMenu* Parent;
	uint32 selfIndex;
};
