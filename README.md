# Third-Person Action Prototype - Unreal Engine 5 (C++)

Technical prototype of a third-person character controller and gameplay mechanics built natively with **C++** and **Blueprints** in **Unreal Engine 5**.

Developed for the **Graphics Engines** course as part of the **Master's Degree in Video Game Design and Development** at Universitat Oberta de Catalunya (UOC).

## 🎥 Video Demo
* **Milestone 1 (PAC 1) Showcase:** [Watch on YouTube](https://www.youtube.com/watch?v=phF6DxUIqK8&t=3s)

---

## ⚙️ Key Implementations (Milestone 1 - PAC 1)

* **Core Framework (`AMyGameModeBase`):** Custom GameMode architecture configured to spawn and possess the custom C++ player character.
* **Third-Person Character (`APlayerCharacter`):**
  * Camera boom (`USpringArmComponent`) and follow camera (`UCameraComponent`) with pawn control rotation.
  * Locomotion and camera look functionality powered by the **Enhanced Input System** (`UInputMappingContext` & `UInputAction`).
* **Animation System (`UMyCharacterAnimInstance`):**
  * **IK Retargeting:** Full skeletal retargeting from the UE5 Mannequin to the *Paragon: Lt. Belica* asset.
  * **Native C++ AnimInstance:** Real-time calculation of planar velocity (`Size2D`), vertical velocity, airborne state (`IsFalling`), and camera pitch angle.
  * **State Machine & 1D Blend Space:** Smooth transitions between Idle, Run, Jump Start, Jump Loop, and Jump End states.
  * **Procedural Spine Aiming:** Dynamic upper-body bone rotation (`Transform (Modify) Bone`) driven by camera pitch.
* **Projectile System (`AProjectileActor`):**
  * Root sphere collision detection (`USphereComponent`), visual mesh, and linear trajectory via `UProjectileMovementComponent`.
  * Dynamic hit event binding (`OnComponentHit`) for automatic destruction upon impact or lifespan expiration.

---

## 🛠️ Tech Stack & Environment
* **Engine:** Unreal Engine 5
* **Language:** C++17 / C++20
* **IDE:** Visual Studio 2022
* **Assets:** Paragon: Lt. Belica & Starter Content (Epic Games Marketplace)

---

## 🚀 Getting Started
1. Clone the repository.
2. Right-click `MyProject.uproject` and select **Generate Visual Studio project files**.
3. Open `MyProject.sln` in Visual Studio, set the configuration to **Development Editor / Win64**, and build the solution (`Ctrl + Shift + B`).
4. Double-click `MyProject.uproject` to open the project in Unreal Engine 5.