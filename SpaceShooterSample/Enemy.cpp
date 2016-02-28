// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShooterSample.h"
#include "Enemy.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh")); 
	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision Component"));
	ExplosionFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Explosion FX"));
	ExplosionSound = CreateDefaultSubobject<UAudioComponent>(TEXT("Explosion Sound"));



	StaticMesh->AttachTo(RootComponent);
	CollisionComponent->AttachTo(RootComponent);
	ExplosionFX->AttachTo(RootComponent);
	ExplosionSound->AttachTo(RootComponent);



	OnActorBeginOverlap.AddDynamic(this, &AEnemy::OnBeginOverlap);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	this->AIControllerClass = AEnemyController::StaticClass();

	//If Current Velocity is left unset give a sensible default value

	TotalTime = 0.0f;
	TimeSinceLastShot = 0.0f;
	bHit = false;
	bDestroy = false;
	fDestroyTimer = 1.0f;

	ExplosionFX->Deactivate();
	ExplosionSound->Deactivate();
	
	
}

// Called every frame
void AEnemy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	//Move from wherever you spawn strait to the left past the player
	TotalTime += DeltaTime;
	TimeSinceLastShot += DeltaTime;

	FActorSpawnParameters Params = {};
	Params.Owner = this;
	FRotator CurrentRotation = this->GetActorRotation();
	FVector CurrentLocation = this->GetActorLocation();
	CurrentLocation.Y += FMath::Sin(TotalTime * 5) * 3;
	this->SetActorLocation(CurrentLocation - (CurrentVelocity * DeltaTime));
	
	if (TimeSinceLastShot >= 1.0f && !bHit)
	{
		GetWorld()->SpawnActor(EnemyProjectile, &CurrentLocation, &CurrentRotation, Params);
		TimeSinceLastShot = 0.0f;
	}

	if (bHit == true)
	{
		StaticMesh->SetVisibility(false);
		this->SetActorEnableCollision(false);
		ExplosionFX->Activate();
		ExplosionSound->Activate();
		fDestroyTimer -= DeltaTime;
	}
	if (fDestroyTimer <= 0.0f)
		this->Destroy();

	if (bDestroy)
		this->Destroy();

	
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void AEnemy::OnBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("Bounds"))
		bDestroy = true;
	if (OtherActor->ActorHasTag("Projectile"))
		bHit = true;
	if (OtherActor->ActorHasTag("Asteroid"))
		bHit = true;

}