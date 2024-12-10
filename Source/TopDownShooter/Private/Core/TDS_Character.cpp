#include "TDS_Character.h"
#include "TDS_EquipmentComponent.h"
#include "TDS_HealthComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"



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

	SetReplicates(true);
}

void ATDS_Character::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority() && HealthComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Pass health: %d"), 100);
		HealthComponent->SetHealth(100.f);
	}
}

void ATDS_Character::Move(FVector2d InDirection) const
{
	InDirection.X = FMath::Max(InDirection.X, 1.);
	InDirection.Y = FMath::Max(InDirection.Y, 1.);
	
	if (const auto MovementComponent = GetMovementComponent())
	{
		MovementComponent->AddInputVector(FVector(InDirection.X, InDirection.Y, 0));
	}
}

void ATDS_Character::UpdateRotation_Implementation(const FRotator& InTargetRotator)
{
	const FRotator CurrentRotator = GetActorRotation();
	SetActorRotation(FRotator(CurrentRotator.Pitch, InTargetRotator.Yaw, CurrentRotator.Roll));
}

void ATDS_Character::OnMousePressed_Implementation()
{
	if (!EquipmentComponent) return;

	HealthComponent->SetHealth(200.f);
	EquipmentComponent->OnMousePressed();
}

void ATDS_Character::OnMouseReleased_Implementation()
{
	if (!EquipmentComponent) return;

	EquipmentComponent->OnMouseReleased();
}

UCameraComponent* ATDS_Character::GetCamera() const 
{
	return TopDownCameraComponent;
}
