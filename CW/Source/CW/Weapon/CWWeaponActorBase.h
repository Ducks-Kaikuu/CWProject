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

	void AttachToOwner(FName SocketName);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
//	virtual void Tick(float DeltaTime) override;

};
