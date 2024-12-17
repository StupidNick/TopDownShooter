#include "TDS_MainMenuWD.h"



void UTDS_MainMenuWD::NativeConstruct()
{
	Super::NativeConstruct();

	if (!CreateGameButton || !JoinGameButton || !ExitGameButton) return;

	CreateGameButton->OnButtonPressedEvent.BindUObject(this, &UTDS_MainMenuWD::CreateGame);
	JoinGameButton->OnButtonPressedEvent.BindUObject(this, &UTDS_MainMenuWD::JoinGame);
	ExitGameButton->OnButtonPressedEvent.BindUObject(this, &UTDS_MainMenuWD::ExitGame);
}

void UTDS_MainMenuWD::CreateGame()
{
	CreateGameEvent.ExecuteIfBound();
}

void UTDS_MainMenuWD::JoinGame()
{
	JoinGameEvent.ExecuteIfBound();
}

void UTDS_MainMenuWD::ExitGame()
{
	ExitGameEvent.ExecuteIfBound();
}
