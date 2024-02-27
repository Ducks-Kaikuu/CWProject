// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SNDebugTextRenderObject.generated.h"

//----------------------------------------------------------------------//
//----------------------------------------------------------------------//
struct FSNDebugTextParam{
	
	int32			key;
	FString			str;
	float			lifeTime;
	FVector			screenPos;
	FLinearColor	color;
	UFont*			pFont;
	float			scale;
	bool			bScalePosition;
	
	FSNDebugTextParam()
	: key(0)
	, str("")
	, lifeTime(0.0f)
	, screenPos(FVector::ZeroVector)
	, color(FColor::White)
	, pFont(NULL)
	, scale(1.0f)
	, bScalePosition(false)
	{
	}
};

//----------------------------------------------------------------------//
//
//! @brief �f�o�b�O�p�̕`��I�u�W�F�N�g
//
//----------------------------------------------------------------------//
UCLASS()
class SNDEBUG_API USNDebugTextRenderObject : public UObject
{
	GENERATED_BODY()
	
public:
	//! @{@name �f�t�H���g�R���X�g���N�^
	USNDebugTextRenderObject();
	//! @}
	
	//! @{@name �f�X�g���N�^
	~USNDebugTextRenderObject();
	//! @}
	
	//! @{@name �X�V����
	void Tick(float DeltaTime);
	//! @}
	
	//! @{@name �`�揈��
	void Draw(UCanvas* pCanvas);
	//! @}
	
	//! @{@name �\������f�o�b�O������o�^
	void AddString(const FString& text, FLinearColor color, float screenX, float screenY, float lifeTime, UFont* pFont, float scale, bool bScalePosition);
	//! @}
	
private:
	//!< �f�o�b�O�e�L�X�g
	TMap<int32, FSNDebugTextParam> DebugTextList;
	//!< �L�[���
	int32 Key;
};
