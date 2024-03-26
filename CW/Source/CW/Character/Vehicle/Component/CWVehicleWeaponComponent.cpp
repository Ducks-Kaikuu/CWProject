// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/Character/Vehicle/Component/CWVehicleWeaponComponent.h"
#include "CW/CWDef.h"
#include "CW/Character/Vehicle/CWWheeledVehiclePawn.h"

// Sets default values for this component's properties
UCWVehicleWeaponComponent::UCWVehicleWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCWVehicleWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCWVehicleWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCWVehicleWeaponComponent::SetWeapon(FName Name, ACWWeaponActorBase* Weapon){

	ACWWheeledVehiclePawn* Owner = Cast<ACWWheeledVehiclePawn>(GetOwner());

	if(Owner != nullptr)
	{
		if(Name != NAME_None)
		{
			Weapon->AttachToActor(Owner, FAttachmentTransformRules::KeepRelativeTransform, Name);			
		} else
		{
			CW_LOG(TEXT("Weapon Attach Socket Name Is None"));
		}
	}
}

