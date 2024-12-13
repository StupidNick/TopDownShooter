#include "TDS_PlayerController.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TDS_Character.h"



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
	CurrentCharacter = Cast<ITDS_Controllable>(GetCharacter());
}

void ATDS_PlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateCharacterRotation();
}

void ATDS_PlayerController::UpdateCharacterRotation() const
{
	if (!CurrentCharacter || !GetWorld()) return;
	
	FVector WorldLocation, WorldDirection;
	DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	FHitResult Result;
	GetWorld()->LineTraceSingleByChannel(Result, WorldLocation, WorldLocation + WorldDirection * 5000, MouseTraceChanel);

	if (Result.bBlockingHit)
	{
		CurrentCharacter->AddRotation(Result.Location);
	}
}

void ATDS_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MouseClickAction, ETriggerEvent::Started, this, &ATDS_PlayerController::OnMousePressed);
		EnhancedInputComponent->BindAction(MouseClickAction, ETriggerEvent::Completed, this, &ATDS_PlayerController::OnMouseReleased);
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &ATDS_PlayerController::OnMoveForwardPressed);
	}
}

void ATDS_PlayerController::OnMousePressed()
{
	if (!CurrentCharacter) return;

	CurrentCharacter->MousePressed();
}

void ATDS_PlayerController::OnMouseReleased()
{
	if (!CurrentCharacter) return;

	CurrentCharacter->MouseReleased();
}

void ATDS_PlayerController::OnMoveForwardPressed(const FInputActionValue& Input)
{
	if (!CurrentCharacter) return;
	
	FVector2d MovingVector = Input.Get<FVector2d>();
	CurrentCharacter->AddMove(MovingVector);
}
