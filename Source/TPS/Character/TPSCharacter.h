// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FuncLibrary/Types.h"
#include "WeaponDefault.h"
#include "Character/TPSInventoryComponent.h"
#include "Character/TPSCharacterHealthComponent.h"
#include "TPSHealthComponent.h"

#include "TPSCharacter.generated.h"

UCLASS(Blueprintable)
class ATPSCharacter : public ACharacter
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

public:
    ATPSCharacter();

    FTimerHandle TimerHandle_RagDollTimer;

    // Called every frame.
    virtual void Tick(float DeltaSeconds) override;

    virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

    /** Returns TopDownCameraComponent subobject **/
    FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const
    {
        return TopDownCameraComponent;
    }
    /** Returns CameraBoom subobject **/
    FORCEINLINE class USpringArmComponent* GetCameraBoom() const
    {
        return CameraBoom;
    }
    /** Returns CursorToWorld subobject **/
    // FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
    class UTPSInventoryComponent* InventoryComponent;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
    class UTPSCharacterHealthComponent* CharHealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
    bool bIsDead = false;


private:
    /** Top down camera */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* TopDownCameraComponent;

    /** Camera boom positioning the camera above the character */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class USpringArmComponent* CameraBoom;

    /** A decal that projects to the cursor location. */
    // UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    // class UDecalComponent* CursorToWorld;


public:
    // Cursor
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
    UMaterialInterface* CursorMaterial = nullptr;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
    FVector CursorSize = FVector(20.0f, 40.0f, 40.0f);

    // Movement
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    EMovementState MovementState = EMovementState::Run_State;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    FCharacterSpeed MovementSpeedInfo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    bool SprintRunEnabled = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    bool WalkEnabled = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    bool AimEnabled = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    bool bIsAlive = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    TArray<UAnimMontage*> DeadsAnim;

    // Weapon
    AWeaponDefault* CurrentWeapon = nullptr;

    UDecalComponent* CurrentCursor = nullptr;

    float AxisX = 0.0f;
    float AxisY = 0.0f;

    // Inputs
    UFUNCTION()
    void InputAxisY(float Value);
    UFUNCTION()
    void InputAxisX(float Value);
    UFUNCTION()
    void InputAttackPressed();
    UFUNCTION()
    void InputAttackReleased();

    // Tick Func
    UFUNCTION()
    void MovementTick(float DeltaTaim);

    //Func
    UFUNCTION(BlueprintCallable)
    void AttackCharEvent(bool bIsFiring);
    UFUNCTION(BlueprintCallable)
    void CharacterUpdate();
    UFUNCTION(BlueprintCallable)
    void ChangeMovementState();

    UFUNCTION(BlueprintCallable)
    AWeaponDefault* GetCurrentWeapon();

    UFUNCTION(BlueprintCallable)
    void InitWeapon(FName IdWeaponName, FAdditionalWeaponInfo WeaponAdditionalInfo, int32 NewCurrentIndexWeapon);
    
    UFUNCTION(BlueprintCallable) // VisualOnly
    void RemoveCurrentWeapon();

    UFUNCTION(BlueprintCallable)
    void TryReloadWeapon();



    UFUNCTION(BlueprintCallable)
    void StartSprinting();
    UFUNCTION(BlueprintCallable)
    void StopSprinting();
    UFUNCTION(BlueprintCallable)
    void HandleCharacterMovementSpeedTick();

    UFUNCTION()
    void WeaponReloadStart(UAnimMontage* Anim);
    UFUNCTION()
    void WeaponReloadEnd(bool bIsSuccess, int32 AmmoTake);
    UFUNCTION(BlueprintNativeEvent)
    void WeaponReloadStart_BP(UAnimMontage* Anim);
    UFUNCTION(BlueprintNativeEvent)
    void WeaponReloadEnd_BP(bool bIsSuccess);

    UFUNCTION()
    void WeaponFireStart(UAnimMontage* Anim);
    UFUNCTION(BlueprintNativeEvent)
    void WeaponFireStart_BP(UAnimMontage* Anim);

    UFUNCTION(BlueprintCallable)
    UDecalComponent* GetCursorToWorld();

    void TrySwicthNextWeapon();
    void TrySwitchPreviosWeapon();

    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
    int32 CurrentIndexWeapon = 0;

    UFUNCTION(BlueprintCallable)
    void Die(bool bIsDead);
    //
    UFUNCTION(BlueprintCallable)
    void CharDead();
    void EnableRagdoll();
    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;;


};
