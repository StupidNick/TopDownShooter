#pragma once

#include "CoreMinimal.h"
#include "TDS_MainMenuController.h"
#include "GameFramework/HUD.h"
#include "TDS_MainMenuHUD.generated.h"

class UTDS_MainMenuWD;

UCLASS()
class TOPDOWNSHOOTER_API ATDS_MainMenuHUD : public AHUD
{
	GENERATED_BODY()

public:

	void Initialize(ATDS_MainMenuController* InController);

	void CreateMainMenu();
	void RemoveMainMenu();

	UFUNCTION()
	void CreateCreateGameMenu();
	UFUNCTION()
	void RemoveCreateGameMenu();

	UFUNCTION()
	void CreateJoinGameMenu();
	UFUNCTION()
	void RemoveJoinGameMenu();

	UFUNCTION()
	void ExitGame();

public:
	
	UPROPERTY(EditDefaultsOnly, Category = "Main menu")
	TSubclassOf<UTDS_MainMenuWD> MainMenuWidgetClass;
	UPROPERTY()
	UTDS_MainMenuWD* MainMenuWidget;

private:

	UPROPERTY()
	ATDS_MainMenuController* PlayerController;
};
