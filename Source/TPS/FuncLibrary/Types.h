// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Types.generated.h"

UENUM(BlueprintType)
enum class EMovementState : uint8
{
	Aim_State UMETA(DisplayName = "Aim State"),
	AimWalk_State UMETA(DisplayName = "AimWalk State"),
	Walk_State UMETA(DisplayName = "Walk State"),
	Run_State UMETA(DispalyName = "Run State"),
	SprintRun_State UMETA(DisplayName = "SprintRun State")

};

USTRUCT(BlueprintType)	
struct FCharacterSpeed
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Movement")
		float AimSpeedNormal = 300.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float WAlkSpeedNomal = 200.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float RunSpeedNormal = 600.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float AimSpeedWalk = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float SprintRunSprintRun = 800.0f;
};

UCLASS()
class TPS_API UTupes : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

};