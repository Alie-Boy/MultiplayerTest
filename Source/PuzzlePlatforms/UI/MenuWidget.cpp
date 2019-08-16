


#include "MenuWidget.h"
#include "MenuInterface.h"

UMenuWidget::UMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UMenuWidget::SetMenuInterface(IMenuInterface* MenuInterface)
{
	this->MenuInterface = MenuInterface;
}

void UMenuWidget::Setup()
{
	AddToViewport();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = true;
}

void UMenuWidget::OnLevelRemovedFromWorld(ULevel * InLevel, UWorld * InWorld)
{
	RemoveFromViewport();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	FInputModeGameOnly InputMode;
	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = false;
}
