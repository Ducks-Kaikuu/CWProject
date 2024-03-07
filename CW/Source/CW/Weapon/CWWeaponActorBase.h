// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWWeaponActorBase.generated.h"

UCLASS()
class CW_API ACWWeaponActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	//! @{@name デフォルトコンストラクタ
	ACWWeaponActorBase();
	//! @}
	
	//! @{@name オーナーアクターにアタッチ
	void AttachToOwner(FName SocketName);
	//! @}

	virtual FName GetLaunchSocketName() const ;
	
	// Called every frame
//	virtual void Tick(float DeltaTime) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	

};

FORCEINLINE FName ACWWeaponActorBase::GetLaunchSocketName() const
{
	return FName(TEXT("Launch"));
}
