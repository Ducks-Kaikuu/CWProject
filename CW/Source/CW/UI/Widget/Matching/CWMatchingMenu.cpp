// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/UI/Widget/Matching/CWMatchingMenu.h"

#include "CW/UI/Widget/CWButton.h"

bool UCWMatchingMenu::Initialize()
{
	bool Result = Super::Initialize();
	
	HostSessionButton = Cast<UCWButton>(GetWidgetFromName(TEXT("Host")));
	JoinSessionButton = Cast<UCWButton>(GetWidgetFromName(TEXT("Client")));

	return Result;
}

void UCWMatchingMenu::BeginDestroy()
{
	Super::BeginDestroy();
	
	HostSessionButton = nullptr;
	JoinSessionButton = nullptr;
}
