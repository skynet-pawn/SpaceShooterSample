// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooterSample.h"
#include "Hazard.h"
#include "SSS_GameMode.h"

// Sets default values
AHazard::AHazard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
	AsteroidExplosionSound = CreateDefaultSubobject<UAudioComponent>(TEXT("AsteroidExplosionSound"));
	AsteroidExplosionFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("AsteroidExplosionFX"));

	StaticMesh->AttachTo(RootComponent);
	CollisionComponent->AttachTo(RootComponent);
	AsteroidExplosionSound->AttachTo(RootComponent);
	AsteroidExplosionFX->AttachTo(RootComponent);
	
	SpawnXVelocity = -250.0f;
	SpawnYVelocity = 0.0f;

	SelfDestructTimer = 1.0f;

	bHit = false;
	AsteroidExplosionSound->Activate(false);

	OnActorBeginOverlap.AddDynamic(this, &AHazard::OnBeginOverlap);

	

}

// Called when the game starts or when spawned
void AHazard::BeginPlay()
{
	Super::BeginPlay();
	InitialRotation = 0.0f;
	InitialXLocation = 1500.0f;
	InitialYLocation = FMath::RandRange(-500, 500);
	bHit = false;

	RandSize = FMath::RandRange(3, 8);
	this->SetActorScale3D(FVector(RandSize, RandSize, RandSize));

	AsteroidExplosionSound->Deactivate();
	AsteroidExplosionFX->Deactivate();
	AsteroidExplosionSound->bStopWhenOwnerDestroyed = false;

}

// Called every frame
void AHazard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	check(this != nullptr);

	InitialRotation += DeltaTime;
	InitialXLocation += (DeltaTime * SpawnXVelocity);
	InitialYLocation += (DeltaTime * SpawnYVelocity);



	this->SetActorRotation(FRotator(InitialRotation * 100.0f, InitialRotation * 50.0f, 0.0f));
	this->SetActorLocation(FVector(InitialXLocation, InitialYLocation, 0.0f));

	if(bStartDestroyTimer)
		SelfDestructTimer -= DeltaTime;


	if (bHit)
	{
		bHit = false;
		bStartDestroyTimer = true;

		if (this->GetActorScale3D().X > 6.0f)
		{
			SpawnChildren(3);
		}
		AsteroidExplosionFX->Activate();
		AsteroidExplosionFX->SetWorldLocation(this->GetActorLocation());
		AsteroidExplosionFX->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
		AsteroidExplosionSound->Activate();
		AsteroidExplosionSound->Play();

		this->StaticMesh->SetVisibility(false);
		this->SetActorEnableCollision(false);
	}
	if(SelfDestructTimer <= 0.0f)
		this->Destroy();
		
		
}

void AHazard::OnBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("Projectile"))
	{
		bHit = true;
	}

	if (OtherActor->ActorHasTag("Bounds"))
		SelfDestructTimer = 0.0f;
}

void AHazard::SpawnChildren(int32 NumChildren)
{
	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	for (int i = 0; i < NumChildren; i++)
	{
		if (ChildSpawn != nullptr)
		{
			AHazard* NewHazard = Cast<AHazard>(GetWorld()->SpawnActor(ChildSpawn, new FVector(this->GetActorLocation()), new FRotator(this->GetActorRotation()), Params));
			NewHazard->InitialXLocation = this->GetActorLocation().X;
			NewHazard->InitialYLocation = this->GetActorLocation().Y;
			NewHazard->SetHazardVelocity(FVector(FMath::RandRange(-250, -100), FMath::RandRange(-50, 50), 0.0f));
			NewHazard->SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));
			NewHazard->SetActorEnableCollision(true);
			NewHazard->StaticMesh->SetVisibility(true);
		}
	}
	
}

void AHazard::SetHazardVelocity(FVector NewVelocity)
{
	SpawnXVelocity = NewVelocity.X;
	SpawnYVelocity = NewVelocity.Y;
}