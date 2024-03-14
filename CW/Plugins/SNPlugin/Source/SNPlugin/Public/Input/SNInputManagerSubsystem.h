// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SNInputManagerSubsystem.generated.h"

class UInputMappingContext;
/**
 * 
 */
UCLASS()
class SNPLUGIN_API USNInputManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void Initialize(FSubsystemCollectionBase& Collection) override;

	void AddInputContext(const FName& Name, UInputMappingContext* InputMappingContext);

	void SetInputMapping(const FName& Name, bool bClearMapping=true);
	
private:
	UPROPERTY()
	TMap<FName, TObjectPtr<UInputMappingContext>> InputMapContextMap;
};
