// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FiaUserWidget.h"

#include "FIA/FIA.h"
#include "System/EventManagerSubsystem.h"


void UFiaUserWidget::NativeConstruct()
{
	BindEventManager();
	Super::NativeConstruct();
}

void UFiaUserWidget::NativeDestruct()
{
	UnBindEventManager();
	Super::NativeDestruct();
}

void UFiaUserWidget::BindEventManager()
{
	const UWorld* World = GetWorld();
	if (!World)
	{
		FIA_LOG("World Not Found in Fia User Widget Bind Event Manager");
		return;
	} 
	EventManagerSubsystem = World->GetSubsystem<UEventManagerSubsystem>();
	if (!EventManagerSubsystem)
	{
		FIA_LOG("Event Manager Subsystem Not Found in Fia User Widget Bind Event Manager");
		return;
	}
	EventManagerSubsystem->OnPlayerOpenedChest.AddUniqueDynamic(this, &UFiaUserWidget::OnPlayerOpenedChest);
	EventManagerSubsystem->OnQuizLoaded.AddUniqueDynamic(this, &UFiaUserWidget::OnQuizLoaded);
	EventManagerSubsystem->OnPlayerMissed.AddUniqueDynamic(this, &UFiaUserWidget::OnPlayerMissed);
	EventManagerSubsystem->OnPlayerAnswered.AddUniqueDynamic(this, &UFiaUserWidget::OnPlayerAnswered);
	EventManagerSubsystem->OnScoreChanged.AddUniqueDynamic(this, &UFiaUserWidget::OnScoreChanged);
	EventManagerSubsystem->OnAnnouncementMessage.AddUniqueDynamic(this, &UFiaUserWidget::OnAnnouncementMessage);
	EventManagerSubsystem->OnQuizResultsBroadcast.AddUniqueDynamic(this, &UFiaUserWidget::OnQuizResultsBroadcast);
	
	EventManagerSubsystem->OnCountDownTimeChanged.AddUniqueDynamic(this, &UFiaUserWidget::OnCountDownTimeChanged);
	EventManagerSubsystem->OnAdventureTimeChanged.AddUniqueDynamic(this, &UFiaUserWidget::OnAdventureTimeChanged);
	EventManagerSubsystem->OnQuizTimeChanged.AddUniqueDynamic(this, &UFiaUserWidget::OnQuizTimeChanged);
}

void UFiaUserWidget::UnBindEventManager()
{
	if (EventManagerSubsystem)
	{
		// Score Updates
		EventManagerSubsystem->OnPlayerOpenedChest.RemoveDynamic(this, &UFiaUserWidget::OnPlayerOpenedChest);
		EventManagerSubsystem->OnQuizLoaded.RemoveDynamic(this, &UFiaUserWidget::OnQuizLoaded);
		EventManagerSubsystem->OnPlayerMissed.RemoveDynamic(this, &UFiaUserWidget::OnPlayerMissed);
		EventManagerSubsystem->OnPlayerAnswered.RemoveDynamic(this, &UFiaUserWidget::OnPlayerAnswered);
		EventManagerSubsystem->OnScoreChanged.RemoveDynamic(this, &UFiaUserWidget::OnScoreChanged);
		
		// Message Updates
		EventManagerSubsystem->OnAnnouncementMessage.RemoveDynamic(this, &UFiaUserWidget::OnAnnouncementMessage);
		EventManagerSubsystem->OnQuizResultsBroadcast.RemoveDynamic(this, &UFiaUserWidget::OnQuizResultsBroadcast);
		
		// Timers
		EventManagerSubsystem->OnCountDownTimeChanged.RemoveDynamic(this, &UFiaUserWidget::OnCountDownTimeChanged);
		EventManagerSubsystem->OnAdventureTimeChanged.RemoveDynamic(this, &UFiaUserWidget::OnAdventureTimeChanged);
		EventManagerSubsystem->OnQuizTimeChanged.RemoveDynamic(this, &UFiaUserWidget::OnQuizTimeChanged);
	}

}
