// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"
#include "ShootTrainnerCharacter.h"
#include "Components/SphereComponent.h"
#include"Particles/ParticleSystemComponent.h"
#include"Sound/SoundCue.h"

// Sets default values
AWeapon::AWeapon(const FObjectInitializer& FObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	RootComponent = SkeletalMeshComponent;
	PickupSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickupSphere"));
	PickupSphere->SetupAttachment(RootComponent);
	PickupSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PickupSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	PickupSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	PickupSphere->SetSphereRadius(50.f);
	FireParticle = CreateDefaultSubobject<UParticleSystemComponent>("FireParticleComponent");
	FireSound=CreateDefaultSubobject<USoundCue>("FireSound");
}


/**
 *  Called when the game starts or when spawned
 */
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

/**
 * Called every frame
 * @param DeltaTime 
 */
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::FireBullet()
{
	if (CurrentAmmo == 0)
	{
		UE_LOG(LogTemp, Display, TEXT("Out of ammo, please reload"));
		return;
	}

	const FVector SpawnLocation = this->GetActorLocation();
	const FRotator SpawnRotation = this->GetActorRotation();

	if (BulletClass)
	{
		const FActorSpawnParameters SpawnParams;

		if (ABullet* Bullet = GetWorld()->SpawnActor<ABullet>(BulletClass, SpawnLocation, SpawnRotation, SpawnParams))
		{
			Bullets.Add(Bullet);
			CurrentAmmo--;
		}
	}
}


void AWeapon::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (auto const Player = Cast<AShootTrainnerCharacter>(OtherActor))
	{
		//if()
		{
			Player->pickUpPistol = this;
		}
	}
}

ABullet::ABullet(const FObjectInitializer& FObjectInitializer)
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	if (StaticMeshComponent)
	{
		RootComponent = StaticMeshComponent;
	}
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	if (ProjectileMovementComponent)
	{
		ProjectileMovementComponent->InitialSpeed = 2000.f;
		ProjectileMovementComponent->MaxSpeed = 3000.f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = false;
	}
}
