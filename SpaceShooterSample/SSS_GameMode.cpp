// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShooterSample.h"
#include "SSS_GameMode.h"


ASSS_GameMode::ASSS_GameMode()
{
	SpawnTimer = 0;

	MusicTrack = CreateDefaultSubobject<UAudioComponent>(TEXT("Music"));

	AsteroidSpawnLoc = FVector(10000.0f, 10000.0f, 10000.0f);
	AsteroidSpawnRot = FRotator(0.0f, 0.0f, 0.0f);
	AsteroidSpawnParams.Owner = this;

	
	
}

void ASSS_GameMode::BeginPlay()
{
	Super::BeginPlay();
	MusicTrack->Play();

	if (ScoreWidgetClass != nullptr)
	{
		ScoreWidget = CreateWidget<UUserWidget>(GetWorld(), ScoreWidgetClass);
		ScoreWidget->AddToViewport();
	}
	if(RestartWidgetClass != nullptr)
		RestartWidget = CreateWidget<UUserWidget>(GetWorld(), RestartWidgetClass);

	bPlayerDead = false;

	PCRef = GetWorld()->GetFirstPlayerController();
	RestartWidget->AddToViewport();
	RestartWidget->SetVisibility(ESlateVisibility::Hidden);
	

	
}

void ASSS_GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpawnTimer = FMath::RandRange(0, 1000);
	if (HazardTemplate)
	{
		if (SpawnTimer > 995)
		{
			AActor *NewHazard = GetWorld()->SpawnActor(HazardTemplate, &AsteroidSpawnLoc, &AsteroidSpawnRot, AsteroidSpawnParams);

			NewHazard->SetActorLocation(FVector(1000.0f, 1000.0f, 1000.0f));
			
		}
	}
	
	FVector EnemySpawnLoc(0.0f, 0.0f, 0.0f);
	FRotator EnemySpawnRot(0.0f, 0.0f, 0.0f);

	if (Enemies)
	{
		if (SpawnTimer > 990)
		{
			AActor* NewEnemy = GetWorld()->SpawnActor(Enemies, &EnemySpawnLoc, &EnemySpawnRot, AsteroidSpawnParams);
			if (NewEnemy)
				NewEnemy->SetActorLocation(FVector(1000.0f, FMath::RandRange(-500, 500), 0.0f));
		}

	}

	if (bPlayerDead)
	{
		
		if (PCRef != nullptr)
		{
			RestartWidget->SetVisibility(ESlateVisibility::Visible);
			PCRef->bShowMouseCursor = true;
			bPlayerDead = false;
		}
		
	}
}

TSubclassOf<AHazard> ASSS_GameMode::GetHazardTemplate()
{
	return HazardTemplate;
}

void ASSS_GameMode::RestartLevel(FName LevelName)
{
	UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}