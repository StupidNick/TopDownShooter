#include "TDS_MainMenuHUD.h"
#include "TDS_MainMenuWD.h"
#include "Kismet/KismetSystemLibrary.h"


void ATDS_MainMenuHUD::Initialize(ATDS_MainMenuController* InController)
{
	PlayerController = InController;
}

void ATDS_MainMenuHUD::CreateMainMenu()
{
	if (!MainMenuWidgetClass || MainMenuWidget) return;

	MainMenuWidget = CreateWidget<UTDS_MainMenuWD>(GetWorld(), MainMenuWidgetClass);
	if (!MainMenuWidget) return;

	MainMenuWidget->JoinGameEvent.BindUObject(this, &ATDS_MainMenuHUD::CreateJoinGameMenu);
	MainMenuWidget->CreateGameEvent.BindUObject(this, &ATDS_MainMenuHUD::CreateCreateGameMenu);
	MainMenuWidget->ExitGameEvent.BindUObject(this, &ATDS_MainMenuHUD::ExitGame);
	
	MainMenuWidget->AddToViewport();
}

void ATDS_MainMenuHUD::RemoveMainMenu()
{
	if (!MainMenuWidget) return;

	MainMenuWidget->RemoveFromParent();
	MainMenuWidget = nullptr;
}

void ATDS_MainMenuHUD::CreateCreateGameMenu()
{
}

void ATDS_MainMenuHUD::RemoveCreateGameMenu()
{
}

void ATDS_MainMenuHUD::CreateJoinGameMenu()
{
}

void ATDS_MainMenuHUD::RemoveJoinGameMenu()
{
}

void ATDS_MainMenuHUD::ExitGame()
{
	if (!PlayerController) return;

	UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, true);
}
