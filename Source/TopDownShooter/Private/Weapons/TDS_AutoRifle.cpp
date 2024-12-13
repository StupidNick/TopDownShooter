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
	if (!WeaponInfo || !bIsFiring || !CanShoot() || !OwnedController) return;

	FVector WorldLocation, WorldDirection;
	OwnedController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
	
	FHitResult Result;
	const FVector StartLocation = Mesh->GetSocketLocation(WeaponInfo->FireSocketName);
	GetWorld()->LineTraceSingleByChannel(Result, StartLocation, FVector(WorldLocation.X, WorldLocation.Y, StartLocation.Z), ECC_WorldStatic);
	DrawDebugLine(GetWorld(), StartLocation, FVector(WorldLocation.X, WorldLocation.Y, StartLocation.Z), FColor::Red);
	
	bCanShoot = false;
	Ammo--;
	UE_LOG(LogTemp, Warning, TEXT("%s Fire from weapon, ammo left %i. Hit %s"), *GetName(), Ammo, *Result.HitObjectHandle.GetName());
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
