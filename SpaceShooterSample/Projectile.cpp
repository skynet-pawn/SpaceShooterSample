// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooterSample.h"
#include "SSS_Player.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	PlaneComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneComponent"));
	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));

	
	CapsuleCollision->AttachTo(RootComponent);
	PlaneComponent->AttachTo(RootComponent);
	ProjectileSpeed = 0.0f;
	bDestroy = false;
	bHit = false;

	//Overlap Events
	OnActorBeginOverlap.AddDynamic(this, &AProjectile::OnBeginOverlap);
	
	
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CurrLocation = this->GetActorLocation();
}

// Called every frame
void AProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	
	FVector NewLoc = FVector(CurrLocation.X + (ProjectileSpeed * DeltaTime),
		CurrLocation.Y, CurrLocation.Z);
	
	this->SetActorLocation(NewLoc);
	CurrLocation = NewLoc;
	
	
	

	if (bHit == true)
		this->Destroy();
}

void AProjectile::OnBeginOverlap(AActor* OtherActor)
{
	if (OtherActor)
	{
		ASSS_Player* OwningPlayer = Cast<ASSS_Player>(this->GetOwner());
		if (OtherActor->ActorHasTag(FName("EnemyShip")))
		{
			if (OwningPlayer)
				OwningPlayer->PlayerScore += 50.0f;
		}
		if (OtherActor->ActorHasTag(FName("Asteroid")))
		{
			//If we haven't hit something already 
			if (OwningPlayer)
				OwningPlayer->PlayerScore += 10.0f;
			bHit = true;
		}
		if (OtherActor->ActorHasTag(FName("ProjectileShield")))
			bHit = true;

		if (OtherActor->ActorHasTag(FName("Bounds")))
			bHit = true;
	}
}

