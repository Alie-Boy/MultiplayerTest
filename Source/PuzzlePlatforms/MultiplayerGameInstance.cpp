#include "MultiplayerGameInstance.h"

#include "Engine\Engine.h"
#include "Classes\GameFramework\PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint\UserWidget.h"
#include "OnlineSubsystem.h"

#include "UI\MainMenu.h"
#include "UI\PauseMenu.h"
#include "PlatformTrigger.h"

UMultiplayerGameInstance::UMultiplayerGameInstance(const FObjectInitializer & ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> MenuClassBP(TEXT("/Game/UI/MenuSystem/WBP_MainMenu"));
	if (!ensure(MenuClassBP.Class != nullptr)) return;
	static ConstructorHelpers::FClassFinder<UUserWidget> PauseMenuClassBP(TEXT("/Game/UI/MenuSystem/WBP_PauseMenu"));
	if (!ensure(PauseMenuClassBP.Class != nullptr)) return;
	/*UE_LOG(LogTemp, Warning, TEXT("Class found: %s"), *MenuClassBP.Class->GetName());*/
	MenuClass = MenuClassBP.Class;
	PauseMenuClass = PauseMenuClassBP.Class;
}

void UMultiplayerGameInstance::Init()
{
	Super::Init();
	IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
	if (OSS == nullptr) return;
	UE_LOG(LogTemp, Warning, TEXT("OSS pointer : %s"), *OSS->GetSubsystemName().ToString());
	UE_LOG(LogTemp, Warning, TEXT("OSS service : %s"), *OSS->GetOnlineServiceName().ToString());
	if (OSS->GetSessionInterface().IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Found OSS session."));
	}
}

void UMultiplayerGameInstance::Host()
{
	HostServer();
}

void UMultiplayerGameInstance::Join(FString address)
{
	JoinServer(address);
}

void UMultiplayerGameInstance::LoadMenu()
{
	if (!ensure(MenuClass != nullptr)) return;
	UMainMenu* Menu = CreateWidget<UMainMenu>(this, MenuClass);
	Menu->Setup();

	Menu->SetMenuInterface(this);
}

void UMultiplayerGameInstance::LoadPauseMenu()
{
	if (!ensure(PauseMenuClass != nullptr)) return;
	UPauseMenu* PauseMenu = CreateWidget<UPauseMenu>(this, PauseMenuClass);
	PauseMenu->ShowPauseMenu();
}

void UMultiplayerGameInstance::HidePauseMenu()
{
	if (!ensure(PauseMenuClass != nullptr)) return;
	UPauseMenu* PauseMenu = CreateWidget<UPauseMenu>(this, PauseMenuClass);
	PauseMenu->HidePauseMenu();
}

void UMultiplayerGameInstance::HostServer()
{
	UEngine * Engine = GetEngine();
	Engine->AddOnScreenDebugMessage(0, 1.5f, FColor::Green, TEXT("Hosting"));

	UWorld* world = GetWorld();
	if (!ensure(world != nullptr)) return;

	world->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UMultiplayerGameInstance::JoinServer(FString address)
{
	UEngine * Engine = GetEngine();
	FString string = "Joining " + address;
	Engine->AddOnScreenDebugMessage(0, 1.5f, FColor::Green, string);

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->ClientTravel(address, ETravelType::TRAVEL_Absolute);
}
