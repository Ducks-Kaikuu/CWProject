// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CW/Bullet/CWBulletData.h"
#include "Components/ActorComponent.h"
#include "CWBulletManager.generated.h"


UCLASS(Blueprintable, Meta = (BlueprintSpawnableComponent))
class CW_API UCWBulletManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCWBulletManager();
	
	void SetupBulletDataAsset();

	void RequestSpawn(const FName& Key, const TSoftClassPtr<ACWBulletBase>& BulletClass, int Num);

	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override ;

	ACWBulletBase* GetBullet(const FName& Name);

	void RecycleBullet(ACWBulletBase* Bullet);
	
protected:

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override ;

	void RegistBullet(const FName& Name, ACWBulletBase* Bullet);
	
private:

	void SpawnBullet(TSubclassOf<ACWBulletBase> Class, const FName& Key);

	bool ExecSpawnBullet();
	
	//!< 1回のスポーン処理で生成可能な弾の数
	UPROPERTY(EditAnywhere, Category="Settings", meta=(ClampMin=10))
	int Distributed = 10;
	
	//!< 弾管理用のリスト
	UPROPERTY()
	TMap<FName, FCWBullet> BulletMap;
};
