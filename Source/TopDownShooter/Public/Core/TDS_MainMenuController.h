#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TDS_MainMenuController.generated.h"


class ATDS_MainMenuHUD;

UCLASS()
class TOPDOWNSHOOTER_API ATDS_MainMenuController : public APlayerController
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

public:

	UPROPERTY()
	ATDS_MainMenuHUD* HUD;
};
