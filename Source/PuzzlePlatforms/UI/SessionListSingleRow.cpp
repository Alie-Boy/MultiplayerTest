
#include "SessionListSingleRow.h"
#include "MainMenu.h"

#include "Components\Button.h"

bool USessionListSingleRow::Initialize()
{
	bool success = Super::Initialize();
	if (!success) return false;
	ServerSelectButton->OnClicked.AddDynamic(this, &USessionListSingleRow::ServerSelectButtonClicked);
	return true;
}

void USessionListSingleRow::ServerSelectButtonClicked()
{
	Parent->SelectIndex(selfIndex);
}

void USessionListSingleRow::Setup(UMainMenu * MainMenu, uint32 index)
{
	Parent = MainMenu;
	selfIndex = index;
}
