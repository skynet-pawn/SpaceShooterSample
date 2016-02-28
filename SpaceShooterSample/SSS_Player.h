// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SSS_GameMode.h"
#include "Projectile.h"
#include "GameFramework/Pawn.h"
#include "SSS_Player.generated.h"


UCLASS()
class SPACESHOOTERSAMPLE_API ASSS_Player : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASSS_Player();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* ParticleSystems;
	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* ExplosionFX;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ShipMesh;
	UPROPERTY(EditAnywhere)
	UCapsuleComponent *CollisionComponent;
	UPROPERTY(EditAnywhere)
	UAudioComponent *DeathExplosionSound;

	UPROPERTY(EditAnywhere)
		float FieldHeight;
	UPROPERTY(EditAnywhere)
		float FieldWidth;
	
	

	//Input Functions

	void MoveRight(float AxisValue);
	void MoveUp(float AxisValue);

	void FireWeapon();
	void StartFiring();
	void StopFiring();


	//Input Variables
	UPROPERTY(EditAnywhere)
	float MaxVelocity;
	bool bIsFiring;
	float WeaponFireRate;
	float TimeSinceLastShot;

	//Player State Vars
	bool bHit;
	bool bDead;

	float CurrXVelocity;
	float CurrYVelocity;

	UPROPERTY(BlueprintReadOnly)
	float PlayerScore;

	FVector CurrLocation;
	FRotator CurrRotation;
	FVector NewLocation;

	//Projectile Component
	

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AProjectile> WeaponProjectile_BP;

	//Events
	UFUNCTION()
	void OnBeginOverlap(AActor* OtherActor);

	UFUNCTION()
	int32 GetScore();



};
