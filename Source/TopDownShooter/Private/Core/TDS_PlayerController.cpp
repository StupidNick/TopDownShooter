#include "TDS_PlayerController.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TDS_Character.h"
#include "TDS_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"


ATDS_PlayerController::ATDS_PlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ATDS_PlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ATDS_PlayerController, CurrentCharacter, COND_OwnerOnly);
}

void ATDS_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	// CurrentCharacter = Cast<ITDS_Controllable>(GetCharacter());
	// UE_LOG(LogTemp, Error, TEXT("Current character: %s"), GetCharacter());
	// if (CurrentCharacter)
	// {
	// 	CurrentCharacter->SetPlayerController(this);
	// 	UE_LOG(LogTemp, Error, TEXT("Subscribe on event PC"));
	// 	CurrentCharacter->OnPLayerDead.BindUObject(this, &ATDS_PlayerController::OnPlayerDead);
	// }
}

void ATDS_PlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!HasAuthority())
	{
		
	}
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

void ATDS_PlayerController::OnPlayerDead()
{
	UnPossess();
	CurrentCharacter = nullptr;

	FTimerHandle DestroyTimerHandler;
	GetWorldTimerManager().SetTimer(DestroyTimerHandler, this, &ATDS_PlayerController::Respawn_Implementation, 10.f);
}

void ATDS_PlayerController::Respawn_Implementation()
{
	if (const auto GameMode = Cast<ATDS_GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		const auto NewCharacter = GameMode->CreateCharacter(this);
		if (!NewCharacter) return;

		Possess(NewCharacter);
	}
}

void ATDS_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	CurrentCharacter = TScriptInterface<ITDS_Controllable>(GetCharacter());
	if (CurrentCharacter)
	{
		CurrentCharacter->SetPlayerController(this);
		CurrentCharacter->OnPLayerDead.BindUObject(this, &ATDS_PlayerController::OnPlayerDead);
	}
}

void ATDS_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MouseClickAction, ETriggerEvent::Started, this, &ATDS_PlayerController::OnMousePressed);
		EnhancedInputComponent->BindAction(MouseClickAction, ETriggerEvent::Completed, this, &ATDS_PlayerController::OnMouseReleased);
		
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Triggered, this, &ATDS_PlayerController::OnReloadPressed);
		
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATDS_PlayerController::OnMoveForwardPressed);
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

void ATDS_PlayerController::OnReloadPressed()
{
	UE_LOG(LogTemp, Error, TEXT("Reload in controller"));
	if (!CurrentCharacter) return;

	UE_LOG(LogTemp, Error, TEXT("Reload in controller to character"));
	CurrentCharacter->ReloadPressed();
}

void ATDS_PlayerController::OnMoveForwardPressed(const FInputActionValue& Input)
{
	if (!CurrentCharacter) return;
	
	FVector2d MovingVector = Input.Get<FVector2d>();
	CurrentCharacter->AddMove(MovingVector);
}
