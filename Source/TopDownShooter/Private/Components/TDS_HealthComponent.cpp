#include "TDS_HealthComponent.h"
#include "Net/UnrealNetwork.h"



UTDS_HealthComponent::UTDS_HealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicated(true);
}

void UTDS_HealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTDS_HealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UTDS_HealthComponent, Health, COND_OwnerOnly);
}

void UTDS_HealthComponent::SetHealth_Implementation(float InHealth)
{
	Health += InHealth;
}

void UTDS_HealthComponent::OnRep_Health()
{
	//TODO make UI health update
}
