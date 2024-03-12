#include "CW/Bullet/CWBulletData.h"

#include "CW/CWDef.h"
#include "CW/Bullet/CWBulletBase.h"

FCWBullet::FCWBullet()
	:RequestNum(0)
{
	EmptyBullet.Empty();
	UsedBullet.Empty();
}

void FCWBullet::RegistBullet(ACWBulletBase* Bullet)
{
	EmptyBullet.Add(Bullet);
}


bool FCWBullet::LoadClass(const TSoftClassPtr<ACWBulletBase>& BulletClass)
{
	ClassPtr = Cast<UClass>(BulletClass.LoadSynchronous());

	return (ClassPtr != nullptr);
}

ACWBulletBase* FCWBullet::GetBullet()
{
	if(EmptyBullet.Num() <= 0)
	{
		return nullptr;
	}

	ACWBulletBase* Bullet(EmptyBullet.Pop());

	UsedBullet.Add(Bullet);

	return Bullet;
}

void FCWBullet::RecycleBullet(ACWBulletBase* Bullet)
{
	// 使用中リストから削除
	UsedBullet.Remove(Bullet);
	// 弾のコリジョンをOFF
	Bullet->SetActorEnableCollision(false);
	// 弾を見えないように設定
	Bullet->SetActorHiddenInGame(true);
	// 未使用リストに登録
	EmptyBullet.Add(Bullet);
}

void FCWBullet::SetRequestNum(int Num)
{
	RequestNum = Num;
}

int FCWBullet::GetRequestNum() const
{
	return RequestNum;
}

UClass* FCWBullet::GetClassPtr() const
{
	return ClassPtr;
}

