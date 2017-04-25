// Fill out your copyright notice in the Description page of Project Settings.

#include "Pong.h"
#include "Ball.h"


// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
	
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
	// TODO: Add some random angle to this rotation for more fun
	Velocity = FVector(0.0f, 500.0f, 0.0f);

	// Register OnHit event
	GetStaticMeshComponent()->OnComponentHit.AddDynamic(this, &ABall::OnHit);
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Moving the ball
	AddActorWorldOffset(Velocity * DeltaTime, true);
}


void ABall::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// TODO: Extract tags as constants

	if (OtherActor->ActorHasTag("Paddle"))
	{
		// Invert vertical component of velocity
		FVector InvertedVelocity = FVector(1, -1, 1) * Velocity;

		// Add random rotation to a vector 
		// TODO: Extract as a method
		const FRotator RandomRotator = FRotator(0.0f, (FMath::FRand() - 0.5f) * RandomHitRotationAngle, 0.0f);
		Velocity = RandomRotator.RotateVector(InvertedVelocity);
	}
	else if (OtherActor->ActorHasTag("Border"))
	{
		// Invert vertical component of velocity
		Velocity *= FVector(-1, 1, 1);
	}

}