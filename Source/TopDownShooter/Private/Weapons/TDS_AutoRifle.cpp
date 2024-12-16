#include "TDS_AutoRifle.h"

#include "TDS_HealthComponent.h"
#include "TDS_WeaponInfo.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


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

	StopFireOnServer();
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

	StartReloadOnServer();
}

void ATDS_AutoRifle::Detach()
{
	ITDS_Usable::Detach();

	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}

void ATDS_AutoRifle::StartFire()
{
	if (!CanShoot()) return;
	
	StartFireOnServer();
	Fire();
}

void ATDS_AutoRifle::StartFireOnServer_Implementation()
{
	bIsFiring = true;
}

void ATDS_AutoRifle::Fire_Implementation()
{
	if (!OwnedController) return;

	FVector WorldLocation, WorldDirection;
	OwnedController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	FHitResult Result;
	const FVector StartLocation = Mesh->GetSocketLocation(WeaponInfo->FireSocketName);
	GetWorld()->LineTraceSingleByChannel(Result, WorldLocation, WorldLocation + WorldDirection * 5000, CameraTraceCollisionChannel);
	DrawDebugFire(WorldLocation, WorldLocation + WorldDirection * 5000);

	FireOnServer(Result.Location);
}

void ATDS_AutoRifle::FireOnServer_Implementation(FVector InTargetLocation)
{
	if (!WeaponInfo || !bIsFiring || !CanShoot()) return;
	
	TArray<FHitResult> Result;
	const FVector StartLocation = Mesh->GetSocketLocation(WeaponInfo->FireSocketName);
	FVector Direction = InTargetLocation - StartLocation;
	Direction.Normalize();
	const FVector EndLocation = StartLocation + Direction * 1000;
	
	GetWorld()->LineTraceMultiByChannel(Result, StartLocation,  EndLocation, ShootCollisionChannel);
	DrawDebugFire(StartLocation, EndLocation);
	
	bCanShoot = false;
	Ammo--;
	GetWorldTimerManager().SetTimer(ReloadBetweenShotsTimerHandle, this, &ATDS_AutoRifle::FireAgainOnServer, WeaponInfo->TimeBetweenShots);

	for (auto HitResult : Result)
	{
		if (!HitResult.GetActor()->IsA(ACharacter::StaticClass())) break;
		
		HitResult.GetActor()->TakeDamage(WeaponInfo->Damage, FDamageEvent(), OwnedController, OwnedController->GetCharacter());
		
		UE_LOG(LogTemp, Warning, TEXT("%s Fire from weapon, ammo left %i. Hit %s"), *GetName(), Ammo, *HitResult.HitObjectHandle.GetName());
	}

}

void ATDS_AutoRifle::DrawDebugFire_Implementation(const FVector& InStartLocation, const FVector& InEndLocation)
{
	DrawDebugLine(GetWorld(), InStartLocation, InEndLocation, FColor::Red, false, 5);
}

void ATDS_AutoRifle::FireAgainOnServer_Implementation()
{
	bCanShoot = true;
	Fire();
}

void ATDS_AutoRifle::StopFireOnServer_Implementation()
{
	bIsFiring = false;
}

void ATDS_AutoRifle::StartReloadOnServer_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("Reload in weapon"));
	if (!CanReload()) return;

	bIsFiring = false;
	bCanShoot = false;

	UE_LOG(LogTemp, Error, TEXT("Start reload, ammo: %i"), Ammo);

	GetWorldTimerManager().SetTimer(FullReloadTimerHandle, this, &ATDS_AutoRifle::FinishReloadOnServer, WeaponInfo->ReloadTime);
}

void ATDS_AutoRifle::FinishReloadOnServer_Implementation()
{
	if (!WeaponInfo) return;
	
	Ammo = WeaponInfo->MaxAmmo;
	if (WeaponInfo->bOneInChamber)
	{
		Ammo++;
	}
	bCanShoot = true;
	UE_LOG(LogTemp, Error, TEXT("Finish reload, ammo: %i"), Ammo);
}
