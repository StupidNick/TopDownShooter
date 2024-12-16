#include "TDS_Controllable.h"



void ITDS_Controllable::MousePressed(){}
void ITDS_Controllable::MouseReleased(){}
void ITDS_Controllable::ReloadPressed(){}

void ITDS_Controllable::AddRotation(const FVector& InTargetRotator){}
void ITDS_Controllable::AddMove(FVector2d& InDirection){}

void ITDS_Controllable::SetPlayerController(APlayerController* InController){}
APlayerController* ITDS_Controllable::GetPlayerController(){return nullptr;}
