#include "MultiplayerGameInstance.h"

#include "Engine\Engine.h"
#include "Classes\GameFramework\PlayerController.h"

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

	UWorld* world = GetWorld();
	if (!ensure(world != nullptr)) return;

	world->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UMultiplayerGameInstance::Join(FString address)
{
	UEngine * Engine = GetEngine();
	FString string = "Joining " + address;
	Engine->AddOnScreenDebugMessage(0, 1.5f, FColor::Green, string);

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->ClientTravel(address, ETravelType::TRAVEL_Absolute);
}
