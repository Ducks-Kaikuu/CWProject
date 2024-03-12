// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/Bullet/CWBulletManager.h"
#include "CW/CWDef.h"
#include "CW/System/CWGameInstance.h"
#include "CW/Bullet//CWBulletBase.h"

#include "Data/SNDataAssetManager.h"
#include "Data/SNContentsAsset.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

//----------------------------------------------------------------------//
//
//! @brief デフォルトコンストラクタ
//
//----------------------------------------------------------------------//
UCWBulletManager::UCWBulletManager(){
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// Tickを回さない
	SetComponentTickEnabled(false);
	
	SetIsReplicatedByDefault(true);
	
	SetNetAddressable();
	
	BulletMap.Empty();
	// ...
}

void UCWBulletManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

//----------------------------------------------------------------------//
//
//! @brief 弾データのアセットを初期化
//
//----------------------------------------------------------------------//
void UCWBulletManager::SetupBulletDataAsset(){
	// データ管理クラスを取得
	USNDataAssetManager* DataAssetManager(GetCWGameInstance()->GetDataAssetManager());
	// データ管理クラスがない場合はアサート
	CW_ASSERT(DataAssetManager != nullptr, TEXT("Data Asset Manager is null"));
	// 武器のアセットリストを取得
	const USNContentsAsset* BulletAsset(DataAssetManager->GetContentAsset(FName(TEXT("Bullet"))));
	// データ存在するかチェック
	if(BulletAsset == nullptr){
		
		CW_LOG(TEXT("Bullet Data is none"));
		
		return;
	}
	// 
	const TMap<FName, TSoftClassPtr<UObject>>& BulletClassList(BulletAsset->GetContentClassList());
	
	for(auto& Bullet:BulletClassList){
		// クラス情報をキャスト
		TSoftClassPtr<ACWBulletBase> BulletClass(Bullet.Value.ToSoftObjectPath());
		// @@Satoshi Nishimura 2024/03/12
		// 生成する球数が固定値なのでそこは考えないと…
		RequestSpawn(Bullet.Key, BulletClass, 200);
	}
}

//----------------------------------------------------------------------//
//
//! @brief スポーンをリクエスト
//
//! @param BulletClass スポーンする弾丸のクラス情報
//! @param Num         スポーンする数
//
//----------------------------------------------------------------------//
void UCWBulletManager::RequestSpawn(const FName& Key, const TSoftClassPtr<ACWBulletBase>& BulletClass, int Num){
	// 弾丸のスポーンをサーバーのみ
	if(UKismetSystemLibrary::IsServer(GetWorld()) == true){
		// 既に弾丸情報が設定されていないかチェック
		if(BulletMap.Contains(Key) == false){
			// 弾丸情報を追加
			BulletMap.Add(Key, FCWBullet());
			// クラス情報をロード
			BulletMap[Key].LoadClass(BulletClass);
			// スポーンする数を設定
			BulletMap[Key].SetRequestNum(Num);
			// Tickを回すように変更
			SetComponentTickEnabled(true);
		}
	}
}

//----------------------------------------------------------------------//
//
//! @brief 弾丸のインスタンスを登録
//
//! @param Name   弾のアセット名(マップのキー)
//! @param Bullet 弾のインスタンス
//
//----------------------------------------------------------------------//
void UCWBulletManager::RegistBullet(const FName& Name, ACWBulletBase* Bullet){
	// 弾が登録されているかチェック
	if(BulletMap.Contains(Name) == false){
		// この関数が呼ばれるのに弾が登録されていないことはないはず…なので警告を出す
		CW_WARNING(TEXT("Regist Bullet does not contain."));
		// 弾を登録
		BulletMap.Add(Name, FCWBullet());
	}
	// 弾を登録
	BulletMap[Name].RegistBullet(Bullet);
}

