// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CW/UI/Widget/CWUserWidgetBase.h"
#include "CWRoomItem.generated.h"

class UTextBlock;
class UCWButton;
/**
 * 
 */
UCLASS()
class CW_API UCWRoomItem : public UCWUserWidgetBase
{
	GENERATED_BODY()

public:
	
	bool Initialize() override;

	void SetRoom(const FString& Name, int Num);

	UCWButton* GetJoinButton();

	FString GetSessionName() const ;
	
private:
	UPROPERTY()
	TObjectPtr<UCWButton> JoinButton = nullptr;

	UPROPERTY()
	TObjectPtr<UTextBlock> SessionName = nullptr;

	UPROPERTY()
	TObjectPtr<UTextBlock> ConnectionNum = nullptr;
};

FORCEINLINE UCWButton* UCWRoomItem::GetJoinButton()
{
	return JoinButton;
}

