#pragma once

class ITDS_Usable;

DECLARE_MULTICAST_DELEGATE_OneParam(FFloatDelegate, float)
DECLARE_MULTICAST_DELEGATE_OneParam(FUsableDelegate, const TScriptInterface<ITDS_Usable>&)