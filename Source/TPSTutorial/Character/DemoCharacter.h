// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ALSCharacter.h"
#include "DemoCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TPSTUTORIAL_API ADemoCharacter : public AALSCharacter
{
	GENERATED_BODY()
	
public:
	ADemoCharacter(const FObjectInitializer& ObjectInitializer);
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
protected:
	void EquipKeyPressed();

private:
	UPROPERTY(ReplicatedUsing = OnRep_OverlappedWeapon)
	class AWeaponBase* OverlappedWeapon;

	UFUNCTION()
	void OnRep_OverlappedWeapon(AWeaponBase* LastWeapon);

	UPROPERTY(VisibleAnywhere)
	class UCombatComponent* Combat;
public:
	void SetOverlappedWeapon(AWeaponBase* Weapon);
};
