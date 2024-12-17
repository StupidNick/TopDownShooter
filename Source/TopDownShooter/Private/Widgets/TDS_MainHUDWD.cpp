#include "TDS_MainHUDWD.h"
#include "TDS_CounterWD.h"
#include "TDS_ProgressBarWD.h"
#include "TDS_Usable.h"


void UTDS_MainHUDWD::InitializeWidget() const
{
	if (!HealthProgressBar || !AmmoCounter) return;

	AmmoCounter->SetVisibility(ESlateVisibility::Collapsed);
}

void UTDS_MainHUDWD::OnHealthChanged(float InHealth)
{
	if (!HealthProgressBar) return;

	HealthProgressBar->ChangeValue(InHealth);
}

void UTDS_MainHUDWD::OnAmmoChanged(float InAmmo)
{
	if (!AmmoCounter) return;
	
	AmmoCounter->SetCurrentNum(InAmmo);
}

void UTDS_MainHUDWD::OnObjectInHandsChanged(const TScriptInterface<ITDS_Usable>& InObject)
{
	if (!InObject || !AmmoCounter) return;

	if (InObject->NeedAmmoCounter())
	{
		AmmoCounter->SetVisibility(ESlateVisibility::Visible);
		AmmoCounter->SetCurrentNum(InObject->GetAmmo());
	}
	else
	{
		AmmoCounter->SetVisibility(ESlateVisibility::Collapsed);
	}
}
