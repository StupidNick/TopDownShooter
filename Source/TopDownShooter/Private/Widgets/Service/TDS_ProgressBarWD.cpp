#include "TDS_ProgressBarWD.h"


void UTDS_ProgressBarWD::InitializeWidget(const float InMaxValue, const float InCurrentValue)
{
	MaxValue = InMaxValue;
	ChangeValue(InCurrentValue);
}

void UTDS_ProgressBarWD::ChangeValue(const float InValue) const
{
	if (!Text || !ProgressBar) return;

	Text->SetText(FText::AsNumber(InValue));
	ProgressBar->SetPercent(InValue/MaxValue);
}
