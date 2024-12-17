#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TDS_GameHUD.generated.h"

class UTDS_PauseMenuWD;
class ATDS_PlayerController;
class UTDS_MainHUDWD;

UCLASS()
class TOPDOWNSHOOTER_API ATDS_GameHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	void Initialize(ATDS_PlayerController* InPlayerController);

	void CreateMainWidget();
	void RemoveMainWidget();

	void CreatePauseMenuWidget();
	void RemovePauseMenuWidget();

public:

	UPROPERTY(EditDefaultsOnly, Category = "Main widget")
	TSubclassOf<UTDS_MainHUDWD> MainWidgetClass;
	UPROPERTY()
	UTDS_MainHUDWD* MainWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Main widget")
	TSubclassOf<UTDS_PauseMenuWD> PauseMenuWidgetClass;
	UPROPERTY()
	UTDS_PauseMenuWD* PauseMenuWidget;

private:

	UPROPERTY()
	ATDS_PlayerController* PlayerController; 
};
