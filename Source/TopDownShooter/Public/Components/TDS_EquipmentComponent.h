#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types.h"
#include "TDS_EquipmentComponent.generated.h"


class ATDS_BaseWeapon;
class ITDS_Usable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNSHOOTER_API UTDS_EquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTDS_EquipmentComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Server, Reliable)
	void AddWeapon(TSubclassOf<ATDS_BaseWeapon> InWeaponClass);

	void DetachObjectInHand();

	void OnMousePressed() const;
	void OnMouseReleased() const;

	void OnReloadPressed() const;

protected:

	void SetObjectInHand(AActor* InObject);

	UFUNCTION()
	void OnRep_ObjectInHands();

public:

	FFloatDelegate OnAmmoChangedEvent;
	FUsableDelegate OnObjectInHandsChangedDelegate;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponSocketName;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ATDS_BaseWeapon> DefaultWeapon;

	UPROPERTY(ReplicatedUsing=OnRep_ObjectInHands)
	TScriptInterface<ITDS_Usable> ObjectInHands = nullptr;
};
