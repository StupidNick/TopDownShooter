#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TDS_Character.generated.h"

class UTDS_EquipmentComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS(Blueprintable)
class ATDS_Character : public ACharacter
{
	GENERATED_BODY()

public:
	ATDS_Character();

	void Move(FVector2d InDirection) const;

	UFUNCTION(Server, Unreliable)
	void UpdateRotation(const FRotator& InTargetRotator);
	void UpdateRotation_Implementation(const FRotator& InTargetRotator);

	UFUNCTION(Server, Reliable)
	void OnMousePressed();
	void OnMousePressed_Implementation();
	UFUNCTION(Server, Reliable)
	void OnMouseReleased();
	void OnMouseReleased_Implementation();

	UCameraComponent* GetCamera() const;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	UCameraComponent* TopDownCameraComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UTDS_EquipmentComponent* EquipmentComponent;
};
