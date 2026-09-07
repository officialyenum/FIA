// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FiaUserWidget.h"

#include "FIA/FIA.h"
#include "System/EventManagerSubsystem.h"
#include "System/QuizManagerSubsystem.h"


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
	QuizManagerSubsystem = World->GetSubsystem<UQuizManagerSubsystem>();
	if (!EventManagerSubsystem)
	{
		FIA_LOG("Event Manager Subsystem Not Found in Fia User Widget Bind Event Manager");
		return;
	}
	if (!QuizManagerSubsystem)
	{
		FIA_LOG("Quiz Manager Subsystem Not Found in Fia User Widget Bind Event Manager");
		return;
	}
	QuizManagerSubsystem->OnQuizStarted.AddUniqueDynamic(this, &UFiaUserWidget::OnQuizStarted);
	QuizManagerSubsystem->OnQuizFinished.AddUniqueDynamic(this, &UFiaUserWidget::OnQuizFinished);
	QuizManagerSubsystem->OnPlayerAnswered.AddUniqueDynamic(this, &UFiaUserWidget::OnQuizPlayerAnswered);
	QuizManagerSubsystem->OnPlayerScored.AddUniqueDynamic(this, &UFiaUserWidget::OnQuizPlayerScored);
	EventManagerSubsystem->OnAnnouncementMessage.AddUniqueDynamic(this, &UFiaUserWidget::OnAnnouncementMessage);
}

void UFiaUserWidget::UnBindEventManager()
{
	if (EventManagerSubsystem)
	{
		EventManagerSubsystem->OnAnnouncementMessage.RemoveDynamic(this, &UFiaUserWidget::OnAnnouncementMessage);
	}
	if (QuizManagerSubsystem)
	{
		QuizManagerSubsystem->OnQuizStarted.RemoveDynamic(this, &UFiaUserWidget::OnQuizStarted);
		QuizManagerSubsystem->OnQuizFinished.RemoveDynamic(this, &UFiaUserWidget::OnQuizFinished);
		QuizManagerSubsystem->OnPlayerAnswered.RemoveDynamic(this, &UFiaUserWidget::OnQuizPlayerAnswered);
		QuizManagerSubsystem->OnPlayerScored.RemoveDynamic(this, &UFiaUserWidget::OnQuizPlayerScored);
	}

}
