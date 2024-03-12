// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWBulletBase.generated.h"

UCLASS()
class CW_API ACWBulletBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACWBulletBase();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetBulletKey(FName Key);
	
	FName GetBulletKey() const ;

	void SetValidation(bool bValidate);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	FName BulletKey = NAME_None;
};

FORCEINLINE FName ACWBulletBase::GetBulletKey() const
{
	return BulletKey;
}

FORCEINLINE void ACWBulletBase::SetBulletKey(FName Key)
{
	BulletKey = Key;
}
