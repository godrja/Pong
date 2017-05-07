// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "PaddleAIController.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API APaddleAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	// Ball tracked by this AI controller
	UPROPERTY(BlueprintReadWrite, Category = "Setup")
	ABall* TheBall = nullptr;

	// How different X coordinate has to be for AI to start moving the paddle
	float JitterThreshold = 10.0f;

public:
	virtual void Tick(float DeltaTime) override;

};
