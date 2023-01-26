// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "Blueprint/UserWidget.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (hudOverlayAsset)
	{
		hudOverlay = CreateWidget<UUserWidget>(this, hudOverlayAsset);
	}
	hudOverlay->AddToViewport();

	hudOverlay->SetVisibility(ESlateVisibility::Visible);


}