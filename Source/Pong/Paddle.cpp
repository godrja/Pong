// Fill out your copyright notice in the Description page of Project Settings.

#include "Pong.h"
#include "Paddle.h"


// Sets default values
APaddle::APaddle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APaddle::BeginPlay()
{
	Super::BeginPlay();
	
	InitialLocation = GetActorLocation();
}

// Called every frame
void APaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APaddle::SetCurrentSpeed(float NewSpeed)
{
	CurrentSpeed = FMath::Clamp(NewSpeed, -1.0f, 1.0f);
}

void APaddle::ResetPosition()
{
	SetActorLocation(InitialLocation);
	CurrentSpeed = 0.0f;
}
