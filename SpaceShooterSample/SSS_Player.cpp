// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShooterSample.h"
#include "SSS_Player.h"


// Sets default values
ASSS_Player::ASSS_Player()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	ParticleSystems = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
	ExplosionFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ExplosionFX"));
	DeathExplosionSound = CreateDefaultSubobject<UAudioComponent>(TEXT("DeathExplosionSound"));
	

	CollisionComponent->AttachTo(RootComponent);
	ShipMesh->AttachTo(RootComponent);
	ParticleSystems->AttachTo(RootComponent);
	ExplosionFX->AttachTo(RootComponent);
	DeathExplosionSound->AttachTo(RootComponent);



	MaxVelocity = 100.0f;
	CurrXVelocity = 0.0f;
	CurrYVelocity = 0.0f;

	bIsFiring = false;
	WeaponFireRate = 0.25f;
	TimeSinceLastShot = 0.0f;

	PlayerScore = 0.0f;

	//Event Delegate

	OnActorBeginOverlap.AddDynamic(this, &ASSS_Player::OnBeginOverlap);
	
}

// Called when the game starts or when spawned
void ASSS_Player::BeginPlay()
{
	Super::BeginPlay();

	CurrLocation = this->GetActorLocation();
	CurrRotation = this->GetActorRotation();
	
	bHit = false;
	bDead = false;

	ExplosionFX->Deactivate();
	DeathExplosionSound->Deactivate();

	
}

// Called every frame
void ASSS_Player::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	

	if (CurrXVelocity != 0.0f || CurrYVelocity != 0.0f)
	{
		NewLocation = FVector(CurrLocation.X + (CurrXVelocity * DeltaTime),
							  CurrLocation.Y + (CurrYVelocity * DeltaTime), 0);
		this->SetActorLocation(NewLocation);
		CurrLocation = NewLocation;

		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::FromInt(CurrLocation.Y));
		
	}

	if (CurrYVelocity > .1)
	{
		this->SetActorRotation(FRotator(CurrRotation.Pitch + 45.0f, CurrRotation.Yaw, CurrRotation.Roll));
	}
	else if (CurrYVelocity < -.1)
	{
		this->SetActorRotation(FRotator(CurrRotation.Pitch - 45.0f, CurrRotation.Yaw, CurrRotation.Roll));
	}
	else
		this->SetActorRotation(FRotator(CurrRotation));
	

	if (this->GetActorLocation().X > FieldWidth)
		CurrLocation = FVector(FieldWidth - 1, CurrLocation.Y, CurrLocation.Z);
	if (this->GetActorLocation().X < -FieldWidth)
		CurrLocation = FVector(-FieldWidth + 1, CurrLocation.Y, CurrLocation.Z);
	if (this->GetActorLocation().Y > FieldHeight)
		CurrLocation = FVector( CurrLocation.X, FieldHeight - 1, CurrLocation.Z);
	if (this->GetActorLocation().Y < -FieldHeight)
		CurrLocation = FVector(CurrLocation.X, -FieldHeight + 1, CurrLocation.Z);

	if (bIsFiring)
	{
		if (TimeSinceLastShot > WeaponFireRate)
		{
			FireWeapon();
			TimeSinceLastShot = 0.0f;
		}
	}
	
	TimeSinceLastShot += DeltaTime;

	if (bHit)
	{

		bDead = true;

		this->ShipMesh->SetVisibility(false);
		this->ParticleSystems->SetVisibility(false);
		this->ExplosionFX->Activate();
		this->DeathExplosionSound->Activate();
		this->DeathExplosionSound->Play();
		this->SetActorTickEnabled(false);

		ASSS_GameMode *GameModeRef = Cast<ASSS_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		GameModeRef->bPlayerDead = true;
	}
	
}

// Called to bind functionality to input
void ASSS_Player::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis(FName("MoveRight"), this, &ASSS_Player::MoveRight);
	InputComponent->BindAxis(FName("MoveUp"), this, &ASSS_Player::MoveUp);
	InputComponent->BindAction(FName("Fire"), IE_Pressed, this, &ASSS_Player::StartFiring);
	InputComponent->BindAction(FName("Fire"), IE_Released, this, &ASSS_Player::StopFiring);
}

void ASSS_Player::MoveRight(float AxisValue)
{
	CurrXVelocity = MaxVelocity * AxisValue;
}

void ASSS_Player::MoveUp(float AxisValue)
{
	CurrYVelocity = MaxVelocity * AxisValue;
}

void ASSS_Player::FireWeapon()
{
	FActorSpawnParameters Params = {  };
	Params.Owner = this;
	AActor* SpawnedProjectile = GetWorld()->SpawnActor(WeaponProjectile_BP, &CurrLocation, &CurrRotation, Params);
}

void ASSS_Player::StartFiring()
{
	bIsFiring = true;
}

void ASSS_Player::StopFiring()
{
	bIsFiring = false;
}

void ASSS_Player::OnBeginOverlap(AActor* OtherActor)
{
	if(OtherActor->ActorHasTag(FName("Asteroid")))
		bHit = true;
	if (OtherActor->ActorHasTag(FName("EnemyProjectile")))
		bHit = true;
	if (OtherActor->ActorHasTag(FName("EnemyShip")))
		bHit = true;
	
}

int32 ASSS_Player::GetScore()
{
	return this->PlayerScore;
}