// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Weapon.generated.h"


class ABullet;


/**
 * base class of all weapons
 */
UCLASS()
class SHOOTTRAINNER_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	/**
	 * // Sets default values for this actor's properties
	 * @param FObjectInitializer Internal class to finalize UObject creation (initialize properties) after the real C++ constructor is called.
	 */
	explicit AWeapon(const FObjectInitializer& FObjectInitializer);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/**
	 * this is the SkeletonMeshComponent for the Pistol
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void FireBullet();
	/**
	 * collision detection function, like Unity's OnEnterCollision()
	 * @param OtherActor :actor to collide with
	 */
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	/**
	 * this is for reusability, for different types of bullets , meant to be set in the blueprint derived class
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABullet> BulletClass;
	/**
	 * maximum number of bullets
	 */
	uint32 MagazineSize = 20;
	/**
	 * initial number of bullets
	 */
	uint32 CurrentAmmo = MagazineSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* PickupSphere;
	/**
	 * this is the sound of the gunshot 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sounds", meta = (AllowPrivateAccess = "true"))
	class USoundCue* FireSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components", meta = (AllowPrivateAccess = "true"))
	TArray<ABullet*> Bullets;
	/**
	 * this is the gun fire visual effect , aka VFX
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	UParticleSystemComponent* FireParticle;
	
};


UCLASS()
class ABullet : public AActor
{
	GENERATED_BODY()

public:
	explicit ABullet(const FObjectInitializer& FObjectInitializer);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	/// Component responsible for projectile movement behavior 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
	/// used for basic collision with targets


	/*class UBoxComponent* BoxComponent;
	*/
};
