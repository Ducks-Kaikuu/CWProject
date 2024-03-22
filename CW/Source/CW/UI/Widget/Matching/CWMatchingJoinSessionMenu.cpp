// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/UI/Widget/Matching/CWMatchingJoinSessionMenu.h"

#include "CWRoomItem.h"
#include "Components/TileView.h"
#include "CW/UI/Widget/CWButton.h"

bool UCWMatchingJoinSessionMenu::Initialize()
{
	bool Result = Super::Initialize();

	for(int i=0 ; i<10 ; ++i)
	{
		FString Name = FString::Printf(TEXT("Room%02d"), i);

		UCWRoomItem* RoomItem = Cast<UCWRoomItem>(GetWidgetFromName(FName(*Name)));

		if(RoomItem != nullptr)
		{
			RoomItem->SetVisibility(ESlateVisibility::Hidden);
			
			RoomItemList.Add(RoomItem);
		}
	}

	RoomItem00 = Cast<UCWRoomItem>(GetWidgetFromName(FName(TEXT("Room00"))));
	
	return Result;
}

UCWRoomItem* UCWMatchingJoinSessionMenu::CreateRoomItem(const FString& SessionName, int ConnectionNum)
{
	if(RoomCount >= RoomItemList.Num())
	{
		return nullptr;
	}
	
	UCWRoomItem* RoomItem = RoomItemList[RoomCount];
	
	RoomItem->SetRoom(SessionName, ConnectionNum);
	
	if(UCWButton* Button = RoomItem->GetJoinButton())
	{
		Button->OnClickedDelegate.AddDynamic(this, &UCWMatchingJoinSessionMenu::OnJoinButtonClicked);
	}

	RoomItem->SetVisibility(ESlateVisibility::Visible);
	
	return RoomItem;
}

void UCWMatchingJoinSessionMenu::OnJoinButtonClicked(UCWButton* Button)
{
	UCWRoomItem* RoomItem = Cast<UCWRoomItem>(Button->GetRootWidget());

	if(RoomItem != nullptr)
	{
		OnJoinButtonClickedDelegate.ExecuteIfBound(*RoomItem->GetSessionName());	
	}
	
}

