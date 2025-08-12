// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"
#include "ShootTrainnerCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include"Sound/SoundCue.h"


void AWeapon::FireBullet()
{
	if (CurrentAmmo==0)
	{if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Out Of Ammo , Please press R to Reload");
	}
		
	}
	const FVector SpawnLocation = this->SkeletalMeshComponent->GetSocketLocation("Muzzle");
	const FRotator SpawnRotation = this->SkeletalMeshComponent->GetSocketRotation("Muzzle");

	if (CurrentAmmo > 0)
	{
		if (BulletClass)
		{
			const FActorSpawnParameters SpawnParams;
			ABullet* Bullet = GetWorld()->SpawnActor<ABullet>(BulletClass, SpawnLocation, SpawnRotation, SpawnParams);
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation(), 3,
												  5);
			CurrentAmmo--;
		}
	}
}

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
	FireSound = CreateDefaultSubobject<USoundCue>("FireSound");
	NiagraComponent = CreateDefaultSubobject<UNiagaraComponent>("NiagaraComponent");
	NiagraComponent->SetupAttachment(SkeletalMeshComponent);
}


/**
 *  Called when the game starts or when spawned
 */
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
#if UE_EDITOR
	if (FireSound == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("FireSound is NULL"));
	}
#endif
}

/**
 * Called every frame
 * @param DeltaTime 
 */
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
	SetActorRelativeRotation(FRotator(0, 0, 0));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	if (StaticMeshComponent)
	{
		RootComponent = StaticMeshComponent;
	}
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	if (ProjectileMovementComponent)
	{
		ProjectileMovementComponent->InitialSpeed = 200.f;
		ProjectileMovementComponent->MaxSpeed = 300.f;
		ProjectileMovementComponent->bRotationFollowsVelocity = false;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	}
	
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CollisionCapsule");
	CapsuleComponent->SetupAttachment(RootComponent);
	CapsuleComponent->SetCapsuleHalfHeight(81.08f);
	CapsuleComponent->SetCapsuleRadius(23.944208f);
}
