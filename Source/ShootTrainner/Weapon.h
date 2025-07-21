// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Weapon.generated.h"

UCLASS()
class SHOOTTRAINNER_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	explicit AWeapon(const FObjectInitializer& FObjectInitializer);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//this is the SkeletonMeshComponent for the Pistol
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	class USphereComponent* PickupSphere;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};


UCLASS()
class ABullet : public AActor
{
	GENERATED_BODY()

public:
	ABullet(const FObjectInitializer& FObjectInitializer);
	private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components",meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
};
