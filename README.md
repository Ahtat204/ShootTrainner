## 🎯 ShootTrainer Core Game Logic  ![Status](https://img.shields.io/badge/status-done-green?style=for-the-badge)

This repository contains the core C++ source files for managing the **game state, player mechanics, weapons, and challenges** in the **ShootTrainer** project. These foundational classes and structures define the gameplay flow essential for a first-person shooting training simulator.

-----
## Project Diagram 
<img src="Classes%20Diagram.png" alt="Diagram">
## ⚙️ Key C++ Components

### 1\. Game State and Data

| Class/Struct                   | Role                                             | Key Properties/Methods                                                                                                                |
|:-------------------------------|:-------------------------------------------------|:--------------------------------------------------------------------------------------------------------------------------------------|
| **`AShootTrainnerGameState`**  | Server-side object managing shared session data. | **`Challenges`**: Stores `TArray<FChallenge>` for the session.                                                                        |
| **`FChallenge`**               | Defines a single training exercise.              | **`Difficulty`**, **`Name`**, **`TimeLimit`**, **`ScoreMultiplier`**.<br/> **`EvaluatePerChallengeAccuracy(float distance)`** method. |                                                                          |
| **`AShootTrainerPlayerState`** | Tracks per-player stats and performance.         | **`Accuracy`**, **`ShotsFiredCount`**, **`TargetHit`**, **`TimePlayed`**. **`EvaluateAccuracy(TArray<float> Accuracies)`** method.    |

### 2\. Player and World Interaction

| Class                         | Role                                     | Key Responsibilities                                                                                                                                      |
|:------------------------------|:-----------------------------------------|:----------------------------------------------------------------------------------------------------------------------------------------------------------|
| **`AShootTrainnerCharacter`** | Represents the player in the world.      | Handles movement, camera, **weapon states** (Armed, Firing, Aiming), input binding, and interaction.                                                      |
| **`AChallengeGate`**          | Defines the entry point for a challenge. | Uses an overlap box (`GateTrigger`) to detect players, displays optional UI (`ChallengeWidget`), and starts the challenge upon player **`Interact`** (E). |
| **`AWeapon`**                 | Base class for all firearms.             | Manages firing, **ammo**, `MagazineSize`, **pickup**, and effects (`NiagaraComponent`).                                                                   |
| **`ABullet`**                 | Represents the projectile.               | Uses `UProjectileMovementComponent` for flight and handles collision.                                                                                     |
| **`ATarget`**                 | Base class for all shooting targets.     | Tracks **`Hits`**, **`Impact`** location, **`distance`** from the player, and handles collision with bullets.                                             |
| **`AChallengeGate`**          | the gate to start playing a challenge.   | it detects player overlapping state  **`EOverLappingState`**, **`Impact`** location, **`distance`** from the player, and handles collision with bullets.  |

-----

## 📜 Enumerators (Enums)

These enums standardize key states and values, making the logic predictable and accessible to Blueprints.

| Enumerator              | Purpose                                        | Key Values                                          |
|:------------------------|:-----------------------------------------------|:----------------------------------------------------|
| **`EPlayerState`**      | Player's current activity.                     | `FreeRoam`, `Challenge`                             |
| **`EDifficultyLevel`**  | Pre-set challenge difficulty.                  | `VeryEasy` → `Insane`                               |
| **`EOverlappingState`** | Tracking actor overlap events.                 | `None`, `Started`, `Ended`                          |
| **`EWeaponState`**      | Tracks if the player is aiming or shooting ... | `Unarmed`, `Armed`, `Aiming`,`Shooting`,`Reloading` |

-----

## ⌨️ Default Input Mappings

The player character binds the following actions to control movement, combat, and interaction:

| Action       | Key / Button         | Description                     |
|:-------------|:---------------------|:--------------------------------|
| **Move**     | `WASD`               | Player movement                 |
| **Look**     | `Mouse`              | Camera rotation                 |
| **Jump**     | `Space`              | Player jump                     |
| **Fire**     | `Left Mouse Button`  | Shoot weapon                    |
| **Aim**      | `Right Mouse Button` | Aim down sights                 |
| **Reload**   | `R`                  | Reload weapon                   |
| **Open**     | `O`                  | Open a Door                     |
| **Drop**     | `Q`                  | Drop equipped weapon            |
| **Play**     | `P`                  | Open Pause Menu                 |
| **Exit**     | `Esc`                | Exit challenge                  |

-----

## 📁 Project Structure

The C++ source code is organized into logical directories within the `Source/` folder:

```
ShootTrainner/
├─ Config/             # UE5 configuration files
├─ Source/             # C++ source files
├─ ShootTrainner.uproject
└─ README.md
```

-----

**Note:** This repository provides a code-only reference implementation. All core gameplay logic—including player stats, challenge mechanics, and weapon handling—is implemented entirely in **C++**. Blueprints are not included but can be used to extend these classes.
Thumbnail:
<img src="Thumbnail.png">
