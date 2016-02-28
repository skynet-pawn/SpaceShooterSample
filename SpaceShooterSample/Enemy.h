// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Projectile.h"
#include "EnemyController.h"
#include "GameFramework/Pawn.h"
#include "Enemy.generated.h"

UCLASS()
class SPACESHOOTERSAMPLE_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//Components
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CollisionComponent;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> EnemyProjectile;
	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* ExplosionFX;
	UPROPERTY(EditAnywhere)
		UAudioComponent* ExplosionSound;


	//Velocity Vector
	UPROPERTY(EditAnywhere)
	FVector CurrentVelocity;
	float TotalTime;
	float TimeSinceLastShot;

	UFUNCTION()
	void OnBeginOverlap(AActor* OtherActor);


	bool bHit;
	bool bDestroy;
	float fDestroyTimer;

	
};
