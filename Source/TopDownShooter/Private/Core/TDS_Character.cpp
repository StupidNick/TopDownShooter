#include "TDS_Character.h"
#include "TDS_EquipmentComponent.h"
#include "TDS_HealthComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"


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
	ITDS_Controllable::AddRotation(InTargetLocation);

	const FRotator InTargetRotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), InTargetLocation);

	const FRotator CurrentRotator = GetActorRotation();
	SetActorRotation(FRotator(CurrentRotator.Pitch, InTargetRotator.Yaw, CurrentRotator.Roll));
}

void ATDS_Character::MousePressed()
{
	ITDS_Controllable::MousePressed();

	if (!EquipmentComponent) return;

	EquipmentComponent->OnMousePressed();
}

void ATDS_Character::MouseReleased()
{
	ITDS_Controllable::MouseReleased();

	if (!EquipmentComponent) return;

	EquipmentComponent->OnMouseReleased();
}

UCameraComponent* ATDS_Character::GetCamera() const 
{
	return TopDownCameraComponent;
}

void ATDS_Character::Initialize()
{
	if (HealthComponent)
	{
		HealthComponent->OnDead.BindUObject(this, &ATDS_Character::OnPlayerDead_Implementation);
	}
}

void ATDS_Character::OnPlayerDead_Implementation()
{
	// UnPossessed();
}
