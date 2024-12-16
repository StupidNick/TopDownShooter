#include "TDS_GameMode.h"
#include "GameFramework/Character.h"



ATDS_GameMode::ATDS_GameMode()
{
}

ACharacter* ATDS_GameMode::CreateCharacter(APlayerController* InPlayerController)
{
	return GetWorld()->SpawnActor<ACharacter>(DefaultPawnClass, FindPlayerStart(InPlayerController)->GetActorLocation(), FRotator::ZeroRotator);
}
