// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/UI/Widget/Matching/CWRoomItem.h"

#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "CW/CWDef.h"
#include "CW/UI/Widget/CWButton.h"

bool UCWRoomItem::Initialize()
{
	bool Result = Super::Initialize();

	UHorizontalBox* RoomItem = Cast<UHorizontalBox>(GetWidgetFromName(TEXT("RoomItem")));

//	if(RoomItem != nullptr)
	{
		JoinButton = Cast<UCWButton>(GetWidgetFromName(TEXT("Join")));

		if(JoinButton != nullptr)
		{
			JoinButton->SetRootWidget(this);
		}
		
		SessionName = Cast<UTextBlock>(GetWidgetFromName(TEXT("SessionNameText")));

		ConnectionNum = Cast<UTextBlock>(GetWidgetFromName(TEXT("ConnectionNumText")));
	}

	return Result;
}

void UCWRoomItem::SetRoom(const FString& Name, int Num)
{
	if(SessionName != nullptr)
	{
		SessionName->SetText(FText::FromString(Name));

		FText test = SessionName->GetText();

		FString aaa = test.ToString();

		CW_LOG(TEXT("%s"), *aaa);
	}
	
	if(ConnectionNum != nullptr)
	{
		ConnectionNum->SetText(FText::AsNumber(Num));	
	}
}

FString UCWRoomItem::GetSessionName() const
{
	FString Name("");

	if(SessionName != nullptr)
	{
		Name = SessionName->GetText().ToString();
	}

	return Name;
}


