#include "TDS_BaseWeapon.h"

#include "TDS_Controllable.h"
#include "TDS_WeaponInfo.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"



ATDS_BaseWeapon::ATDS_BaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	RootComponent = Mesh;
}

void ATDS_BaseWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ATDS_BaseWeapon, Ammo, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(ATDS_BaseWeapon, OwnedController, COND_OwnerOnly);
}

void ATDS_BaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

bool ATDS_BaseWeapon::CanShoot()
{
	if (!OwnedController)
	{
		TakeOwnedController();
	}
	return Ammo > 0 && bCanShoot && !bIsReloading;
}

bool ATDS_BaseWeapon::CanReload()
{
	if (!WeaponInfo) return false;
	
	return !bIsReloading && Ammo < WeaponInfo->MaxAmmo;
}

void ATDS_BaseWeapon::TakeOwnedController()
{
	if (const auto CurrentOwner = Cast<ITDS_Controllable>(GetOwner()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Current owner is valid %s"), CurrentOwner->GetPlayerController());
		OwnedController = CurrentOwner->GetPlayerController();
		if (OwnedController)
		{
			UE_LOG(LogTemp, Error, TEXT("Controller: %s"), *OwnedController->GetName());
		}
	}
}

void ATDS_BaseWeapon::Initialize_Implementation()
{
	
}
