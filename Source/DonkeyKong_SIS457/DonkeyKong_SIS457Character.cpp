// Copyright Epic Games, Inc. All Rights Reserved.

#include "DonkeyKong_SIS457Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "IStrategy.h"
#include "StrategyRun.h"
#include "StrategyFire.h"
#include "StrategyInmunity.h"
//#include "IProjectileAdapter.h"
#include "HieloProjectile.h"
#include "FuegoProjectile.h"

ADonkeyKong_SIS457Character::ADonkeyKong_SIS457Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void ADonkeyKong_SIS457Character::DispararHielo()
{
	FVector SpawnLocation = GetActorLocation() + FVector(0.f, 0.f, 50.f);
	FRotator SpawnRotation = GetActorRotation();
	GetWorld()->SpawnActor<AHieloProjectile>(AHieloProjectile::StaticClass(), SpawnLocation, SpawnRotation);
}

void ADonkeyKong_SIS457Character::DispararFuego()
{
	FVector SpawnLocation = GetActorLocation() + FVector(0.f, 0.f, 50.f);
	FRotator SpawnRotation = GetActorRotation();
	GetWorld()->SpawnActor<AFuegoProjectile>(AFuegoProjectile::StaticClass(), SpawnLocation, SpawnRotation);
}


void ADonkeyKong_SIS457Character::BeginPlay()
{
	Super::BeginPlay();
	run = GetWorld()->SpawnActor<AStrategyRun>(AStrategyRun::StaticClass());
	fire = GetWorld()->SpawnActor<AStrategyFire>(AStrategyFire::StaticClass());
	inmunity = GetWorld()->SpawnActor<AStrategyInmunity>(AStrategyInmunity::StaticClass());

	// Inicializar estrategias 
	ImmobileStrategy = GetWorld()->SpawnActor<AImmobileStrategy>(AImmobileStrategy::StaticClass()); 
	FlyStrategy = GetWorld()->SpawnActor<AFlyStrategy>(AFlyStrategy::StaticClass()); 
	FallStrategy = GetWorld()->SpawnActor<AFallStrategy>(AFallStrategy::StaticClass()); 
	ReturnToOriginStrategy = GetWorld()->SpawnActor<AReturnToOriginStrategy>(AReturnToOriginStrategy::StaticClass()); 
	InitialPosition = GetActorLocation(); // Guardar la posición inicial 
	// Empezar con una estrategia inicial 
	ChangeStrategy();
} 


void ADonkeyKong_SIS457Character::Tick(float DeltaTime) 
{ 
	Super::Tick(DeltaTime); 
	if (CurrentStrategy) 
	{ 
		CurrentStrategy->CambiarHabilidad(); 
	}
}




void ADonkeyKong_SIS457Character::ChangeStrategy()
{
	int32 RandomIndex = FMath::RandRange(0, 3);
    switch (RandomIndex) 
	{ 
	case 0: CurrentStrategy = ImmobileStrategy; 
	break; 
	case 1: CurrentStrategy = FlyStrategy; 
	break; 
	case 2: CurrentStrategy = FallStrategy; 
	break; 
	case 3: CurrentStrategy = ReturnToOriginStrategy; 
	break; 
	default: CurrentStrategy = ImmobileStrategy; 
		break; } 
	// Establecer un temporizador para cambiar de estrategia cada 5 segundos 
	GetWorldTimerManager().SetTimer(StateChangeTimerHandle, this, &ADonkeyKong_SIS457Character::ChangeStrategy, 5.0f, false);
}



void ADonkeyKong_SIS457Character::Habilidad1()
{
	EstablecerEstrategia(run);
	// Increase character speed by 75%
	GetCharacterMovement()->MaxWalkSpeed *= 1.75f;

	// Set a timer to reset the speed after 5 seconds
	GetWorldTimerManager().SetTimer(SpeedTimerHandle, this, &ADonkeyKong_SIS457Character::ResetSpeed, 5.0f, false);

}

void ADonkeyKong_SIS457Character::Habilidad2()
{
	EstablecerEstrategia(fire);
	// Double jump height
	GetCharacterMovement()->JumpZVelocity *= 2.0f;
	// Set a timer to reset the jump height after 5 seconds 
	GetWorldTimerManager().SetTimer(JumpTimerHandle, this, &ADonkeyKong_SIS457Character::ResetJumpHeight, 5.0f, false);
}

void ADonkeyKong_SIS457Character::Habilidad3()
{
	EstablecerEstrategia(inmunity);
	// Make character invisible 
	GetMesh()->SetVisibility(false);
	// Set a timer to reset the visibility after 2 seconds 
	GetWorldTimerManager().SetTimer(InvisibilityTimerHandle, this, &ADonkeyKong_SIS457Character::ResetVisibility, 2.0f, false);
}

void ADonkeyKong_SIS457Character::OnTimerReachedZero()
{
	SetActorLocation(PositionObjetivo);
}

void ADonkeyKong_SIS457Character::SetPositionObjetivo(FVector NuevaPosicion)
{
	PositionObjetivo = NuevaPosicion;
}

void ADonkeyKong_SIS457Character::EstablecerEstrategia(AActor* _strategys)
{
	habilidades = Cast<IIStrategy>(_strategys);
	if (habilidades) {
		habilidades->CambiarHabilidad();
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
			FString::Printf(TEXT("No hay una habilidad establecida")));
	}
}

void ADonkeyKong_SIS457Character::ResetSpeed()
{
	// Reset character speed to original
	GetCharacterMovement()->MaxWalkSpeed /= 1.75f;
}

void ADonkeyKong_SIS457Character::ResetJumpHeight()
{
	// Reset jump height to original 
	GetCharacterMovement()->JumpZVelocity /= 2.0f;
}

void ADonkeyKong_SIS457Character::ResetVisibility()
{
	// Reset visibility to original
	GetMesh()->SetVisibility(true);
}


//////////////////////////////////////////////////////////////////////////
// Input

void ADonkeyKong_SIS457Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("J1", IE_Pressed, this, &ADonkeyKong_SIS457Character::Habilidad1);
	PlayerInputComponent->BindAction("K2", IE_Pressed, this, &ADonkeyKong_SIS457Character::Habilidad2);
	PlayerInputComponent->BindAction("L3", IE_Pressed, this, &ADonkeyKong_SIS457Character::Habilidad3);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADonkeyKong_SIS457Character::MoveRight);
	PlayerInputComponent->BindAction("DispararHielo", IE_Pressed, this, &ADonkeyKong_SIS457Character::DispararHielo);
	PlayerInputComponent->BindAction("DispararFuego", IE_Pressed, this, &ADonkeyKong_SIS457Character::DispararFuego);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ADonkeyKong_SIS457Character::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ADonkeyKong_SIS457Character::TouchStopped);
}

void ADonkeyKong_SIS457Character::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}

void ADonkeyKong_SIS457Character::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void ADonkeyKong_SIS457Character::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}
