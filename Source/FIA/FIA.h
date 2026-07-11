// Chukwuyenum Opone Copyright 2026

#pragma once

#include "CoreMinimal.h"

//Logs
#define FIA_LOG(Text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, TEXT(Text), false)
#define FIA_LOG_K(Key, Text) if (GEngine) GEngine->AddOnScreenDebugMessage(Key, 2.0f, FColor::Black, TEXT(Text), false)
#define FIA_LOG_F(Format, ...) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, FString::Printf(TEXT(Format), ##__VA_ARGS__), false)
#define FIA_LOG_F_K(Key, Format, ...) if (GEngine) GEngine->AddOnScreenDebugMessage(Key, 2.0f, FColor::Black, FString::Printf(TEXT(Format). ##__VA_ARGS__)
