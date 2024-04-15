﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Base/SNCharacterBase.h"

// Sets default values
ASNCharacterBase::ASNCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASNCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASNCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASNCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

