#include "MultiplayerGameInstance.h"

#include "Engine\Engine.h"

UMultiplayerGameInstance::UMultiplayerGameInstance(const FObjectInitializer & ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("Game Instance constructor called."));
}

void UMultiplayerGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("Game Instance Init called."));
}

void UMultiplayerGameInstance::Host()
{
	UEngine * Engine = GetEngine();
	Engine->AddOnScreenDebugMessage(0, 1.5f, FColor::Green, TEXT("Hosting"));
}

void UMultiplayerGameInstance::Join(FString address)
{
	UEngine * Engine = GetEngine();
	FString string = "Joining " + address;
	Engine->AddOnScreenDebugMessage(0, 1.5f, FColor::Green, string);
}
