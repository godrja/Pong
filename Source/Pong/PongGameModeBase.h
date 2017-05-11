// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "PongGameModeBase.generated.h"

UENUM(BlueprintType)
enum class EPlayer : uint8
{
	P_RIGHT UMETA(DisplayName = "Right Player"),
	P_LEFT UMETA(DisplayName = "Left Player")
};

/**
 * 
 */
UCLASS()
class PONG_API APongGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	
	
	
};
