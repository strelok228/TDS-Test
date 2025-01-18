// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"

#include "FuncLibrary/Types.h"
#include "ProjectileDefault.h"
#include "WeaponDefault.generated.h"

UCLASS()
class TPS_API AWeaponDefault : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties 
	AWeaponDefault();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Components)
		class USceneComponent* SceneComponent = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Components)
		class USkeletalMeshComponent* SkeletalMeshWeapon = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Components)
		class UStaticMeshComponent* StaticMeshWeapon = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Components)
		class UArrowComponent* ShootLocation = nullptr;
	UPROPERTY()
		FWeaponInfo WeaponSetting;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info")
		FAddicionalWeaponInfo WeaponInfo;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireLogic")
		bool WeaponFiring = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReloadLogic")
		bool WeaponReloading = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
	void FireTick(float DeltaTime);
	void WeaponInit();
	void UpdateStateWeapon(EMovementState NewMovementState);

	UFUNCTION(BlueprintCallable)
	void SetWeaponStateFire(bool bIsFire);

	bool CheckWeaponCanFire();

	float FireTimer = 0.0f;
	FProjectileInfo GetProjectile();

	void Fire();
};
