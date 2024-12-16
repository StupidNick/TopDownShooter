#include "TDS_Character.h"
#include "TDS_EquipmentComponent.h"
#include "TDS_HealthComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"


ATDS_Character::ATDS_Character()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;

	EquipmentComponent = CreateDefaultSubobject<UTDS_EquipmentComponent>(TEXT("EquipmentComponent"));
	HealthComponent = CreateDefaultSubobject<UTDS_HealthComponent>(TEXT("HealthComponent"));

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	bReplicates = true;
}

void ATDS_Character::BeginPlay()
{
	Super::BeginPlay();

	Initialize();
}

void ATDS_Character::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ATDS_Character, CurrentPlayerController, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(ATDS_Character, bIsAlive, COND_OwnerOnly);
}

float ATDS_Character::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	if (!bIsAlive || !HealthComponent || DamageCauser == this) return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	HealthComponent->TakeDamage(DamageAmount);
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ATDS_Character::AddMove(FVector2d& InDirection)
{
	ITDS_Controllable::AddMove(InDirection);

	InDirection.X = FMath::Min(InDirection.X, 1.);
	InDirection.Y = FMath::Min(InDirection.Y, 1.);
	
	if (const auto MovementComponent = GetMovementComponent())
	{
		MovementComponent->AddInputVector(FVector(InDirection.X, InDirection.Y, 0));
	}
}

void ATDS_Character::AddRotation_Implementation(const FVector& InTargetLocation)
{
	if (!bIsAlive) return;
	
	ITDS_Controllable::AddRotation(InTargetLocation);

	const FRotator InTargetRotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), InTargetLocation);

	const FRotator CurrentRotator = GetActorRotation();
	SetActorRotation(FRotator(CurrentRotator.Pitch, InTargetRotator.Yaw, CurrentRotator.Roll));
}

void ATDS_Character::MousePressed()
{
	if (!bIsAlive) return;
	
	ITDS_Controllable::MousePressed();

	if (!EquipmentComponent) return;

	EquipmentComponent->OnMousePressed();
}

void ATDS_Character::MouseReleased()
{
	if (!bIsAlive) return;
	
	ITDS_Controllable::MouseReleased();

	if (!EquipmentComponent) return;

	EquipmentComponent->OnMouseReleased();
}

UCameraComponent* ATDS_Character::GetCamera() const 
{
	return TopDownCameraComponent;
}

void ATDS_Character::SetPlayerController_Implementation(APlayerController* InController)
{
	CurrentPlayerController = InController;
}

APlayerController* ATDS_Character::GetPlayerController()
{
	return CurrentPlayerController;
}

void ATDS_Character::Initialize()
{
	if (HealthComponent)
	{
		HealthComponent->OnDead.BindUObject(this, &ATDS_Character::OnPlayerDeadOnServer_Implementation);
	}
}

void ATDS_Character::OnPlayerDeadOnServer_Implementation()
{
	if (!CurrentPlayerController || !GetMovementComponent() || !EquipmentComponent) return;

	OnPlayerDeadOnClient();
	GetMovementComponent()->Deactivate();
	MouseReleased();
	bIsAlive = false;
	
	GetCapsuleComponent()->SetCollisionProfileName(FName("NoCollision"));
	EquipmentComponent->DetachObjectInHand();

	FTimerHandle DestroyTimerHandler;
	GetWorldTimerManager().SetTimer(DestroyTimerHandler, this, &ATDS_Character::DestroyCharacter, 10.f);

	OnPLayerDead.ExecuteIfBound();
}

void ATDS_Character::OnPlayerDeadOnClient_Implementation()
{
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName(RagdollCollisionProfileName.Name, true);
}

void ATDS_Character::DestroyCharacter_Implementation()
{
	Destroy();
}
