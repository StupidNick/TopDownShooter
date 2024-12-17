#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDS_PauseMenuWD.generated.h"


class UTDS_ButtonWithText;


UCLASS()
class TOPDOWNSHOOTER_API UTDS_PauseMenuWD : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

	void OnContinueButtonPressed();
	void OnExitButtonPressed();

public:
	
	FSimpleDelegate ContinueGameEvent;
	FSimpleDelegate ExitGameEvent;

	UPROPERTY(meta=(BindWidget))
	UTDS_ButtonWithText* ContinueGameButton;
	UPROPERTY(meta=(BindWidget))
	UTDS_ButtonWithText* ExitGameButton;
};
