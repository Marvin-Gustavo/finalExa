// Fill out your copyright notice in the Description page of Project Settings.


#include "HieloProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AHieloProjectile::AHieloProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/Shapes/Shape_Torus.Shape_Torus'"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));	
	Mesh->SetStaticMesh(MeshAsset.Object);
	RootComponent = Mesh;

	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->InitialSpeed = 100.0f;
	MovementComponent->MaxSpeed = 100.0f;
}

// Called when the game starts or when spawned
void AHieloProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHieloProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHieloProjectile::Disparar()
{
	UE_LOG(LogTemp, Warning, TEXT("Disparando Projectile Hielo"));
}

