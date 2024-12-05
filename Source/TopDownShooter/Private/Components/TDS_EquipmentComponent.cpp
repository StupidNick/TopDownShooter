#include "TDS_EquipmentComponent.h"
#include "TDS_Clickable.h"



UTDS_EquipmentComponent::UTDS_EquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTDS_EquipmentComponent::OnMousePressed() const
{
	if (!ObjectInHands) return;

	ObjectInHands->OnPressed();
}

void UTDS_EquipmentComponent::OnMouseReleased() const
{
	if (!ObjectInHands) return;

	ObjectInHands->OnReleased();
}

void UTDS_EquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
}
