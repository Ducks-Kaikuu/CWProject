// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/Scene/CWSceneBase.h"

#include "AudioMixerDevice.h"
#include "CW/UI/Widget/CWMasterWidget.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACWSceneBase::ACWSceneBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// 最初はTickをOFF
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	SetActorTickEnabled(false);
	// ルートを設定
	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent")));
}

// Called when the game starts or when spawned
void ACWSceneBase::BeginPlay()
{
	Super::BeginPlay();

	if(MasterWidgetClass.IsNull() == false)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		
		UClass* Class = Cast<UClass>(MasterWidgetClass.LoadSynchronous());

		if(Class != nullptr)
		{
			MasterWidget = CreateWidget<UCWMasterWidget>(PlayerController, Class, FName(TEXT("MasterWidget")));

			if(MasterWidget != nullptr)
			{
				//
				MasterWidget->Init();
				
				if((MasterWidget->IsInViewport() == false) && (MasterWidget->GetParent() == nullptr))
				{
					MasterWidget->AddToViewport();
				}
			}
		}
		
	}
}

// Called every frame
void ACWSceneBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

