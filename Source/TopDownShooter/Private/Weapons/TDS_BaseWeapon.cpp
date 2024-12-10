#include "TDS_BaseWeapon.h"
#include "Net/UnrealNetwork.h"


ATDS_BaseWeapon::ATDS_BaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

void ATDS_BaseWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ATDS_BaseWeapon, Ammo, COND_OwnerOnly);
	// DOREPLIFETIME_CONDITION(ATDS_BaseWeapon, bCanShoot, COND_OwnerOnly);
}

void ATDS_BaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		Initialize();
	}
}

bool ATDS_BaseWeapon::CanShoot()
{
	return Ammo > 0 && bCanShoot;
}

void ATDS_BaseWeapon::OnRep_AmmoChanged()
{
}

void ATDS_BaseWeapon::Initialize_Implementation()
{
}
