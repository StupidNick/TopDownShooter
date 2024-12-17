#include "TDS_HealthComponent.h"
#include "Net/UnrealNetwork.h"



UTDS_HealthComponent::UTDS_HealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

float UTDS_HealthComponent::GetHealth()
{
	return Health;
}

void UTDS_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetIsReplicated(true);
}

void UTDS_HealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UTDS_HealthComponent, Health, COND_OwnerOnly);
}

void UTDS_HealthComponent::Initialize_Implementation()
{
	SetHealth(BaseHealth);
}

void UTDS_HealthComponent::SetHealth_Implementation(float InHealth)
{
	Health = InHealth;
	OnHealthChangedEvent.Broadcast(Health);
	UE_LOG(LogTemp, Warning, TEXT("Set health in component"));
}

void UTDS_HealthComponent::TakeDamage_Implementation(float InDamage)
{
	Health = FMath::Max(0.f, Health - InDamage);
	OnHealthChangedEvent.Broadcast(Health);
	UE_LOG(LogTemp, Warning, TEXT("Hit %s health left %f"), *GetOwner()->GetName(), Health);
	if (Health <= 0)
	{
		Death();
	}
}

void UTDS_HealthComponent::Death_Implementation()
{
	OnDead.ExecuteIfBound();
}
