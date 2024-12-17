#pragma once

#include "CoreMinimal.h"
#include "TDS_BaseWeapon.h"
#include "TDS_Usable.h"
#include "TDS_AutoRifle.generated.h"



UCLASS()
class TOPDOWNSHOOTER_API ATDS_AutoRifle : public ATDS_BaseWeapon, public ITDS_Usable
{
	GENERATED_BODY()

public:
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void Initialize() override;
	
	virtual void OnLeftMouseButtonPressed() override;
	virtual void OnLeftMouseButtonReleased() override;

	virtual void OnRightMouseButtonPressed() override;
	virtual void OnRightMouseButtonReleased() override;
	
	virtual void OnReloadPressed() override;

	virtual void Detach() override;

	virtual bool NeedAmmoCounter();
	virtual int32 GetAmmo();

protected:

	void StartFire();
	UFUNCTION(Client, Reliable)
	void Fire();
	
	UFUNCTION(Server, Reliable)
	void StartFireOnServer();
	UFUNCTION(Server, Reliable)
	void FireOnServer(FVector InTargetLocation);
	UFUNCTION(Server, Reliable)
	void StopFireOnServer();
	UFUNCTION(Server, Reliable)
	void FireAgainOnServer();

	UFUNCTION(Server, Reliable)
	void StartReloadOnServer();
	UFUNCTION(Server, Reliable)
	void FinishReloadOnServer();

	// Debug
	UFUNCTION(NetMulticast, Reliable)
	void DrawDebugFire(const FVector& InStartLocation, const FVector& InEndLocation);

public:

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ECollisionChannel> ShootCollisionChannel;

protected:
	
	FTimerHandle ReloadBetweenShotsTimerHandle;
	FTimerHandle FullReloadTimerHandle;
	
	bool bIsFiring = false;
};
