// Fill out your copyright notice in the Description page of Project Settings.

#include "Pong.h"
#include "Ball.h"
#include "Paddle.h"
#include "PaddleAIController.h"


void APaddleAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!ensure(TheBall)) { return; }

	APaddle* Paddle = Cast<APaddle>(GetPawn());
	if (!Paddle) { return; }

	FVector PaddleLocation = Paddle->GetActorLocation();
	FVector BallLocation = TheBall->GetActorLocation();

	float XDiff = BallLocation.X - PaddleLocation.X;

	if (FMath::Abs(XDiff) >= JitterThreshold)
	{
		Paddle->SetCurrentSpeed(XDiff);
	}
	else
	{
		Paddle->SetCurrentSpeed(0.0f);
	}

}
