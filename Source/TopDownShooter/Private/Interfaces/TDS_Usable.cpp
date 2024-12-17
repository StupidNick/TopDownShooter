#include "..\..\Public\Interfaces\TDS_Usable.h"

void ITDS_Usable::OnLeftMouseButtonPressed() {}
void ITDS_Usable::OnLeftMouseButtonReleased() {}
void ITDS_Usable::OnRightMouseButtonPressed(){}
void ITDS_Usable::OnRightMouseButtonReleased(){}
void ITDS_Usable::OnReloadPressed(){}
void ITDS_Usable::Detach(){}

bool ITDS_Usable::NeedAmmoCounter(){return true;}
int32 ITDS_Usable::GetAmmo(){return 0;}
