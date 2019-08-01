

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MultiplayerGameInstance.generated.h"

class UUserWidget;

UCLASS()
class PUZZLEPLATFORMS_API UMultiplayerGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UMultiplayerGameInstance(const FObjectInitializer & ObjectInitializer);

	virtual void Init() override;

	UFUNCTION(Exec)
	void Host();
	
	UFUNCTION(Exec)
	void Join(FString address);

private:

	TSubclassOf<UUserWidget> MenuClass;
};
