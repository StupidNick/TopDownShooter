#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDS_MainHUDWD.generated.h"

class ITDS_Usable;
class UTDS_CounterWD;
class UTDS_ProgressBarWD;

UCLASS()
class TOPDOWNSHOOTER_API UTDS_MainHUDWD : public UUserWidget
{
	GENERATED_BODY()

public:

	void InitializeWidget() const;

	void OnHealthChanged(float InHealth);
	void OnAmmoChanged(float InAmmo);

	void OnObjectInHandsChanged(const TScriptInterface<ITDS_Usable>& InObject);

public:

	UPROPERTY(meta = (BindWidget))
	UTDS_ProgressBarWD*  HealthProgressBar;

	UPROPERTY(meta = (BindWidget))
	UTDS_CounterWD*  AmmoCounter;
};
