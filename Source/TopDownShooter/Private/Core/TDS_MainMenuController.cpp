#include "TDS_MainMenuController.h"

#include "TDS_MainMenuHUD.h"


void ATDS_MainMenuController::BeginPlay()
{
	Super::BeginPlay();

	HUD = Cast<ATDS_MainMenuHUD>(GetHUD());
	if (!HUD) return;
	
	HUD->Initialize(this);
	HUD->CreateMainMenu();
}
