#include "TDS_EquipmentComponent.h"

#include "TDS_BaseWeapon.h"
#include "TDS_Character.h"
#include "TDS_Usable.h"
#include "Net/UnrealNetwork.h"


UTDS_EquipmentComponent::UTDS_EquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTDS_EquipmentComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UTDS_EquipmentComponent, ObjectInHands, COND_OwnerOnly);
}

void UTDS_EquipmentComponent::AddWeapon_Implementation(TSubclassOf<ATDS_BaseWeapon> InWeaponClass)
{
	if (!GetWorld()) return;

	const auto Weapon = GetWorld()->SpawnActor<ATDS_BaseWeapon>(InWeaponClass);
	if (!Weapon) return;

	Weapon->SetOwner(GetOwner());
	SetObjectInHand(Weapon);
	Weapon->Initialize();
}

void UTDS_EquipmentComponent::SetObjectInHand(AActor* InObject)
{
	if (!InObject) return;
	
	if (InObject->Implements<UTDS_Usable>())
	{
		ObjectInHands = TScriptInterface<ITDS_Usable>(InObject);
	}
	if (const auto Character = Cast<ACharacter>(GetOwner()))
	{
		InObject->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::KeepWorldTransform, WeaponSocketName);
		InObject->SetActorRelativeLocation(FVector(0.f, 0.f, 0.f));
		InObject->SetActorRotation(FRotator::ZeroRotator);
	}
}

void UTDS_EquipmentComponent::OnMousePressed() const
{
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
