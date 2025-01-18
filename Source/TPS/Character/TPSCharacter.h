// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "GameFramework/Character.h"
#include "FuncLibrary/Types.h"
#include "CoreMinimal.h"
#include "WeaponDefault.h"
#include "TPSCharacter.generated.h"

UCLASS(Blueprintable)
class ATPSCharacter : public ACharacter 
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override; 
	
public:
	ATPSCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	//FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class UDecalComponent* CursorToWorld;

public:
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Demo")
		TSubclassOf<AWeaponDefault>InitWeaponClass = nullptr;
	
	//Inputs
	UFUNCTION()
	void InputAxisY(float Value);
	UFUNCTION()	
	void InputAxisX(float Value);
	UFUNCTION()
		void InputAttackPressed();
	UFUNCTION()
		void InputAttackReleased();
	//for demo 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Demo")
		FName InitWeaponName;

	float AxisX = 0.0f;
	float AxisY = 0.0f;
	//
	UFUNCTION()
	void MovementTick(float DeltaTaim);

	UFUNCTION(BlueprintCallable)
		void AttackCharEvent(bool bIsFiring);

	//Weapon
	AWeaponDefault* CurrentWeapon = nullptr;

	UFUNCTION(BlueprintCallable)
		void CharacterUpdate();
	UFUNCTION(BlueprintCallable)
		void ChangeMovementState();
	UFUNCTION(BlueprintCallable)
		void StartSprinting();
	UFUNCTION(BlueprintCallable)
		void StopSprinting();
	UFUNCTION(BlueprintCallable)
		void HandleCharacterMovementSpeedTick();
	//Cursor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
		UMaterialInterface* CursorMaterial = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
		FVector CursorSize = FVector(20.0f, 40.0f, 40.0f);

	UFUNCTION(BlueprintCallable)
		UDecalComponent* GetCursorToWorld();
	UDecalComponent* CurrentCursor = nullptr;

	UFUNCTION(BlueprintCallable)
		void InitWeapon(FName IdWeaponName);

	UFUNCTION(BlueprintCallable)
		AWeaponDefault* GetCurrentWeapon();



};


