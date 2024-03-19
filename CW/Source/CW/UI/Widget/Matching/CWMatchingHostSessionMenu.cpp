// Fill out your copyright notice in the Description page of Project Settings.


#include "CWMatchingHostSessionMenu.h"

#include "Components/ComboBoxString.h"
#include "Components/EditableTextBox.h"
#include "CW/UI/Widget/CWButton.h"

bool UCWMatchingHostSessionMenu::Initialize()
{
	bool Result = Super::Initialize();

	SessionName = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("Name")));

	ConnectionNum = Cast<UComboBoxString>(GetWidgetFromName(TEXT("ConnectNum")));

	CreateButton = Cast<UCWButton>(GetWidgetFromName(TEXT("Create")));

	CancelButton = Cast<UCWButton>(GetWidgetFromName(TEXT("Cancel")));
	
	return Result;
}

FName UCWMatchingHostSessionMenu::GetSessionName() const
{
	if(SessionName == nullptr)
	{
		return NAME_None;
	}

	FText Text(SessionName->GetText());

	return *Text.ToString();
}

int UCWMatchingHostSessionMenu::GetConnectionNum() const
{
	if(ConnectionNum == nullptr)
	{
		return -1;
	}

	int index = ConnectionNum->GetSelectedIndex();

	FString option = ConnectionNum->GetSelectedOption();

	int num = FCString::Atoi(*option);
	
	return num;
}

