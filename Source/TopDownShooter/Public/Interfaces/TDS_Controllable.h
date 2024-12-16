#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TDS_Controllable.generated.h"

UINTERFACE(MinimalAPI)
class UTDS_Controllable : public UInterface
{
	GENERATED_BODY()
};

class TOPDOWNSHOOTER_API ITDS_Controllable
{
	GENERATED_BODY()

public:
	virtual void MousePressed();
	virtual void MouseReleased();
	virtual void ReloadPressed();
	
	virtual void AddMove(FVector2d& InDirection);
	virtual void AddRotation(const FVector& InTargetLocation);

	virtual void SetPlayerController(APlayerController* InController);
	virtual APlayerController* GetPlayerController();

	FSimpleDelegate OnPLayerDead;
};
