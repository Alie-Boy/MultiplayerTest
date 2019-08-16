

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SessionListSingleRow.generated.h"

class UTextBlock;

UCLASS()
class PUZZLEPLATFORMS_API USessionListSingleRow : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ServerName;

};
