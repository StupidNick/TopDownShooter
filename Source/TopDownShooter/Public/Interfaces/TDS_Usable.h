#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TDS_Usable.generated.h"

UINTERFACE(MinimalAPI)
class UTDS_Usable : public UInterface
{
	GENERATED_BODY()
};

class TOPDOWNSHOOTER_API ITDS_Usable
{
	GENERATED_BODY()

public:
	virtual void OnLeftMouseButtonPressed();
	virtual void OnLeftMouseButtonReleased();

	virtual void OnRightMouseButtonPressed();
	virtual void OnRightMouseButtonReleased();
	
	virtual void OnReloadPressed();

	virtual void Detach();
};
