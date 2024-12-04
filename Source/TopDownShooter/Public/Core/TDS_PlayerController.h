#pragma once

#include "CoreMinimal.h"
#include "TDS_Character.h"
#include "GameFramework/PlayerController.h"
#include "TDS_PlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class UNiagaraSystem;

UCLASS()
class ATDS_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATDS_PlayerController();

protected:

	virtual void SetupInputComponent() override;
	
	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds) override;

	void OnClick();

	void UpdateCharacterRotation();
	
public:
	void OnMoveForwardPressed(const FInputActionValue& Input);
	void OnInputStarted();

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* MoveForwardAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveRightAction;

private:

	UPROPERTY()
	ATDS_Character* CurrentCharacter = nullptr;
};
