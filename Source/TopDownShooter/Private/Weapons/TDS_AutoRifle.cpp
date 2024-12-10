#include "TDS_AutoRifle.h"
#include "TDS_WeaponInfo.h"


void ATDS_AutoRifle::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ATDS_AutoRifle::Initialize()
{
	Super::Initialize();

	if (!WeaponInfo) return;
	
	Ammo = WeaponInfo->MaxAmmo; 
}

void ATDS_AutoRifle::OnLeftMouseButtonPressed()
{
	ITDS_Usable::OnLeftMouseButtonPressed();
	UE_LOG(LogTemp, Warning, TEXT("Start fire"));

	StartFire();
}

void ATDS_AutoRifle::OnLeftMouseButtonReleased()
{
	ITDS_Usable::OnLeftMouseButtonReleased();

	StopFire();
}

void ATDS_AutoRifle::OnRightMouseButtonPressed()
{
	ITDS_Usable::OnRightMouseButtonPressed();
}

void ATDS_AutoRifle::OnRightMouseButtonReleased()
{
	ITDS_Usable::OnRightMouseButtonReleased();
}

void ATDS_AutoRifle::OnReloadPressed()
{
	ITDS_Usable::OnReloadPressed();
}

void ATDS_AutoRifle::StartFire_Implementation()
{
	bIsFiring = true;

	Fire();
}

void ATDS_AutoRifle::Fire_Implementation()
{
	if (!WeaponInfo || !bIsFiring || !CanShoot()) return;
	
	UE_LOG(LogTemp, Warning, TEXT("Fire from weapon"));
	bCanShoot = false;
	GetWorldTimerManager().SetTimer(ReloadBetweenShotsTimerHandle, this, &ATDS_AutoRifle::FireAgain_Implementation, WeaponInfo->TimeBetweenShots);
}

void ATDS_AutoRifle::FireAgain_Implementation()
{
	bCanShoot = true;
	Fire();
}

void ATDS_AutoRifle::StopFire_Implementation()
{
	bIsFiring = false;
}
