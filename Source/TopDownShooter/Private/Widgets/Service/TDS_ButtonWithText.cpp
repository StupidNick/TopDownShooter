#include "TDS_ButtonWithText.h"



void UTDS_ButtonWithText::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (!Button || !Text) return;

	Text->SetText(DefaultText);
	Button->OnClicked.AddDynamic(this, &UTDS_ButtonWithText::OnButtonPressed);
}

void UTDS_ButtonWithText::OnButtonPressed()
{
	OnButtonPressedEvent.ExecuteIfBound();
}
