#pragma once

#include "CoreMinimal.h"
#include "CWBulletData.generated.h"

class ACWBulletBase;

USTRUCT()
struct FCWBullet
{
	GENERATED_BODY()

	UPROPERTY()
	int RequestNum = 0;

	UPROPERTY()
	TArray<TObjectPtr<ACWBulletBase>> EmptyBullet;

	UPROPERTY()
	TArray<TObjectPtr<ACWBulletBase>> UsedBullet;
	
};
