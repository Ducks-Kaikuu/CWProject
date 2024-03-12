// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/Action/CWVehicleShoot.h"

#include "CW/CWDef.h"
#include "CW/System/CWGameInstance.h"
#include "CW/Scene/CWBattleScene.h"
#include "CW/Bullet/CWBulletManager.h"
#include "CW/Bullet/CWBulletBase.h"
#include "CW/Vehicle/CWWheeledVehiclePawn.h"
#include "CW/Weapon/CWWeaponActorBase.h"

#include "Kismet/KismetSystemLibrary.h"

void UCWVehicleShoot::ExecAction(const FInputActionValue& InputActionValue){
	
	Super::ExecAction(InputActionValue);
	
	if(UKismetSystemLibrary::IsServer(GetWorld()) == true){
		// バトルのシーン情報を取得
		ACWBattleScene* BattleScene(Cast<ACWBattleScene>(GetCWGameInstance()->GetCurrentScene()));
		// シーンがない場合は終了
		if(BattleScene == nullptr){
			
			CW_WARNING(TEXT("Battle Scene is not Found.[Bullet]"));
			
			return;
		}
		// 弾管理クラスを取得
		UCWBulletManager* BulletManager(BattleScene->GetBulletManager());
		
		if(BulletManager != nullptr){
			// 弾を取得
			ACWBulletBase* Bullet = BulletManager->GetBullet(FName(TEXT("Normal")));
			
			if(Bullet != nullptr){
				
				Bullet->SetValidation(true);
				
				ACWWheeledVehiclePawn* Vehicle(GetOwner<ACWWheeledVehiclePawn>());
				
				if(Vehicle != nullptr){
					
					ACWWeaponActorBase* Weapon(Vehicle->GetWeapon(FName(TEXT("Left"))));
					
					if(Weapon != nullptr){
						
						FTransform Transform(Weapon->GetLaunchTransform());
						
						Bullet->SetActorTransform(Transform);
					}
				}
			}
		}
	}
}
