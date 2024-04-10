// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SNPlayerController.h"

#include "SNDef.h"
#include "Utility/SNUtility.h"
#include "Input/SNInputConfig.h"
#include "Input/SNInputManagerSubsystem.h"

//----------------------------------------------------------------------//
//
//! @brief �v���C���I�������ۂ̃C�x���g
//
//! @param EndPlayReason �I�����錴��
//
//----------------------------------------------------------------------//
void ASNPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason){
	
	Super::EndPlay(EndPlayReason);
	// ���͊Ǘ��p�}�l�[�W���[���擾
	USNInputManagerSubsystem* InputManagerSubsystem(SNUtility::GetSNInputManagerSubsystem());
	
	if(bInitializedInput == true){
		
		for(auto& InputConfig:InputConfigMap){
			// ���̓}�b�s���O�𖳌���
			InputManagerSubsystem->DisableInputMapping(InputConfig.Key);
			// ���\�[�X�����
			InputConfig.Value->Release();
		}
	}
}

bool ASNPlayerController::InitializeInput(){
	// �I�[�i�[�p�̃|�[�����擾
	APawn* OwnerPawn = GetPawn();
	// 
	SNPLUGIN_ASSERT(OwnerPawn != nullptr, TEXT("Pawn is nullptr. This function should be called from Pawn's SetupPlayerInputComponent."));
	// ����������
	for(auto& InputConfig:InputConfigMap){
		InputConfig.Value->InitializeInput(InputConfig.Key, OwnerPawn);
	}
	
	SNPLUGIN_LOG(TEXT("Input Config Initialize."));
	
	bInitializedInput = true;
	
	if(CurrentInputTypes.Num() > 0){
		// �J�����g�ɐݒ肳��Ă���^�C�v��ݒ�
		for(auto& Name:CurrentInputTypes){
			EnabledInputType(Name, false);
		}
	}

	return true;
}

void ASNPlayerController::EnabledInputType(FName Name, bool bClearAll){
	
	if(bClearAll){
		// �J�����g�^�C�v���N���A
		CurrentInputTypes.Empty();
	}
	
	CurrentInputTypes.Add(Name);
	
	if(bInitializedInput == true){
		
		USNInputManagerSubsystem* InputManagerSubsystem(SNUtility::GetSNInputManagerSubsystem());
		// �w�肳�ꂽ�}�b�s���O��L����
		InputManagerSubsystem->EnableInputMapping(Name, bClearAll);
		
		SNPLUGIN_LOG(TEXT("Current Input Type : %s"), *Name.ToString());
	}
}

void ASNPlayerController::DisableInputType(FName Name){
	
	CurrentInputTypes.Remove(Name);
	
	if(bInitializedInput == true){
		
		USNInputManagerSubsystem* InputManagerSubsystem(SNUtility::GetSNInputManagerSubsystem());
		
		InputManagerSubsystem->DisableInputMapping(Name);
		
		SNPLUGIN_LOG(TEXT("Disable Input Type : %s"), *Name.ToString());
	}
}
