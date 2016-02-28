// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.h"
#include "Hazard.generated.h"

UCLASS()
class SPACESHOOTERSAMPLE_API AHazard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHazard();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void SpawnChildren(int32 NumChildren);
	void SetHazardVelocity(FVector NewVelocity);
	
	//Callback for overlap with projectiles and other objects
	UFUNCTION()
		void OnBeginOverlap(AActor* OtherActor);

	//Components 
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere)
	UCapsuleComponent *CollisionComponent;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AHazard> ChildSpawn;
	UPROPERTY(EditAnywhere)
	UAudioComponent *AsteroidExplosionSound;
	UPROPERTY(EditAnywhere)
	UParticleSystemComponent *AsteroidExplosionFX;


	//Spawn Transform Vars
	float InitialRotation;
	float InitialXLocation;
	float InitialYLocation;
	float RandSize;

	//Cleanup Destruction vars
	float SelfDestructTimer;

	//Spawn Velocity Vars

	UPROPERTY(EditAnywhere)
	float SpawnXVelocity;
	float SpawnYVelocity;


	//Asteroid Destruction Vars
	bool bHit;
	bool bStartDestroyTimer;
	
	
	
};
