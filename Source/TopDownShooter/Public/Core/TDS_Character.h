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
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// ITDS_Controllable start
	virtual void AddMove(FVector2d& InDirection) override;
	UFUNCTION(Server, Unreliable)
	virtual void AddRotation(const FVector& InTargetLocation) override;
	
	virtual void MousePressed() override;
	virtual void MouseReleased() override;
	virtual void ReloadPressed() override;
	// end

	UCameraComponent* GetCamera() const;

	UFUNCTION(Server, Reliable)
	virtual void SetPlayerController(APlayerController* InController) override;
	virtual APlayerController* GetPlayerController() override;

private:

	void Initialize();

	UFUNCTION(Server, Reliable)
	void OnPlayerDeadOnServer();
	UFUNCTION(NetMulticast, Reliable)
	void OnPlayerDeadOnClient();

	UFUNCTION(Server, Reliable)
	void DestroyCharacter();

public:
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	UCameraComponent* TopDownCameraComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UTDS_EquipmentComponent* EquipmentComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UTDS_HealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Common")
	FCollisionProfileName RagdollCollisionProfileName;

private:

	UPROPERTY(Replicated)
	APlayerController* CurrentPlayerController;

	UPROPERTY(Replicated)
	bool bIsAlive = true;
};
