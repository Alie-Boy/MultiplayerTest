#include "MultiplayerGameInstance.h"

#include "Engine\Engine.h"
#include "Classes\GameFramework\PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint\UserWidget.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "OnlineSessionInterface.h"

#include "UI\MainMenu.h"
#include "UI\PauseMenu.h"
#include "PlatformTrigger.h"

UMultiplayerGameInstance::UMultiplayerGameInstance(const FObjectInitializer & ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> MenuClassBP(TEXT("/Game/UI/MenuSystem/WBP_MainMenu"));
	if (!ensure(MenuClassBP.Class != nullptr)) return;
	static ConstructorHelpers::FClassFinder<UUserWidget> PauseMenuClassBP(TEXT("/Game/UI/MenuSystem/WBP_PauseMenu"));
	if (!ensure(PauseMenuClassBP.Class != nullptr)) return;
	UE_LOG(LogTemp, Warning, TEXT("Class found: %s"), *MenuClassBP.Class->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Class found: %s"), *PauseMenuClassBP.Class->GetName());
	MenuClass = MenuClassBP.Class;
	PauseMenuClass = PauseMenuClassBP.Class;
}

void UMultiplayerGameInstance::Init()
{
	Super::Init();
	IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
	if (OSS == nullptr) return;
	UE_LOG(LogTemp, Warning, TEXT("OSS pointer : %s"), *OSS->GetSubsystemName().ToString());
	SessionInterface = OSS->GetSessionInterface();
	if (SessionInterface.IsValid())
	{
		SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UMultiplayerGameInstance::OnCreateSessionComplete);
		SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UMultiplayerGameInstance::OnCreateSessionComplete);
		SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UMultiplayerGameInstance::OnFindSessionsComplete);

		OnlineSessionSearch = MakeShareable(new FOnlineSessionSearch());

		if (OnlineSessionSearch.IsValid())
		{
			OnlineSessionSearch->bIsLanQuery = true;

			UE_LOG(LogTemp, Warning, TEXT("Starting session search"));
			SessionInterface->FindSessions(0, OnlineSessionSearch.ToSharedRef());
		}
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
	if (SessionInterface.IsValid())
	{
		FNamedOnlineSession* ExistingSession = SessionInterface->GetNamedSession(FName("My Session"));
		if (ExistingSession) {
			SessionInterface->DestroySession(FName("My Session"));
		}
		else { 
			CreateSession(); 
		}
	}
}

void UMultiplayerGameInstance::CreateSession()
{
	FOnlineSessionSettings SessionSettings;
	SessionSettings.bIsLANMatch = true;
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.NumPublicConnections = 2;
	SessionInterface->CreateSession(0, FName("My Session"), SessionSettings);
}

void UMultiplayerGameInstance::OnCreateSessionComplete(FName SessionName, bool isCompleted)
{
	if (!isCompleted) return;
	UEngine * Engine = GetEngine();
	Engine->AddOnScreenDebugMessage(0, 1.5f, FColor::Green, TEXT("Hosting"));

	UWorld* world = GetWorld();
	if (!ensure(world != nullptr)) return;

	world->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UMultiplayerGameInstance::OnDestroySessionComplete(FName SessionName, bool isCompleted)
{
	if (!isCompleted) return;
	CreateSession();
}

void UMultiplayerGameInstance::OnFindSessionsComplete(bool isCompleted)
{
	if (!isCompleted) return;

	UE_LOG(LogTemp, Warning, TEXT("Finding sessions completed."));
	auto SearchResults = OnlineSessionSearch->SearchResults;
	if (SearchResults.Num() > 0)
	{
		for (auto &i : SearchResults)
		{
			UE_LOG(LogTemp, Warning, TEXT("Session: %s"), *i.GetSessionIdStr());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Sessions found."));
	}
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

