// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PIckup.generated.h"

UCLASS()
class SPACESHOOTERSAMPLE_API APIckup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APIckup();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION()
	void OnBeginOverlap(AActor *OtherActor);

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CollisionMesh;
	
	
};
