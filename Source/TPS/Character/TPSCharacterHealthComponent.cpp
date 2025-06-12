// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TPSCharacterHealthComponent.h"
#include "TPSCharacter.h"


void UTPSCharacterHealthComponent::ChangeHealthValue(float ChangeValue)
{
	ATPSCharacter* Character = Cast<ATPSCharacter>(GetOwner());
	if (Character)
	{
		if (!Character->bIsDead == true)
		{
		
			float CurrentDamage = ChangeValue * CoefDamage;

			if (Shield > 0.0f && ChangeValue < 0.0f)
			{
				ChangeShieldValue(ChangeValue);

				if (Shield < 0.0f)
				{
					//FX
					//UE_LOG(LogTemp, Warning, TEXT("UTPSCharacterHealthComponent::ChangeHealthValue - Sheild < 0"));
				}
			}
			else
			{
				Super::ChangeHealthValue(ChangeValue);
			}
		}
		return;
	}
}

float UTPSCharacterHealthComponent::GetCurrentShield()
{
	return Shield;
}

void UTPSCharacterHealthComponent::ChangeShieldValue(float ChangeValue)
{
	ATPSCharacter* Character = Cast<ATPSCharacter>(GetOwner());
	if (Character)
	{
		if(!Character->bIsDead == true)
		{
			Shield += ChangeValue;

			if (Shield > 100.0f)
			{
				Shield = 100.0f;
			}
			else
			{
				if (Shield < 0.0f)
					Shield = 0.0f;
			}

			if (GetWorld())
			{
				GetWorld()->GetTimerManager().SetTimer(TimerHandle_CollDownShieldTimer, this, &UTPSCharacterHealthComponent::CoolDownShieldEnd, CoolDownShieldRecoverTime, false);

				GetWorld()->GetTimerManager().ClearTimer(TimerHandle_ShieldRecoveryRateTimer);
			}

			OnShieldChange.Broadcast(Shield, ChangeValue);
		}
		return;
	}

}

void UTPSCharacterHealthComponent::CoolDownShieldEnd()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_ShieldRecoveryRateTimer, this, &UTPSCharacterHealthComponent::RecoveryShield, ShieldRecoverRate, true);
	}
}

void UTPSCharacterHealthComponent::RecoveryShield()
{
	ATPSCharacter* Character = Cast<ATPSCharacter>(GetOwner());
	if (Character)
	{
		if (!Character->bIsDead == true)
		{
			float tmp = Shield;
			tmp = tmp + ShieldRecoverValue;
			if (tmp > 100.0f)
			{
				Shield = 100.0f;
				if (GetWorld())
				{
					GetWorld()->GetTimerManager().ClearTimer(TimerHandle_ShieldRecoveryRateTimer);
				}
			}
			else
			{
				Shield = tmp;
			}

			OnShieldChange.Broadcast(Shield, ShieldRecoverValue);
		}
		return;
	}
}

