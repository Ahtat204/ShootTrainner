/**
 * @file ChallengeGate.h
 * @brief Defines the AChallengeGate actor, which initiates a training challenge upon player interaction.
 *
 * This actor acts as a physical gate or trigger in the level. When a player
 * overlaps with the actor's trigger volume and presses the designated action key,
 * the challenge defined by the Challenge property is started via the GameState.
 */

#pragma once

#include "CoreMinimal.h"
#include "ShootTrainnerGameState.h"
#include "ShootTrainnerPlayerWidget.h"
#include "GameFramework/Actor.h"
#include "ChallengeGate.generated.h"

// Forward declaration of the struct to minimize dependencies
struct FChallenge; 
// Forward declaration of the enum for difficulty settings
enum class EDifficultyLevel : uint8;

// --- Debugging and Logging Macros ---
#if WITH_EDITOR
    /** Logs a warning message to the Unreal Engine output log, only in the editor build. */
    #define LOG(x) UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(x))
#else
    /** No-op in Shipping/Final builds. */
    #define LOG(x)
#endif


/**
 * @class AChallengeGate
 * @brief An actor that acts as a challenge trigger point in the game world.
 * * When the player character overlaps this gate and interacts with it, 
 * a new training challenge is instantiated based on the FChallenge configuration.
 */
UCLASS(Blueprintable)
class SHOOTTRAINNER_API AChallengeGate : public AActor
{
    GENERATED_BODY()
    
public:    
    // -------------------------------------------------------------------------
    // === COMPONENTS AND PROPERTIES ===
    // -------------------------------------------------------------------------

    /** * @brief The primary trigger component for detecting player overlap. 
     * * This UBoxComponent is used to determine when a player is within range 
     * to interact with the challenge gate and initiate the challenge.
     */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Challenge Gate|Components", 
        meta = (AllowPrivateAccess = "true", ToolTip = "This Component is the trigger for entering the Challenge"))
    class UBoxComponent* Gate;

    /** * @brief Configuration data for the challenge this gate activates.
     * * Defines the parameters of the challenge, such as difficulty, target types, 
     * duration, etc. This is editable in the Level Editor or Blueprints.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Challenge Gate|Settings", 
        meta = (AllowPrivateAccess = "true"))
    FChallenge Challenge;

    // -------------------------------------------------------------------------
    // === LIFECYCLE & CORE FUNCTIONS ===
    // -------------------------------------------------------------------------

    /** * @brief Sets default values for this actor's properties.
     */
    AChallengeGate();

    /**
     * @brief Event called when another actor overlaps with this actor.
     * * This function is typically used to check if the overlapping actor is 
     * the player and, if so, to display the interaction UI prompt.
     * * @param OtherActor The actor that started the overlap.
     */
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

    /**
     * @brief Event called when another actor stops overlapping with this actor.
     * * This function is typically used to hide the interaction UI prompt 
     * when the player moves away from the gate.
     * * @param OtherActor The actor that ended the overlap.
     */
    virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

protected:
    /** * @brief Called when the game starts or when spawned.
     * * Used for initial setup, component attachment, and binding any necessary events.
     */
    virtual void BeginPlay() override;

public: 
    /**
     * @brief Called every frame.
     * * @param DeltaTime The time since the last tick.
     */
    virtual void Tick(float DeltaTime) override;
    
    // -------------------------------------------------------------------------
    // === PUBLIC INTERFACE FUNCTIONS (To be implemented) ===
    // -------------------------------------------------------------------------
    
    // Example of an interaction function that would be called on player input:
    // UFUNCTION(BlueprintCallable, Category = "Challenge Gate|Interaction")
    // void ActivateChallenge();
};