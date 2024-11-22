#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "TDS_PlayerController.generated.h"

class UNiagaraSystem;

UCLASS()
class ATDS_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATDS_PlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* SetDestinationClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* SetDestinationTouchAction;

protected:
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;
	
	virtual void BeginPlay();

	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void OnTouchTriggered();
	void OnTouchReleased();

private:
	FVector CachedDestination;

	bool bIsTouch;
	float FollowTime;
};


