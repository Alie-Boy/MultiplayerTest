

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UI\MenuInterface.h"
#include "MultiplayerGameInstance.generated.h"

class UUserWidget;

UCLASS()
class PUZZLEPLATFORMS_API UMultiplayerGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:

	UMultiplayerGameInstance(const FObjectInitializer & ObjectInitializer);

	virtual void Init() override;

	virtual void Host() override;

	virtual void Join(FString address) override;

	UFUNCTION(Exec, BlueprintCallable)
	void LoadMenu();

	UFUNCTION(Exec, BlueprintCallable)
	void LoadPauseMenu();

	UFUNCTION(Exec, BlueprintCallable)
	void HidePauseMenu();

	UFUNCTION(Exec)
	void HostServer();
	
	UFUNCTION(Exec)
	void JoinServer(FString address);

private:

	TSubclassOf<UUserWidget> MenuClass;
	TSubclassOf<UUserWidget> PauseMenuClass;
};
