#include "TDS_Character.h"
#include "UObject/ConstructorHelpers.h"
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

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ATDS_Character::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void ATDS_Character::Move(FVector2d InDirection) const
{
	if (InDirection.X > 1)
	{
		InDirection.X = 1;
	}
	if (InDirection.Y > 1)
	{
		InDirection.Y = 1;
	}
	
	if (const auto MovementComponent = GetMovementComponent())
	{
		MovementComponent->AddInputVector(FVector(InDirection.X, InDirection.Y, 0));
	}
}

void ATDS_Character::UpdateRotation(const FVector& InMousePosition)
{
	UE_LOG(LogTemp, Error, TEXT("Current location: %s"), *InMousePosition.ToString()); //Think about rotation character
	const FRotator RotatorToMousePosition = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), InMousePosition);
	const FRotator CurrentRotator = GetActorRotation();
	SetActorRotation(FRotator(CurrentRotator.Pitch, CurrentRotator.Yaw, RotatorToMousePosition.Roll));
}
