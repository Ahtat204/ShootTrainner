/**
 * @file Target.h
 * @brief Defines the ATarget actor, the base class for all shootable targets.
 *
 * This class provides the fundamental properties and behavior for all objects
 * intended to be hit by the player (e.g., handling hit counts, damage reaction, 
 * and storing impact geometry).
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Target.generated.h"

/**
 * @class ATarget
 * @brief The base class for all shooting targets in the game.
 *
 * It manages the target's visual representation, hit points, and calculation 
 * of impact geometry, and provides a framework for handling damage.
 */
UCLASS()
class SHOOTTRAINNER_API ATarget : public AActor
{
    GENERATED_BODY()

public:
    // -------------------------------------------------------------------------
    // === CONSTRUCTOR ===
    // -------------------------------------------------------------------------

    /**
     * @brief Constructor that sets default values for this actor's properties.
     * @param ObjectInitializer Used to construct the object.
     */
    explicit ATarget(const FObjectInitializer& ObjectInitializer);

protected:
    // -------------------------------------------------------------------------
    // === LIFECYCLE FUNCTIONS (PROTECTED) ===
    // -------------------------------------------------------------------------

    /**
     * @brief Called when the game starts or when this actor is spawned.
     * * Used to set up initial state, material, or physics properties.
     */
    virtual void BeginPlay() override;

public:
    // -------------------------------------------------------------------------
    // === PUBLIC PROPERTIES ===
    // -------------------------------------------------------------------------

    /**
     * @brief The number of times this target has been hit.
     * * This property is typically used to determine if the target should be destroyed 
     * or change state (e.g., fall down).
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="State", meta = (AllowPrivateAccess = "true"))
    int Hits;

    /**
     * @brief The visual and physical representation of the target.
     * * This component holds the mesh and is the primary component for collision and visibility.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* StaticMeshComponent;

    /**
     * @brief The world location of the exact center of the target.
     * * This can be used for scoring calculations (e.g., calculating distance to bullseye).
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Geometry", meta = (AllowPrivateAccess = "true"))
    FVector Center;

    /**
     * @brief The precise world location of the last projectile impact on the target.
     * * Useful for displaying bullet holes or visual feedback.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Geometry", meta = (AllowPrivateAccess = "true"))
    FVector Impact;

    /**
     * @brief The calculated distance from the center of the target to the last impact point.
     * * Used directly for scoring or determining shot accuracy.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Geometry", meta = (AllowPrivateAccess = "true"))
    float distance;
    
    /**
     * @brief A utility Scene Component used to define the origin or center of the target geometry.
     * * This component allows for easy positioning and visualization of the target's 'bullseye' in the editor.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Geometry", meta = (AllowPrivateAccess = "true"))
    USceneComponent* CenterComponent;

    // -------------------------------------------------------------------------
    // === PUBLIC METHODS ===
    // -------------------------------------------------------------------------

    /**
     * @brief Handles the logic executed when the target receives damage.
     * * Typically increments the @ref Hits count and triggers visual/audio feedback.
     */
    void onTakeDamage();
    
    /**
     * @brief Called every frame.
     * * @param DeltaTime The time since the last tick.
     */
    virtual void Tick(float DeltaTime) override;
    
    /**
     * @brief Event handler bound to the StaticMeshComponent's OnComponentHit delegate.
     * * This function is executed when an external physics body (like a projectile) hits 
     * the target's mesh component.
     * * @param HitComp The component that was hit.
     * * @param OtherActor The actor that hit this target (e.g., the projectile).
     * * @param OtherComp The component of the OtherActor that was involved in the hit.
     * * @param NormalImpulse The magnitude of the impulse applied.
     * * @param Hit Details about the hit event, including impact location and normal.
     */
    UFUNCTION(BlueprintCallable, Category="Collision", meta = (Keyword="Hit"))
    void OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};