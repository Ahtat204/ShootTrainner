// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "ShootTrainnerCharacter.h"

// Sets default values
AWeapon::AWeapon(const FObjectInitializer& FObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SkeletalMeshComponent=CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
    RootComponent=SkeletalMeshComponent;
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

void AWeapon::NotifyActorBeginOverlap(AActor* OtherActor) override
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (auto const player=Cast<AShootTrainnerCharacter>(OtherActor))
	{
		if ()
		{
			player->PickUpItem(this);
		}
		
		
	}
	
}

