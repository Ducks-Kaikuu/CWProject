// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/UI/Widget/Matching/CWMatchingJoinSessionMenu.h"

#include "CWRoomItem.h"
#include "Components/TileView.h"
#include "CW/UI/Widget/CWButton.h"

bool UCWMatchingJoinSessionMenu::Initialize()
{
	bool Result = Super::Initialize();

	RoomList = Cast<UListView>(GetWidgetFromName(FName(TEXT("Room"))));

	return Result;
}

UCWRoomItem* UCWMatchingJoinSessionMenu::CreateRoomItem(const FString& SessionName, int ConnectionNum)
{
	TSubclassOf<UCWRoomItem> Class(RoomList->GetEntryWidgetClass());
	
	UCWRoomItem* RoomItem = Cast<UCWRoomItem>(CreateWidget(this, Class, *SessionName));

	if(RoomItem != nullptr)
	{
		RoomItem->SetRoom(SessionName, ConnectionNum);

		if(UCWButton* Button = RoomItem->GetJoinButton())
		{
			Button->OnClickedDelegate.AddDynamic(this, &UCWMatchingJoinSessionMenu::OnJoinButtonClicked);
		}
		
		RoomList->AddItem(RoomItem);
	}

	return RoomItem;
}

void UCWMatchingJoinSessionMenu::OnJoinButtonClicked(UCWButton* Button)
{
	UCWRoomItem* RoomItem = Cast<UCWRoomItem>(Button->GetParent());

	if(RoomItem != nullptr)
	{
		OnJoinButtonClickedDelegate.ExecuteIfBound(*RoomItem->GetSessionName());	
	}
	
}

