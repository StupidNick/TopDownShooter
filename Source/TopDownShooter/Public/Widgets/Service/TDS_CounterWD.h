#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDS_CounterWD.generated.h"

class UTextBlock;

UCLASS()
class TOPDOWNSHOOTER_API UTDS_CounterWD : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetCurrentNum(const int32 InNum);
	void SetMaxNum(const int32 InNum);

	void OutputFinalCount();

public:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentNumText;

private:

	int32 MaxNum = -1;
	int32 CurrentNum;
};
