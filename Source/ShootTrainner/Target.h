// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Target.generated.h"

/**
 * base class of all the shooting targets 
 */
UCLASS()
class SHOOTTRAINNER_API ATarget : public AActor
{
public:
	

private:
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	explicit ATarget(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="State", meta = (AllowPrivateAccess = "true"))
	int Hits;
	/// 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Geometry", meta = (AllowPrivateAccess = "true"))
	FVector Center;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Geometry", meta = (AllowPrivateAccess = "true"))
	FVector Impact;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Geometry", meta = (AllowPrivateAccess = "true"))
	float distance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Geometry", meta = (AllowPrivateAccess = "true"))
	USceneComponent* CenterComponent;

	void onTakeDamage();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, Category="Collision", meta = (Keyword="Hit"))
	void OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	
};
