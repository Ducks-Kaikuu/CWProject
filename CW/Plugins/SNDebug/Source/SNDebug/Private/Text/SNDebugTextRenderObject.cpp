// Fill out your copyright notice in the Description page of Project Settings.
#include "Text/SNDebugTextRenderObject.h"
#include "CanvasItem.h"
#include "Engine/Canvas.h"

//----------------------------------------------------------------------//
//
//! @brief �f�t�H���g�R���X�g���N�^
//
//----------------------------------------------------------------------//
USNDebugTextRenderObject::USNDebugTextRenderObject()
: Key(0)
{
	
}

//----------------------------------------------------------------------//
//
//! @brief �f�X�g���N�^
//
//----------------------------------------------------------------------//
USNDebugTextRenderObject::~USNDebugTextRenderObject(){
	DebugTextList.Empty();
}

//----------------------------------------------------------------------//
//
//! @brief �X�V����
//
//! @param DeltaTime �o�ߎ���
//
//----------------------------------------------------------------------//
void USNDebugTextRenderObject::Tick(float DeltaTime){
	
	TArray<int32> removeList;
	
	for(auto& element : DebugTextList){
		
		FSNDebugTextParam& param(element.Value);
		// ���C�u�^�C���̃`�F�b�N
		if(param.lifeTime >= 0.0f){
			param.lifeTime -= DeltaTime;
		} else {
			// ���C�t�^�C����0�����������폜
			if(param.lifeTime < 0.0f){
				
				removeList.Add(param.key);
				
				continue;
			}
		}
	}
	// ���X�g����폜
	for(int32& removeVal : removeList){
		DebugTextList.Remove(removeVal);
	}
	// �z��𐮗�
	DebugTextList.Compact();
}

//----------------------------------------------------------------------//
//
//! @brief �`�揈��
//
//! @param pCanvas �`�悷��L�����o�X�ւ̃|�C���^
//
//----------------------------------------------------------------------//
void USNDebugTextRenderObject::Draw(UCanvas* pCanvas){
	// �\�����镶���񂪂Ȃ��ꍇ�͏������Ȃ�
	if(DebugTextList.Num() <= 0){
		return;
	}
	// null�`�F�b�N
	if(pCanvas == nullptr){
		return;
	}
	
	UFont* pFont = GEngine->GetSmallFont();
	
	for(auto& element : DebugTextList){
		
		FSNDebugTextParam& param = element.Value;
		
		FCanvasTextItem TextItem(FVector2D(param.screenPos.X, param.screenPos.Y), FText::FromString(param.str), pFont, param.color);
		
		TextItem.EnableShadow(FLinearColor::Black);
		
		TextItem.Scale.X = param.scale;
		TextItem.Scale.Y = param.scale;
		// �������`��
		pCanvas->DrawItem(TextItem);
	}
}

//----------------------------------------------------------------------//
//
//! @brief �\�����镶�����ǉ�
//
//! @param text           �\�����镶����
//! @param color          �J���[
//! @param screenX        �X�N���[�����WX
//! @param screenY        �X�N���[�����WY
//! @param lifeTime       �\������
//! @param pFont          �t�H���g
//! @param scale          �X�P�[��
//! @param bScalePosition �X�P�[�����|�W�V�����ɔ��f�����邩
//
//----------------------------------------------------------------------//
void USNDebugTextRenderObject::AddString(const FString& text, FLinearColor color, float screenX, float screenY, float lifeTime, UFont* pFont, float scale, bool bScalePosition){
	// int32�ő�l�ɒB������I�[���N���A
	if(Key >= INT32_MAX){
		
		Key = 0;
		
		DebugTextList.Empty();
		
		return;
	}
	
	FSNDebugTextParam param;
	
	param.key				= Key;
	param.str				= text;
	param.lifeTime			= lifeTime;
	param.screenPos.X		= screenX;
	param.screenPos.Y		= screenY;
	param.color				= color;
	param.pFont				= pFont;
	param.scale				= scale;
	param.bScalePosition	= bScalePosition;
	
	DebugTextList.Add(Key, param);
	
	++Key;
}

