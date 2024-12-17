#include "TDS_PauseMenuWD.h"
#include "TDS_ButtonWithText.h"



void UTDS_PauseMenuWD::NativeConstruct()
{
	Super::NativeConstruct();
	if (!ContinueGameButton || !ExitGameButton) return;

	ContinueGameButton->OnButtonPressedEvent.BindUObject(this, &UTDS_PauseMenuWD::OnContinueButtonPressed);
	ExitGameButton->OnButtonPressedEvent.BindUObject(this, &UTDS_PauseMenuWD::OnExitButtonPressed);
}

void UTDS_PauseMenuWD::OnContinueButtonPressed()
{
	ContinueGameEvent.ExecuteIfBound();
}

void UTDS_PauseMenuWD::OnExitButtonPressed()
{
	ExitGameEvent.ExecuteIfBound();
}
