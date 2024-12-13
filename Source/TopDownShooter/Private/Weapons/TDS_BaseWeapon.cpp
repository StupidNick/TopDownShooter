#include "TDS_BaseWeapon.h"

#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"



ATDS_BaseWeapon::ATDS_BaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	RootComponent = Mesh;
}

void ATDS_BaseWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ATDS_BaseWeapon, Ammo, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(ATDS_BaseWeapon, OwnedController, COND_OwnerOnly);
}

void ATDS_BaseWeapon::BeginPlay()
{
	Super::BeginPlay();
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
	if (const auto CurrentOwner = Cast<ACharacter>(GetOwner())) // TODO get controller or find other way to pick mouse hit point
	{
		UE_LOG(LogTemp, Warning, TEXT("Initialize %s"), *CurrentOwner->GetName());
		
		OwnedController = Cast<APlayerController>(CurrentOwner->GetController());
		if (OwnedController)
		{
			UE_LOG(LogTemp, Warning, TEXT("Controller: %s"), *OwnedController->GetName());
		}
	}
}
