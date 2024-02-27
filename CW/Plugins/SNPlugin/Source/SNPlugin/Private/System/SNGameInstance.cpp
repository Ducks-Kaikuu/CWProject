// Fill out your copyright notice in the Description page of Project Settings.

#include "System/SNGameInstance.h"


UWorld* GetPrimaryWorld(){
	
	UWorld* ReturnVal = nullptr;
	
	if(GEngine != nullptr){
		
		for(auto It = GEngine->GetWorldContexts().CreateConstIterator(); It; ++It){
			
			const FWorldContext& Context = *It;
			
			if((Context.WorldType == EWorldType::Game || Context.WorldType == EWorldType::PIE) && Context.World()){
				
				ReturnVal = Context.World();
				break;
			}
		}
	}
	
	return ReturnVal;
}
