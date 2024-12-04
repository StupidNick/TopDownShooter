#include "TDS_PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TDS_Character.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

ATDS_PlayerController::ATDS_PlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ATDS_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	CurrentCharacter = Cast<ATDS_Character>(GetCharacter());
}

void ATDS_PlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateCharacterRotation();
}

void ATDS_PlayerController::UpdateCharacterRotation()
{
	if (!CurrentCharacter) return;
	
	FVector WorldLocation, WorldDirection;
	DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
	CurrentCharacter->UpdateRotation(WorldLocation);
}

void ATDS_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Started, this, &ATDS_PlayerController::OnClick);
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &ATDS_PlayerController::OnMoveForwardPressed);
	}
}

void ATDS_PlayerController::OnClick()
{
	
}

void ATDS_PlayerController::OnMoveForwardPressed(const FInputActionValue& Input)
{
	if (!CurrentCharacter) return;
	
	const FVector2d MovingVector = Input.Get<FVector2d>();
	CurrentCharacter->Move(MovingVector);
}

void ATDS_PlayerController::OnInputStarted()
{
	StopMovement();
}
