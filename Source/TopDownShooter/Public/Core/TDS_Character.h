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
	void UpdateRotation(const FVector& InMousePosition);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
};

