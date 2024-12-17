#pragma once

#include "CoreMinimal.h"
#include "TDS_ButtonWithText.h"
#include "Blueprint/UserWidget.h"
#include "TDS_MainMenuWD.generated.h"


UCLASS()
class TOPDOWNSHOOTER_API UTDS_MainMenuWD : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

	UFUNCTION()
	void CreateGame();
	UFUNCTION()
	void JoinGame();
	UFUNCTION()
	void ExitGame();

public:

	FSimpleDelegate CreateGameEvent;
	FSimpleDelegate JoinGameEvent;
	FSimpleDelegate ExitGameEvent;

	UPROPERTY(meta=(BindWidget))
	UTDS_ButtonWithText* CreateGameButton;
	UPROPERTY(meta=(BindWidget))
	UTDS_ButtonWithText* JoinGameButton;
	UPROPERTY(meta=(BindWidget))
	UTDS_ButtonWithText* ExitGameButton;
};
