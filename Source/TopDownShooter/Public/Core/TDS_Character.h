#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TDS_Character.generated.h"

UCLASS(Blueprintable)
class ATDS_Character : public ACharacter
{
	GENERATED_BODY()

public:
	ATDS_Character();

	virtual void Tick(float DeltaSeconds) override;

	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
};

