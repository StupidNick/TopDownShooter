#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDS_EquipmentComponent.generated.h"


class ATDS_BaseWeapon;
class ITDS_Usable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNSHOOTER_API UTDS_EquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTDS_EquipmentComponent();

	UFUNCTION(Server, Reliable)
	void AddWeapon(TSubclassOf<ATDS_BaseWeapon> InWeaponClass);

	// UFUNCTION(Server, Reliable)
	void GetObjectInHand(ITDS_Usable* InObject);

	void OnMousePressed() const;
	void OnMouseReleased() const;

protected:
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATDS_BaseWeapon> DefaultWeapon;
	
	ITDS_Usable* ObjectInHands = nullptr;
};
