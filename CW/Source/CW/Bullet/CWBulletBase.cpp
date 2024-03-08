// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/Bullet/CWBulletBase.h"

// Sets default values
ACWBulletBase::ACWBulletBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACWBulletBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACWBulletBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

