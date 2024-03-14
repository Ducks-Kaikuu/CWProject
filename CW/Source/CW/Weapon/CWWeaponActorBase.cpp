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

	bNetLoadOnClient = true;
	
	SetReplicates(true);
}

void ACWWeaponActorBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const 
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

//----------------------------------------------------------------------//
//
//! @brief オーナーへアタッチ
//
//! @param SocketName アタッチするソケットの名前
//
//----------------------------------------------------------------------//
void ACWWeaponActorBase::AttachToOwner(FName SocketName){
	// オーナーがいるかチェック
	if(Owner == nullptr){
		return;
	}
	// オーナーのスケルタルメッシュを取得
	USkeletalMeshComponent* Mesh(Cast<USkeletalMeshComponent>(Owner->GetComponentByClass(USkeletalMeshComponent::StaticClass())));
	
	if(Mesh == nullptr){
		return;
	}
	// アタッチ
	AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform, SocketName);
}

// Called when the game starts or when spawned
void ACWWeaponActorBase::BeginPlay(){
	
	Super::BeginPlay();
	
}

FTransform ACWWeaponActorBase::GetLaunchTransform() const
{
	USkeletalMeshComponent* Mesh(Cast<USkeletalMeshComponent>(GetComponentByClass(USkeletalMeshComponent::StaticClass())));

	if(Mesh == nullptr)
	{
		return FTransform::Identity;
	}

	return Mesh->GetSocketTransform(GetLaunchSocketName());
}
#if 0
// Called every frame
void ACWWeaponActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
#endif

