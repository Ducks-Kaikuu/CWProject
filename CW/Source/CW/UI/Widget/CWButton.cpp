// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/UI/Widget/CWButton.h"
#include "CW/CWDef.h"

//----------------------------------------------------------------------//
//
//! @brief デフォルトコンストラクタ
//
//! @param ObjectInitializer イニシャライザ
//
//----------------------------------------------------------------------//
UCWButton::UCWButton(const FObjectInitializer& ObjectInitializer)
:Super(ObjectInitializer)
{
	
	OnClicked.AddDynamic(this, &UCWButton::OnButtonClicked);
	OnHovered.AddDynamic(this, &UCWButton::OnButtonHovered);
	OnUnhovered.AddDynamic(this, &UCWButton::OnButtonUnhovered);
}

//----------------------------------------------------------------------//
//
//! @brief 破棄前の処理
//
//----------------------------------------------------------------------//
void UCWButton::BeginDestroy(){
	
	Super::BeginDestroy();
	// デリゲートをクリア
	OnClickedDelegate.Clear();
	OnHoveredDelegate.Clear();
	OnUnhoveredDelegate.Clear();
	
	OnClicked.RemoveDynamic(this, &UCWButton::OnButtonClicked);
	OnHovered.RemoveDynamic(this, &UCWButton::OnButtonHovered);
	OnUnhovered.RemoveDynamic(this, &UCWButton::OnButtonUnhovered);
}

void UCWButton::OnButtonClicked(){
	
	CW_LOG(TEXT("OnButtonClicked %s"), *GetName());
	
	if(OnClickedDelegate.IsBound()){
		OnClickedDelegate.Broadcast(this);
	}
}

void UCWButton::OnButtonHovered(){
	
	CW_LOG(TEXT("OnButtonHovered %s"), *GetName());
	
	if(OnHoveredDelegate.IsBound()){
		OnHoveredDelegate.Broadcast(this);
	}
}

void UCWButton::OnButtonUnhovered(){
	
	CW_LOG(TEXT("OnButtonUnhovered %s"), *GetName());
	
	if(OnUnhoveredDelegate.IsBound()){
		OnUnhoveredDelegate.Broadcast(this);
	}
}

void UCWButton::SetRootWidget(UCWUserWidgetBase* Root)
{
	RootWidget = Root;
}

UCWUserWidgetBase* UCWButton::GetRootWidget()
{
	return RootWidget;
}


