﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SNBlueprintFunctionLibrary.generated.h"

class USNOnlineSystem;
/**
 * 
 */
UCLASS()
class SNPLUGIN_API USNBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category="SN|Online")
	static bool StartupOnlineSystem();

	UFUNCTION(BlueprintCallable, Category="SN|Online")
	static void Login();

	UFUNCTION(BlueprintCallable, Category="SN|Online")
	static void HostSession();
	
	UFUNCTION(BlueprintCallable, Category="SN|Online")
	static void FindSession();

	UFUNCTION(BlueprintCallable, Category="SN|Online")
	static void KillSession();
	
private:
	static USNOnlineSystem* GetOnlineSystem();
};
