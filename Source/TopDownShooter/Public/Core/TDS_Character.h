#pragma once

#include "CoreMinimal.h"
#include "TDS_Controllable.h"
#include "GameFramework/Character.h"
#include "TDS_Character.generated.h"

class UTDS_EquipmentComponent;
class UTDS_HealthComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS(Blueprintable)
class ATDS_Character : public ACharacter, public ITDS_Controllable
{
	GENERATED_BODY()

public:
	ATDS_Character();

	virtual void BeginPlay() override;

	// ITDS_Controllable start
	virtual void AddMove(FVector2d& InDirection) override;
	virtual void AddRotation(const FVector& InTargetLocation) override;
	virtual void MousePressed() override;
	virtual void MouseReleased() override;
	// end

	UCameraComponent* GetCamera() const;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	UCameraComponent* TopDownCameraComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UTDS_EquipmentComponent* EquipmentComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UTDS_HealthComponent* HealthComponent;
};
