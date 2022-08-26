// Fill out your copyright notice in the Description page of Project Settings.

#include "DemoCharacter.h"
#include "../Weapon/WeaponBase.h"
#include "../Components/CombatComponent.h"
#include "Net/UnrealNetwork.h"

ADemoCharacter::ADemoCharacter(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	Combat = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
	Combat->SetIsReplicated(true);
}

void ADemoCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ADemoCharacter, OverlappedWeapon, COND_OwnerOnly);
}

void ADemoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("EquipAction", IE_Pressed, this, &ADemoCharacter::EquipKeyPressed);
}

void ADemoCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (Combat)
	{
		Combat->Character = this;
	}
}

void ADemoCharacter::EquipKeyPressed()
{

}

void ADemoCharacter::OnRep_OverlappedWeapon(AWeaponBase* LastWeapon)
{
	if (OverlappedWeapon)
	{
		OverlappedWeapon->ShowPickupWidget(false);
	}
	if (LastWeapon)
	{
		LastWeapon->ShowPickupWidget(false);
	}
}

void ADemoCharacter::SetOverlappedWeapon(AWeaponBase* Weapon)
{
	if (OverlappedWeapon)
	{
		OverlappedWeapon = false;
	}
	OverlappedWeapon = Weapon;
	// if the server controlled character is overlapping weapon
	if (IsLocallyControlled())
	{
		if (OverlappedWeapon)
		{
			OverlappedWeapon->ShowPickupWidget(true);
		}
	}
}
