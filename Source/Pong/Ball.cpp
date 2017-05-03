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
	Velocity = FVector(0.0f, InitialSpeed, 0.0f);

	// Register OnHit event
	GetStaticMeshComponent()->OnComponentHit.AddDynamic(this, &ABall::OnHit);
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Move the ball
	AddActorWorldOffset(Velocity * DeltaTime, true);
}

void ABall::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// TODO: Extract tags as constants

	if (OtherActor->ActorHasTag("Paddle"))
	{
		const FVector ImpactPointBasedVelocity = 
			((OtherActor->GetActorLocation() + Hit.ImpactPoint) // Vector that points from the middle of the paddle to the impact point
			* FVector(1.0f, -1.0f, 1.0f)).GetSafeNormal2D() // Get the direction of that vector but moving from the paddle
			* Velocity.Size(); // Give it the current velocity

		// Add random rotation to vector
		// TODO: Extract as a method
		const FRotator RandomRotator = FRotator(0.0f, (FMath::FRand() - 0.5f) * RandomHitRotationAngle, 0.0f);
		Velocity = RandomRotator.RotateVector(ImpactPointBasedVelocity);
	}
	else if (OtherActor->ActorHasTag("Border"))
	{
		// Reflect the ball in vertical direction
		Velocity *= FVector(-1.0f, 1.0f, 1.0f);
	}
}
