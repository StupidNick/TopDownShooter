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

protected:

	UFUNCTION(Server, Reliable)
	void StartFire();
	UFUNCTION(Server, Reliable)
	void Fire();
	UFUNCTION(Server, Reliable)
	void StopFire();

	UFUNCTION(Server, Reliable)
	void FireAgain();

protected:
	
	FTimerHandle ReloadBetweenShotsTimerHandle;
	
	bool bIsFiring = false;
};
