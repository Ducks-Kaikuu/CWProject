// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/Vehicle/Action/CWVehicleShoot.h"

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
		// �o�g���̃V�[�������擾
		ACWBattleScene* BattleScene(Cast<ACWBattleScene>(GetCWGameInstance()->GetCurrentScene()));
		// �V�[�����Ȃ��ꍇ�͏I��
		if(BattleScene == nullptr){
			
			CW_WARNING(TEXT("Battle Scene is not Found.[Bullet]"));
			
			return;
		}
		// �e�Ǘ��N���X���擾
		UCWBulletManager* BulletManager(BattleScene->GetBulletManager());
		
		if(BulletManager != nullptr){
			// �e���擾
			ACWBulletBase* Bullet = BulletManager->GetBullet(FName(TEXT("Normal")));
			
			if(Bullet != nullptr){
				
				Bullet->SetValidation(true);
				
				ACWWheeledVehiclePawn* Vehicle(GetOwner<ACWWheeledVehiclePawn>());
				
				if(Vehicle != nullptr){
					
					ACWWeaponActorBase* Weapon(Vehicle->GetWeapon(FName(TEXT("Left"))));
					
					if(Weapon != nullptr){
						
						FTransform Transform(Weapon->GetLaunchTransform());
						
						Bullet->SetStartTransform(Transform);
					}
				}
			}
		}
	}
}
