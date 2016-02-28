// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Enemy.h"
#include "Blueprint/UserWidget.h"
#include "Hazard.h"
#include "GameFramework/GameMode.h"
#include "SSS_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHOOTERSAMPLE_API ASSS_GameMode : public AGameMode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<AHazard> HazardTemplate;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AEnemy> Enemies;
	UPROPERTY(EditAnywhere)
	UAudioComponent* MusicTrack;

	ASSS_GameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	TSubclassOf<AHazard> GetHazardTemplate();


public:
	int32 SpawnTimer;
	bool bPlayerDead;
	UFUNCTION()
	void RestartLevel(FName LevelName);
	bool bStart;

	//Reference to the player to check for player death



	//UI Vars
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HUD Elements")
	TSubclassOf<UUserWidget> ScoreWidgetClass;
	UUserWidget *ScoreWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HUD Elements")
	TSubclassOf<UUserWidget> RestartWidgetClass;
	UUserWidget *RestartWidget;

	//Asteroid Vars
	

	FActorSpawnParameters AsteroidSpawnParams;
	FVector AsteroidSpawnLoc;
	FRotator AsteroidSpawnRot;


	APlayerController* PCRef;

	
};
