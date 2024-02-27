// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace CWGameplayTags
{
	CW_API	FGameplayTag FindTagByString(const FString& TagString, bool bMatchPartialString = false);
	
}
