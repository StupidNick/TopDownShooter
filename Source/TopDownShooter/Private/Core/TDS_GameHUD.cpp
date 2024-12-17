#include "TDS_GameHUD.h"
#include "TDS_MainHUDWD.h"
#include "TDS_PauseMenuWD.h"
#include "TDS_PlayerController.h"
#include "Kismet/KismetSystemLibrary.h"


void ATDS_GameHUD::Initialize(ATDS_PlayerController* InPlayerController)
{
	PlayerController = InPlayerController;
}

void ATDS_GameHUD::CreateMainWidget()
{
	if (!MainWidgetClass || MainWidget) return;

	MainWidget = CreateWidget<UTDS_MainHUDWD>(GetWorld(), MainWidgetClass);
	if (!MainWidget) return;

	if (PlayerController)
	{
		PlayerController->OnHealthChangedEvent.AddUObject(MainWidget, &UTDS_MainHUDWD::OnHealthChanged);
		PlayerController->OnAmmoChangedEvent.AddUObject(MainWidget, &UTDS_MainHUDWD::OnAmmoChanged);
		
		PlayerController->OnObjectInHandsChangedEvent.AddUObject(MainWidget, &UTDS_MainHUDWD::OnObjectInHandsChanged);
	}
	MainWidget->Initialize();
	MainWidget->AddToViewport();
}

void ATDS_GameHUD::RemoveMainWidget()
{
	if (!MainWidget || !PlayerController) return;

	PlayerController->OnHealthChangedEvent.RemoveAll(MainWidget);
	PlayerController->OnAmmoChangedEvent.RemoveAll(MainWidget);

	MainWidget->RemoveFromParent();
	MainWidget = nullptr;
}

void ATDS_GameHUD::CreatePauseMenuWidget()
{
	if (!PauseMenuWidgetClass) return;
	if (PauseMenuWidget)
	{
		RemovePauseMenuWidget();
		return;
	}

	PauseMenuWidget = CreateWidget<UTDS_PauseMenuWD>(GetWorld(), PauseMenuWidgetClass);
	if (!PauseMenuWidget) return;

	PauseMenuWidget->ContinueGameEvent.BindLambda([&]()
	{
		RemovePauseMenuWidget();
	});
	PauseMenuWidget->ExitGameEvent.BindLambda([&]()
	{
		if (!PlayerController) return;
		
		UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, true);
	});
	
	PauseMenuWidget->AddToViewport();
}

void ATDS_GameHUD::RemovePauseMenuWidget()
{
	if (!PauseMenuWidget) return;

	PauseMenuWidget->RemoveFromParent();
	PauseMenuWidget = nullptr;
}
