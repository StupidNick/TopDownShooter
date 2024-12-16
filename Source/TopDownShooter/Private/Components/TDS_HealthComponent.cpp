#include "TDS_HealthComponent.h"
#include "Net/UnrealNetwork.h"



UTDS_HealthComponent::UTDS_HealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTDS_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetIsReplicated(true);
	if (GetOwner()->HasAuthority())
	{
		SetHealth(BaseHealth);
	}
}

void UTDS_HealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UTDS_HealthComponent, Health, COND_OwnerOnly);
}

void UTDS_HealthComponent::SetHealth_Implementation(float InHealth)
{
	Health = InHealth;
}

void UTDS_HealthComponent::TakeDamage_Implementation(float InDamage)
{
	Health -= InDamage;
	UE_LOG(LogTemp, Warning, TEXT("Hit %s health left %f"), *GetOwner()->GetName(), Health);
	if (Health <= 0)
	{
		Death();
	}
}

void UTDS_HealthComponent::Death_Implementation()
{
	OnDead.ExecuteIfBound();
	// TODO make character ragdoll
	// TODO Unpossess player controller
	// TODO Make UI
}

void UTDS_HealthComponent::OnRep_Health()
{
	//TODO make UI health update
}
