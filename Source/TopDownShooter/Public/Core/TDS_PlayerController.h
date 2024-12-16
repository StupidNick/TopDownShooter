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
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:

	virtual void SetupInputComponent() override;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	void OnMousePressed();
	void OnMouseReleased();
	
	void OnReloadPressed();
	
	void OnMoveForwardPressed(const FInputActionValue& Input);

	void UpdateCharacterRotation() const;
	void OnPlayerDead();

	UFUNCTION(Server, Unreliable)
	void Respawn();

	virtual void OnPossess(APawn* InPawn) override;

public:

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MouseClickAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* ReloadAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TEnumAsByte<ECollisionChannel> MouseTraceChanel;

private:

	UPROPERTY(Replicated)
	TScriptInterface<ITDS_Controllable> CurrentCharacter = nullptr;
};
