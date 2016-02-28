// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "SSS_Player.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class SPACESHOOTERSAMPLE_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* PlaneComponent;
	UPROPERTY(EditAnywhere)
		UCapsuleComponent* CapsuleCollision;
	UPROPERTY(EditAnywhere)
		float ProjectileSpeed;

	UFUNCTION()
		void OnBeginOverlap(AActor* OtherActor);



	FVector CurrLocation;
	bool bHit;
	bool bDestroy;
	
	
};
