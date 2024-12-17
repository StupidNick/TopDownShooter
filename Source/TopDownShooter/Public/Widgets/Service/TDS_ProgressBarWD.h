#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "TDS_ProgressBarWD.generated.h"



UCLASS()
class TOPDOWNSHOOTER_API UTDS_ProgressBarWD : public UUserWidget
{
	GENERATED_BODY()

public:

	void InitializeWidget(const float InMaxValue, const float InCurrentValue);

	void ChangeValue(const float InValue) const;

public:

	UPROPERTY(meta = (BindWidget))
	UProgressBar* ProgressBar;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text;

private:

	float MaxValue = 100;
};
