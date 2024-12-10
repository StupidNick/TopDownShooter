#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDS_HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNSHOOTER_API UTDS_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTDS_HealthComponent();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Server, Reliable)
	void SetHealth(float InHealth);
	UFUNCTION(Server, Reliable)
	void TakeDamage(float InDamage);
	
	UFUNCTION(Server, Reliable)
	void Death();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnRep_Health();

public:
	
	FSimpleDelegate OnDead;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float BaseHealth;

private:

	UPROPERTY(ReplicatedUsing=OnRep_Health)
	float Health;
};
