// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShooterSample.h"
#include "PIckup.h"


// Sets default values
APIckup::APIckup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	CollisionMesh = CreateDefaultSubobject <UCapsuleComponent>(TEXT("Collision Component"));


	StaticMesh->AttachTo(RootComponent);
	CollisionMesh->AttachTo(RootComponent);

	OnActorBeginOverlap.AddDynamic(this, &APIckup::OnBeginOverlap);

}

// Called when the game starts or when spawned
void APIckup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APIckup::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	this->SetActorLocation(FVector(this->GetActorLocation().X - (DeltaTime * 100.0f), this->GetActorLocation().Y, 0.0f));

}

void APIckup::OnBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		this->Destroy();
		//TODO: Add functionality to inform the player of the type of pickup
	}
	if (OtherActor->ActorHasTag("Bounds"))
		this->Destroy(); //just destroy it
}