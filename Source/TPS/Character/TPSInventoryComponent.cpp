// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TPSInventoryComponent.h"
#include "TPSGameInstance.h"
#pragma optimize ("", off)

// Sets default values for this component's properties
UTPSInventoryComponent::UTPSInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTPSInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	//Find init weaponsSlots and First Init Weapon
	for (int8 i = 0; i < WeaponSlots.Num(); i++)
	{
		UTPSGameInstance* myGI = Cast<UTPSGameInstance>(GetWorld()->GetGameInstance());
		if (myGI)
		{
			if (!WeaponSlots[i].NameItem.IsNone())
			{
				FWeaponInfo Info;
				if (myGI->GetWeaponInfoByName(WeaponSlots[i].NameItem, Info))
					WeaponSlots[i].AdditionalInfo.Round = Info.MaxRound;
				else
				{
					WeaponSlots.RemoveAt(i);
					i--;
				}
			}
		}
	}

	MaxSlotsWeapon = WeaponSlots.Num();

	if (WeaponSlots.IsValidIndex(0))
	{
		if (!WeaponSlots[0].NameItem.IsNone())
			OnSwitchWeapon.Broadcast(WeaponSlots[0].NameItem, WeaponSlots[0].AdditionalInfo, 0);
	}
}


// Called every frame
void UTPSInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UTPSInventoryComponent::SwitchWeaponToIndex(int32 ChangeToIndex, int32 OldIndex, FAdditionalWeaponInfo OldInfo, bool bIsForward)
{
	bool bIsSuccess = false;
	int8 CorrectIndex = ChangeToIndex;
	if (ChangeToIndex > WeaponSlots.Num() - 1)
		CorrectIndex = 0;
	else
		if (ChangeToIndex < 0)
			CorrectIndex = WeaponSlots.Num() - 1;

	FName NewIdWeapon;
	FAdditionalWeaponInfo NewAdditionalInfo;
	int32 NewCurrentIndex = 0;




	if (WeaponSlots.IsValidIndex(CorrectIndex))
	{
		if (!WeaponSlots[CorrectIndex].NameItem.IsNone())
		{
			if (WeaponSlots[CorrectIndex].AdditionalInfo.Round > 0)
			{
				//good weapon have ammo start change
				bIsSuccess = true;
			}
			else
			{
				UTPSGameInstance* myGI = Cast<UTPSGameInstance>(GetWorld()->GetGameInstance());
				if (myGI)
				{
					//check ammoSlots for this weapon
					FWeaponInfo myInfo;
					myGI->GetWeaponInfoByName(WeaponSlots[CorrectIndex].NameItem, myInfo);

					bool bIsFind = false;
					int8 j = 0;
					while (j < AmmoSlots.Num() && !bIsFind)
					{
						if (AmmoSlots[j].WeaponType == myInfo.WeaponType && AmmoSlots[j].Cout > 0)
						{
							//good weapon have ammo start change
							bIsSuccess = true;
							bIsFind = true;
						}
						j++;
					}
				}
			}
			if (bIsSuccess)
			{
				NewCurrentIndex = CorrectIndex;
				NewIdWeapon = WeaponSlots[CorrectIndex].NameItem;
				NewAdditionalInfo = WeaponSlots[CorrectIndex].AdditionalInfo;
			}
		}


		if (bIsSuccess)
		{
			SetAdditionalInfoWeapon(OldIndex, OldInfo);
			OnSwitchWeapon.Broadcast(NewIdWeapon, NewAdditionalInfo, NewCurrentIndex);
			//OnWeaponAmmoAviable.Broadcast()
		}

		return bIsSuccess;
	}
}
FAdditionalWeaponInfo UTPSInventoryComponent::GetAdditionalInfoWeapon(int32 IndexWeapon)
{
	return FAdditionalWeaponInfo();
}

int32 UTPSInventoryComponent::GetWeaponIndexSlotByName(FName IdWeaponName)
{
	int32 result = -1;
	int8 i = 0;
	bool bIsFind = false;
	while (i < WeaponSlots.Num() && !bIsFind)
	{
		if (WeaponSlots[i].NameItem == IdWeaponName)
		{
			bIsFind = true;
			result = i/*WeaponSlots[i].IndexSlot*/;
		}
		i++;
	}
	return result;
}

void UTPSInventoryComponent::SetAdditionalInfoWeapon(int32 IndexWeapon, FAdditionalWeaponInfo NewInfo)
{
	if (WeaponSlots.IsValidIndex(IndexWeapon))
	{
		bool bIsFind = false;
		int8 i = 0;
		while (i < WeaponSlots.Num() && !bIsFind)
		{
			if (/*WeaponSlots[i].IndexSlot*/i == IndexWeapon)
			{
				WeaponSlots[i].AdditionalInfo = NewInfo;
				bIsFind = true;

				OnWeaponAdditionalInfoChange.Broadcast(IndexWeapon, NewInfo);
			}
			i++;
		}
		if (!bIsFind)
			UE_LOG(LogTemp, Warning, TEXT("UTPSInventoryComponent::SetAdditionalInfoWeapon - No Found Weapon with index - %d"), IndexWeapon);
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("UTPSInventoryComponent::SetAdditionalInfoWeapon - Not Correct index Weapon - %d"), IndexWeapon);
}

bool UTPSInventoryComponent::CheckAmmoForWeapon(EWeaponType TypeWeapon, int8& AviableAmmForWeapon)
{
	AviableAmmoForWeapon = 0;
	bool bIsFind = false;
	int8 i = 0;
	while (i < AmmoSlots.Num() && !bIsFind)
	{
		if (AmmoSlots[i].WeaponType == TypeWeapon)
		{
			bIsFind = true;
			AviableAmmoForWeapon = AmmoSlots[i].Cout;
			if (AmmoSlots[i].Cout > 0)
			{
				//OnWeaponAmmoAviable.Broadcast(TypeWeapon);//remove not here, only when pickUp ammo this type, or swithc weapon
				return true;
			}

		}

		i++;
	}

	OnWeaponAmmoEmpty.Broadcast(TypeWeapon);//visual empty ammo slot

	return false;
}

void UTPSInventoryComponent::AmmoSlotChangeValue(EWeaponType TypeWeapon, int32 CoutChangeAmmo)
{
	bool bIsFind = false;
	int8 i = 0;
	while (i < AmmoSlots.Num() && !bIsFind)
	{
		if (AmmoSlots[i].WeaponType == TypeWeapon)
		{
			AmmoSlots[i].Cout += CoutChangeAmmo;
			if (AmmoSlots[i].Cout > AmmoSlots[i].MaxCout)
				AmmoSlots[i].Cout = AmmoSlots[i].MaxCout;

			OnAmmoChange.Broadcast(AmmoSlots[i].WeaponType, AmmoSlots[i].Cout);

			bIsFind = true;
		}
		i++;
	}
}

