// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/Weapon/CWWeaponActorBase.h"

//----------------------------------------------------------------------//
//
//! @brief デフォルトコンストラクタ
//
//----------------------------------------------------------------------//
ACWWeaponActorBase::ACWWeaponActorBase(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// ルートコンポーネントを設定
	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent")));
}

void ACWWeaponActorBase::AttachToOwner(FName SocketName){

//	AActor* Owner = GetOwner();

	if(Owner == nullptr)
	{
		return;
	}

	USkeletalMeshComponent* Mesh = Cast<USkeletalMeshComponent>(Owner->GetComponentByClass(USkeletalMeshComponent::StaticClass()));

	if(Mesh == nullptr)
	{
		return;
	}
	
	AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform, SocketName);
}

// Called when the game starts or when spawned
void ACWWeaponActorBase::BeginPlay(){
	
	Super::BeginPlay();
	
}
#if 0
// Called every frame
void ACWWeaponActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
#endif

