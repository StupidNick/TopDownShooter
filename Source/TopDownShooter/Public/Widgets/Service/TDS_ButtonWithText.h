#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "TDS_ButtonWithText.generated.h"



UCLASS()
class TOPDOWNSHOOTER_API UTDS_ButtonWithText : public UUserWidget
{
	GENERATED_BODY()

	void NativeConstruct();
	
	UFUNCTION()
	void OnButtonPressed();
public:

	FSimpleDelegate OnButtonPressedEvent;
	
	UPROPERTY(meta=(BindWidget))
	UButton* Button;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text;

	UPROPERTY(EditAnywhere)
	FText DefaultText;
};
