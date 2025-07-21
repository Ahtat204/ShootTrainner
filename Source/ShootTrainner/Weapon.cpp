// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "ShootTrainnerCharacter.h"
#include "Components/SphereComponent.h"

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
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (auto const player = Cast<AShootTrainnerCharacter>(OtherActor))
	{
		//if()
		{
			player->pickUpPistol = this;
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
}
