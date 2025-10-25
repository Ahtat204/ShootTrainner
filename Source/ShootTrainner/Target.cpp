// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"

#include "Weapon.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATarget::ATarget(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMeshComponent;
	CenterComponent = CreateDefaultSubobject<USceneComponent>(TEXT("TargetCenter"));
	CenterComponent->SetupAttachment(RootComponent);
	
}



// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();
	Center=CenterComponent->GetComponentLocation();
	StaticMeshComponent->OnComponentHit.AddDynamic(this, &ATarget::OnComponentHit);
	
}

void ATarget::onTakeDamage()
{
	Hits++;
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

void ATarget::OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor ||OtherActor==this) return;
	if (const auto* hitactor=Cast<ABullet>(OtherActor)  )
	{
		UGameplayStatics::ApplyDamage(this, 20.0f, nullptr, OtherActor, UDamageType::StaticClass());
		Impact=Hit.ImpactPoint;
		distance=FVector::Dist(Impact,Center);
		onTakeDamage();
	}
}

