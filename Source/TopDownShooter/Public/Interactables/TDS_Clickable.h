#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TDS_Clickable.generated.h"

UINTERFACE(MinimalAPI)
class UTDS_Clickable : public UInterface
{
	GENERATED_BODY()
};

class TOPDOWNSHOOTER_API ITDS_Clickable
{
	GENERATED_BODY()

public:
	virtual void OnPressed();
	virtual void OnReleased();
};
