#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TDS_Character.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS(Blueprintable)
class ATDS_Character : public ACharacter
{
	GENERATED_BODY()

public:
	ATDS_Character();

	virtual void Tick(float DeltaSeconds) override;

	void Move(FVector2d InDirection) const;

	UFUNCTION(Server, Unreliable)
	void UpdateRotation(const FRotator& InTargetRotator);
	void UpdateRotation_Implementation(const FRotator& InTargetRotator);

	UCameraComponent* GetCamera() const;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	UCameraComponent* TopDownCameraComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	USpringArmComponent* CameraBoom;
};
