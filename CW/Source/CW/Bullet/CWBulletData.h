#pragma once

#include "CoreMinimal.h"
#include "CWBulletData.generated.h"

class ACWBulletBase;

USTRUCT()
struct FCWBullet
{
	GENERATED_BODY()

	FCWBullet();

	bool LoadClass(const TSoftClassPtr<ACWBulletBase>& BulletClass);

	void RegistBullet(ACWBulletBase* Bullet);

	ACWBulletBase* GetBullet();

	void RecycleBullet(ACWBulletBase* Bullet);
	
	void SetRequestNum(int Num);

	int GetRequestNum() const ;

	UClass* GetClassPtr() const ;
	
private:
	
	UPROPERTY()
	int RequestNum = 0;

	UPROPERTY()
	TObjectPtr<UClass> ClassPtr;
	
	UPROPERTY()
	TArray<TObjectPtr<ACWBulletBase>> EmptyBullet;

	UPROPERTY()
	TArray<TObjectPtr<ACWBulletBase>> UsedBullet;
	
};
