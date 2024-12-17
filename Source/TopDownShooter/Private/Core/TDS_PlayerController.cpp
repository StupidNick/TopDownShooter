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

void ATDS_PlayerController::OnPlayerDead()
{
	UnPossess();
	CurrentCharacter = nullptr;

	FTimerHandle DestroyTimerHandler;
	GetWorldTimerManager().SetTimer(DestroyTimerHandler, this, &ATDS_PlayerController::Respawn_Implementation, 2.f);
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
		CurrentCharacter->OnHealthChanged.AddUObject(this, &ATDS_PlayerController::OnHealthChanged);
		CurrentCharacter->OnAmmoChanged.AddUObject(this, &ATDS_PlayerController::OnAmmoChanged);
	}
}

void ATDS_PlayerController::OnRep_CurrentCharacter()
{
	if (!CurrentCharacter)
	{
		if (HUD)
		{
			HUD->RemoveMainWidget();
		}
		return;
	}
	
	HUD = Cast<ATDS_GameHUD>(GetHUD());
	if (!HUD) return;

	HUD->Initialize(this);
	HUD->CreateMainWidget();
	
	CurrentCharacter->OnObjectInHandsChanged.AddUObject(this, &ATDS_PlayerController::OnObjectInHandsChanged);
	CurrentCharacter->Initialize();
}

void ATDS_PlayerController::OnObjectInHandsChanged_Implementation(const TScriptInterface<ITDS_Usable>& InObject)
{
	OnObjectInHandsChangedEvent.Broadcast(InObject);
}

void ATDS_PlayerController::OnHealthChanged_Implementation(float InHealth)
{
	OnHealthChangedEvent.Broadcast(InHealth);
}

void ATDS_PlayerController::OnAmmoChanged_Implementation(float InAmmo)
{
	OnAmmoChangedEvent.Broadcast(InAmmo);
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
		
		EnhancedInputComponent->BindAction(EscapeAction, ETriggerEvent::Triggered, this, &ATDS_PlayerController::OnEscapePressed);
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
	if (!CurrentCharacter) return;

	CurrentCharacter->ReloadPressed();
}

void ATDS_PlayerController::OnMoveForwardPressed(const FInputActionValue& Input)
{
	if (!CurrentCharacter) return;
	
	FVector2d MovingVector = Input.Get<FVector2d>();
	CurrentCharacter->AddMove(MovingVector);
}

void ATDS_PlayerController::OnEscapePressed()
{
	if (!HUD) return;

	HUD->CreatePauseMenuWidget();
}
