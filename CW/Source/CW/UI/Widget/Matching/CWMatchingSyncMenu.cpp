// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/UI/Widget/Matching/CWMatchingSyncMenu.h"

#include "Components/TextBlock.h"
#include "CW/Scene/StateTree/CWMatchingSyncTask.h"


bool UCWMatchingSyncMenu::Initialize()
{
	bool bResult = Super::Initialize();

	SessionName = Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("MatchingSessionName"))));
	
	return bResult;
}

void UCWMatchingSyncMenu::SetSessionName(const FName& Name)
{
	if(SessionName != nullptr)
	{
		SessionName->SetText(FText::FromString(Name.ToString()));
	}
}
