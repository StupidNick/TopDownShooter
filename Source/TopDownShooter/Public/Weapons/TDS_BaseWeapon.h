#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDS_BaseWeapon.generated.h"

class UTDS_WeaponInfo;

UCLASS()
class TOPDOWNSHOOTER_API ATDS_BaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ATDS_BaseWeapon();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Server, Reliable)
	virtual void Initialize();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual bool CanShoot();

	void TakeOwnedController();

public:

	UPROPERTY(EditDefaultsOnly, Category = "Base Info")
	UTDS_WeaponInfo* WeaponInfo;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* Mesh;
protected:

	UPROPERTY(Replicated)
	int32 Ammo;

	bool bCanShoot = true;

	UPROPERTY(Replicated)
	APlayerController* OwnedController;
};
