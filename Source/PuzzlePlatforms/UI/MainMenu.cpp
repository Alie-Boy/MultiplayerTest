
#include "MainMenu.h"
#include "MenuInterface.h"

#include "SessionListSingleRow.h"

#include "Components\Button.h"
#include "Components\ScrollBox.h"
#include "Components\WidgetSwitcher.h"
#include "Components\EditableText.h"
#include "UObject\ConstructorHelpers.h"

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> ServerRow(TEXT("/Game/UI/MenuSystem/WBP_SessionListSingleRow"));
	if (!ensure(ServerRow.Class != nullptr)) return;
	ServerRowClass = ServerRow.Class;
}

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (Success == false) return false;
	
	if (!ensure(HostServerButton != nullptr)) return false;
	if (!ensure(JoinMenuButton != nullptr)) return false;
	if (!ensure(BackToMainButton != nullptr)) return false;
	if (!ensure(JoinServerButton != nullptr)) return false;
	if (!ensure(QuitToOSButton != nullptr)) return false;

	HostServerButton->OnClicked.AddDynamic(this, &UMainMenu::HostServerButtonClick);
	JoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::JoinMenuButtonClick);
	BackToMainButton->OnClicked.AddDynamic(this, &UMainMenu::BackToMainButtonClick);
	JoinServerButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServerButtonClick);
	QuitToOSButton->OnClicked.AddDynamic(this, &UMainMenu::QuitToOSButtonClick);

	return true;
}

void UMainMenu::Setup()
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

void UMainMenu::OnLevelRemovedFromWorld(ULevel * InLevel, UWorld * InWorld)
{
	RemoveFromViewport();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	FInputModeGameOnly InputMode;
	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = false;
}

void UMainMenu::SetMenuInterface(IMenuInterface* MenuInterface)
{
	this->MenuInterface = MenuInterface;
}

void UMainMenu::HostServerButtonClick()
{
	if (MenuInterface == nullptr) return;
	MenuInterface->Host();
}

void UMainMenu::JoinMenuButtonClick()
{
	if (MenuSwitcher == nullptr) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::BackToMainButtonClick()
{
	if (MenuSwitcher == nullptr) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::JoinServerButtonClick()
{
	if (MenuInterface == nullptr) return;
	//FString address = IPAddressInput->GetText().ToString();
	//MenuInterface->Join(address);
	USessionListSingleRow* item = CreateWidget<USessionListSingleRow>(this, ServerRowClass);
	IPAddressScrollBox->AddChild(item);
}

void UMainMenu::QuitToOSButtonClick()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ConsoleCommand("Quit");
}
