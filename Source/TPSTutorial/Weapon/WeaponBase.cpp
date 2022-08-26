// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "../Character/DemoCharacter.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;
	// whether this actor replicates to network clients
	// Properties flagged for replication will update on clients if they change on the server
	bReplicates = true;  

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);
	SetRootComponent(WeaponMesh);

	WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AreaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AreaSphere"));
	AreaSphere->SetupAttachment(RootComponent);
	// specified for multiplayer games: 
	// handle pickup detection only on the server
	AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	PickupWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickupWidget"));
	PickupWidget->SetupAttachment(RootComponent);
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("AWeaponBase::BeginPlay"));
	if (PickupWidget)
	{
		PickupWidget->SetVisibility(false);
	}
	
	// check if run on server
	if (GetLocalRole() == ENetRole::ROLE_Authority) // HasAuthority()
	{
		AreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		AreaSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		AreaSphere->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBase::OnSphereOverlap);
		AreaSphere->OnComponentEndOverlap.AddDynamic(this, &AWeaponBase::OnSphereEndOverlap);
	}
}

void AWeaponBase::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActer, UPrimitiveComponent* OthrComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADemoCharacter* OtherCharacter = Cast<ADemoCharacter>(OtherActer);
	if (OtherCharacter)
	{
		//PickupWidget->SetVisibility(true);
		OtherCharacter->SetOverlappedWeapon(this);
	}
}

void AWeaponBase::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActer, UPrimitiveComponent* OthrComp, int32 OtherBodyIndex)
{
	ADemoCharacter* OtherCharacter = Cast<ADemoCharacter>(OtherActer);
	if (OtherCharacter)
	{
		OtherCharacter->SetOverlappedWeapon(nullptr);
	}
}

void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::ShowPickupWidget(bool bShowWidget)
{
	if (PickupWidget)
	{
		PickupWidget->SetVisibility(bShowWidget);
	}
}

