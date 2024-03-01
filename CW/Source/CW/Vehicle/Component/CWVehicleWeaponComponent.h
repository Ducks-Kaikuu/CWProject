// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CW/Weapon/CWWeaponActorBase.h"
#include "CWVehicleWeaponComponent.generated.h"


UCLASS( Blueprintable, meta=(BlueprintSpawnableComponent) )
class CW_API UCWVehicleWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCWVehicleWeaponComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetWeapon(FName Name, ACWWeaponActorBase* Weapon);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere, Category="CW|Weapon")
	TMap<FName, TObjectPtr<ACWWeaponActorBase>> EquipWeaponMap;
};
