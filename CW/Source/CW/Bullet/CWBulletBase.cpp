// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/Bullet/CWBulletBase.h"

// Sets default values
ACWBulletBase::ACWBulletBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// 最初はTickをOFF
	PrimaryActorTick.bStartWithTickEnabled = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent")));
	
	SetActorTickEnabled(false);
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

	FVector Vec(Speed, 0, 0);

	Vec = StartTransform.TransformVector(Vec);

	FVector Pos(GetActorLocation());

	Pos += Vec;

	SetActorLocation(Pos);
}

void ACWBulletBase::SetValidation(bool bValidate)
{
	// コリジョンの設定
	SetActorEnableCollision(bValidate);
	// ゲーム内での表示設定
	SetActorHiddenInGame(!bValidate);
	// Tickの設定
	SetActorTickEnabled(bValidate);
}

void ACWBulletBase::SetStartTransform(const FTransform& Transform)
{
	// スタートトランスフォームを覚えておく
	StartTransform = Transform;

	SetActorTransform(Transform);
}

