
#include "MainMenu.h"
#include "MenuInterface.h"
#include "SessionListSingleRow.h"

#include "Components\Button.h"
#include "Components\ScrollBox.h"
#include "Components\WidgetSwitcher.h"
#include "Components\EditableText.h"
#include "Components\TextBlock.h"
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

void UMainMenu::HostServerButtonClick()
{
	if (MenuInterface == nullptr) return;
	MenuInterface->Host();
}

void UMainMenu::SetServerList(TArray<FString> ServerNames)
{
	IPAddressScrollBox->ClearChildren();

	uint32 index = 0;
	for (const FString& serverName: ServerNames)
	{
		USessionListSingleRow* item = CreateWidget<USessionListSingleRow>(this, ServerRowClass);
		if (!ensure(item != nullptr)) return;
		item->ServerName->SetText(FText::FromString(serverName));
		item->Setup(this, index);
		++index;

		IPAddressScrollBox->AddChild(item);
	}
}

void UMainMenu::SelectIndex(uint32 Index)
{
	SelectedIndex = Index;
}

void UMainMenu::JoinMenuButtonClick()
{
	if (MenuSwitcher == nullptr) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);
	if (MenuInterface == nullptr) return;
	MenuInterface->RefreshServerList();
}

void UMainMenu::BackToMainButtonClick()
{
	if (MenuSwitcher == nullptr) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::JoinServerButtonClick()
{
	if (SelectedIndex.IsSet())
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected index = %d"), SelectedIndex.GetValue());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected index not set."));
	}

	if (MenuInterface == nullptr) return;
	//FString address = IPAddressInput->GetText().ToString();
	MenuInterface->Join("");
}

void UMainMenu::QuitToOSButtonClick()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ConsoleCommand("Quit");
}
