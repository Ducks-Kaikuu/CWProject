// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/GameplayTags/CWGameplayTags.h"

namespace CWGameplayTags
{
FGameplayTag FindTagByString(const FString& TagString, bool bMatchPartialString){
	
	const UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
	
	FGameplayTag Tag = Manager.RequestGameplayTag(FName(*TagString), false);
	
	if(!Tag.IsValid() && bMatchPartialString){
		
		FGameplayTagContainer AllTags;
		
		Manager.RequestAllGameplayTags(AllTags, true);
		
		for(const FGameplayTag& TestTag : AllTags){
			
			if(TestTag.ToString().Contains(TagString)){
				
				UE_LOG(LogTemp, Display, TEXT("Could not find exact match for tag [%s] but found partial match on tag [%s]."), *TagString, *TestTag.ToString());
				
				Tag = TestTag;
				
				break;
			}
		}
	}
	
	return Tag;
}

}
