// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CW/UI/Widget/CWUserWidgetBase.h"
#include "CWMatchingJoinSessionMenu.generated.h"

class UCWButton;
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnJoinButtonClicked, const FString&, SessionName);

class UCWRoomItem;
class UListView;
class UTileView;
/**
 * 
 */
UCLASS()
class CW_API UCWMatchingJoinSessionMenu : public UCWUserWidgetBase
{
	GENERATED_BODY()

public:

	bool Initialize() override;

	UCWRoomItem* CreateRoomItem(const FString& SessionName, int ConnectionNum);

	FOnJoinButtonClicked OnJoinButtonClickedDelegate;

	UListView* GetRoomList();
	
private:

	UFUNCTION()
	void OnJoinButtonClicked(UCWButton* Button);
	
	UPROPERTY()
	TObjectPtr<UListView> RoomList = nullptr;
};

FORCEINLINE UListView* UCWMatchingJoinSessionMenu::GetRoomList()
{
	return RoomList;
}
