
#include "MainMenu.h"
#include "MenuInterface.h"

#include "Components\Button.h"


bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (Success == false) return false;
	
	if (!ensure(Host != nullptr)) return false;
	if (!ensure(Join != nullptr)) return false;

	Host->OnClicked.AddDynamic(this, &UMainMenu::HostButtonClick);
	Join->OnClicked.AddDynamic(this, &UMainMenu::JoinButtonClick);

	return true;
}

void UMainMenu::Setup()
{
	AddToViewport();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = true;
}


void UMainMenu::OnLevelRemovedFromWorld(ULevel * InLevel, UWorld * InWorld)
{
	RemoveFromViewport();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	FInputModeGameOnly InputMode;
	InputMode.SetConsumeCaptureMouseDown(false);
	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = false;
}

void UMainMenu::SetMenuInterface(IMenuInterface* MenuInterface)
{
	this->MenuInterface = MenuInterface;
}

void UMainMenu::HostButtonClick()
{
	if (MenuInterface == nullptr) return;
	MenuInterface->Host();
}

void UMainMenu::JoinButtonClick()
{
	if (MenuInterface == nullptr) return;
	MenuInterface->Join("temporary text");
}