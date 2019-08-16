
#include "PauseMenu.h"
#include "MenuInterface.h"
#include "Components\Button.h"

bool UPauseMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (Success == false) return false;

	if (!ensure(ResumeButton != nullptr)) return false;
	if (!ensure(QuitToMenuButton != nullptr)) return false;

	ResumeButton->OnClicked.AddDynamic(this, &UPauseMenu::ResumeButtonClicked);
	QuitToMenuButton->OnClicked.AddDynamic(this, &UPauseMenu::QuitToMenuButtonClicked);

	return true;
}

void UPauseMenu::ShowPauseMenu()
{
	this->AddToViewport();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = true;
}

void UPauseMenu::HidePauseMenu()
{
	RemoveFromViewport();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeGameOnly InputMode;
	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = false;
	
	MarkPendingKill();
}

void UPauseMenu::ResumeButtonClicked()
{
	HidePauseMenu();
}

void UPauseMenu::QuitToMenuButtonClicked()
{
	MenuInterface->QuitToMenu();
}
