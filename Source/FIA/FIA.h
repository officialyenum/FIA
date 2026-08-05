// Chukwuyenum Opone Copyright 2026

#pragma once

#include "CoreMinimal.h"

//LOG
#define FIA_LOG(Text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, TEXT(Text), false)
#define FIA_LOG_K(Key, Text) if (GEngine) GEngine->AddOnScreenDebugMessage(Key, 2.0f, FColor::Black, TEXT(Text), false)
#define FIA_LOG_F(Format, ...) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, FString::Printf(TEXT(Format), ##__VA_ARGS__), false)
#define FIA_LOG_F_K(Key, Format, ...) if (GEngine) GEngine->AddOnScreenDebugMessage(Key, 2.0f, FColor::Black, FString::Printf(TEXT(Format). ##__VA_ARGS__)

//WARN
#define FIA_WARN(Text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Orange, TEXT(Text), false)
#define FIA_WARN_K(Key, Text) if (GEngine) GEngine->AddOnScreenDebugMessage(Key, 2.0f, FColor::Orange, TEXT(Text), false)
#define FIA_WARN_F(Format, ...) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Orange, FString::Printf(TEXT(Format), ##__VA_ARGS__), false)
#define FIA_WARN_F_K(Key, Format, ...) if (GEngine) GEngine->AddOnScreenDebugMessage(Key, 2.0f, FColor::Orange, FString::Printf(TEXT(Format). ##__VA_ARGS__)

//ERRORS
#define FIA_ERROR(Text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(Text), false)
#define FIA_ERROR_K(Key, Text) if (GEngine) GEngine->AddOnScreenDebugMessage(Key, 2.0f, FColor::Red, TEXT(Text), false)
#define FIA_ERROR_F(Format, ...) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT(Format), ##__VA_ARGS__), false)
#define FIA_ERROR_F_K(Key, Format, ...) if (GEngine) GEngine->AddOnScreenDebugMessage(Key, 2.0f, FColor::Red, FString::Printf(TEXT(Format). ##__VA_ARGS__)