//----------------------------------------------------------------------//
//
//! @brief 弾を取得
//
//! @param Name 取得する弾の名前
//
//! @retval 弾のインスタンス
//
//----------------------------------------------------------------------//
ACWBulletBase* UCWBulletManager::GetBullet(const FName& Name){
	// 弾が存在するかチェック
	if(BulletMap.Contains(Name) == false){
		// 警告
		CW_WARNING(TEXT("Bullet designation is invalid.[%s]"), *Name.ToString());
		
		return nullptr;
	}
	// 弾を取得
	ACWBulletBase* Bullet = BulletMap[Name].GetBullet();
	
#if !UE_BUILD_SHIPPING
	// nullチェック
	if(Bullet == nullptr){
		CW_WARNING(TEXT("Not enough bullets.[%s]"), *Name.ToString());
	}
#endif
	
	return Bullet;
}

//----------------------------------------------------------------------//
//
//! @brief 弾のリサイクル処理
//
//! @param Bullet 未使用に変更する弾のインスタンス
//
//----------------------------------------------------------------------//
void UCWBulletManager::RecycleBullet(ACWBulletBase* Bullet){
	
	if(Bullet == nullptr){
		return;
	}
	// 弾の名前を取得
	FName Name(Bullet->GetBulletKey());
	// 管理リストに存在するかチェック
	if(BulletMap.Contains(Name) == false){
		// 存在しない場合はアサート
		CW_ASSERT(false, TEXT("Uncontrolled bullets materialise."));
	}
	// 弾をリサイクル
	BulletMap[Name].RecycleBullet(Bullet);
}

//----------------------------------------------------------------------//
//
//! @brief 毎フレームの更新処理
//
//! @param DeltaTime        経過時間
//! @param TickType         Tickのタイプ
//! @param ThisTickFunction TickFunction
//
//----------------------------------------------------------------------//
void UCWBulletManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// 弾を生成
	if(ExecSpawnBullet() == false){
		SetComponentTickEnabled(false);
	}
}

//----------------------------------------------------------------------//
//
//! @brief 弾を生成
//
//! @param Class 弾のクラス情報
//! @param Key   弾のアセット名(Mapのキー情報)
//
//----------------------------------------------------------------------//
void UCWBulletManager::SpawnBullet(TSubclassOf<ACWBulletBase> Class, const FName& Key){
	// プレイヤーコントローラを取得
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	// 見つからない場合はアサート
	CW_ASSERT(PlayerController != nullptr, TEXT("Player Controller is nullptr"));
	
	FActorSpawnParameters Parameters;
	
	Parameters.Owner = PlayerController;
	// プレイヤーコントローラを親にして弾を生成
	ACWBulletBase* Bullet = Cast<ACWBulletBase>(GetWorld()->SpawnActor(Class.Get(), nullptr, Parameters));
	
	if(Bullet != nullptr){
		// 弾を無効化
		Bullet->SetValidation(false);
		// 弾のキー情報を設定
		Bullet->SetBulletKey(Key);
		// 弾を登録
		RegistBullet(Key, Bullet);
	}
}

//----------------------------------------------------------------------//
//
//! @brief 弾の生成処理を実行
//
//! @retval true  弾を生成しました。
//! @retval false 弾の生成はされませんでした。
//
//----------------------------------------------------------------------//
bool UCWBulletManager::ExecSpawnBullet(){
	// サーバー以外では処理をさせない
	if(UKismetSystemLibrary::IsServer(GetWorld()) == false){
		return false;
	}
	// スポーンを行ったかどうかのフラグ
	bool bDoSpawn = false;
	// 1回のスポーン処理でスポーン可能な数を設定
	int Num = Distributed;
	
	for(auto& BulletData:BulletMap){
		// 残り生成するべき個数を取得
		int RequestNum = BulletData.Value.GetRequestNum();
		// リクエスト数が上限値を超えてる場合は上限値分スポーン
		int GenerateNum = (RequestNum > Num) ? Num : RequestNum;
		
		for(int i=0 ; i<GenerateNum ; ++i){
			// 弾をスポーン
			SpawnBullet(BulletData.Value.GetClassPtr(), BulletData.Key);
		}
		// リクエスト数を更新
		BulletData.Value.SetRequestNum(RequestNum - GenerateNum);
		// 生成数が0より大きい場合はフラグを有効化
		if(GenerateNum > 0){
			bDoSpawn = true;
		}
		// 生成可能な数を更新
		Num = Num - GenerateNum;
		// 生成可能な数が0以下になった場合はこのフレームでのスポーンを終了
		if(Num <= 0){
			break;
		}
	}
	
	return bDoSpawn;
}

