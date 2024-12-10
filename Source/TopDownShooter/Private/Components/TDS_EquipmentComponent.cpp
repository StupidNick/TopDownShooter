#include "TDS_EquipmentComponent.h"

#include "TDS_BaseWeapon.h"
#include "TDS_Usable.h"



UTDS_EquipmentComponent::UTDS_EquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// void UTDS_EquipmentComponent::GetObjectInHand_Implementation(ITDS_Usable* InObject)
// {
	
// }

void UTDS_EquipmentComponent::AddWeapon_Implementation(TSubclassOf<ATDS_BaseWeapon> InWeaponClass)
{
	if (!GetWorld()) return;

	const FActorSpawnParameters SpawnParams;
	// FVector* SpawnLocation = nullptr;
	// *SpawnLocation = GetOwner()->GetActorLocation();
	auto Weapon = GetWorld()->SpawnActor<ATDS_BaseWeapon>(InWeaponClass, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation());
	if (!Weapon) return;

	UE_LOG(LogTemp, Error, TEXT("Spawned weapon"));
	GetObjectInHand(Cast<ITDS_Usable>(Weapon));
}

void UTDS_EquipmentComponent::GetObjectInHand(ITDS_Usable* InObject)
{
	if (!InObject) return;
	
	ObjectInHands = InObject;
	UE_LOG(LogTemp, Error, TEXT("Weapon in hands"));
}

void UTDS_EquipmentComponent::OnMousePressed() const
{
	UE_LOG(LogTemp, Warning, TEXT("Mouse pressed in Equipment component"));
	if (!ObjectInHands) return;

	
	ObjectInHands->OnLeftMouseButtonPressed();
}

void UTDS_EquipmentComponent::OnMouseReleased() const
{
	if (!ObjectInHands) return;

	ObjectInHands->OnLeftMouseButtonReleased();
}

void UTDS_EquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner()->HasAuthority())
	{
		AddWeapon(DefaultWeapon);
	}
}
