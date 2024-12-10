#include "TDS_HealthComponent.h"
#include "Net/UnrealNetwork.h"



UTDS_HealthComponent::UTDS_HealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicated(true);
}

void UTDS_HealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// DOREPLIFETIME(UTDS_HealthComponent, Health);
	DOREPLIFETIME_CONDITION(UTDS_HealthComponent, Health, COND_OwnerOnly);
}

void UTDS_HealthComponent::SetHealth(float InHealth)
{
	Health = InHealth;
	UE_LOG(LogTemp, Error, TEXT("Client: %s, Set health: %s"), *GetOwner()->GetName(), *FString::FormatAsNumber(Health));
}

void UTDS_HealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTDS_HealthComponent::OnRep_Health()
{
	UE_LOG(LogTemp, Warning, TEXT("Client: %s, New health: %s"), *GetOwner()->GetName(), *FString::FormatAsNumber(Health));
	//TODO make UI health update
}
