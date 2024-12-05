#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDS_EquipmentComponent.generated.h"


class ITDS_Clickable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNSHOOTER_API UTDS_EquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTDS_EquipmentComponent();

	void OnMousePressed() const;
	void OnMouseReleased() const;

protected:
	virtual void BeginPlay() override;

public:	
	
	ITDS_Clickable* ObjectInHands = nullptr;
		
};
