#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TDS_WeaponInfo.generated.h"

UENUM()
enum EAmmoType
{
	Type762,
	Type556,
	Type919
};

UCLASS()
class TOPDOWNSHOOTER_API UTDS_WeaponInfo : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
	TEnumAsByte<EAmmoType> AmmoType;

	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
	int32 MaxAmmo;

	UPROPERTY(EditDefaultsOnly, Category = "Common")
	bool bOneInChamber;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Characteristics")
	float Damage;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Characteristics")
	float ReloadTime;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Characteristics")
	float TimeBetweenShots;

	// UPROPERTY(EditDefaultsOnly, Category = "Weapon Characteristics")
	// bool bAutoFire;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Characteristics")
	FName FireSocketName;
};
