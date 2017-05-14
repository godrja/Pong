// Fill out your copyright notice in the Description page of Project Settings.

#include "Pong.h"
#include "PongGameModeBase.h"
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
	GetStaticMeshComponent()->OnComponentHit.AddDynamic(this, &ABall::OnHit);
	GetStaticMeshComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABall::OnBeginOverlap);

	InitialLocation = GetActorLocation();
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Move the ball
	AddActorWorldOffset(Velocity * DeltaTime, true);
}

void ABall::ResetPosition()
{
	SetActorLocation(InitialLocation);
	Velocity = FVector::ZeroVector;
}

void ABall::Launch(EPlayer Player)
{
	float ThrowSpeed; // by default throw right
	if (Player == EPlayer::P_RIGHT)
	{
		ThrowSpeed = InitialSpeed;
	}
	else
	{
		ThrowSpeed = -InitialSpeed;
	}

	Velocity = RotateRandomly(FVector(0.0f, InitialSpeed, 0.0f));
}

void ABall::Relaunch(EPlayer Player)
{
	ResetPosition();

	FTimerHandle Handle; // throw away handle
	GetWorldTimerManager().SetTimer(Handle, FTimerDelegate::CreateUObject(this, &ABall::Launch, Player), 0.5f, false);
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
		Velocity = RotateRandomly(ImpactPointBasedVelocity);
	}
	else if (OtherActor->ActorHasTag("Border"))
	{
		// Reflect the ball in vertical direction
		Velocity *= FVector(-1.0f, 1.0f, 1.0f);
	}
}

void ABall::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Probably this should be a responsibility of another object but now game area borders are simple trigger volumes
	// so it is the most convenient place to place the event.
	if (OtherActor->ActorHasTag("Out Right"))
	{
		OnBallOut.Broadcast(EPlayer::P_RIGHT);
	}
	else if (OtherActor->ActorHasTag("Out Left"))
	{
		OnBallOut.Broadcast(EPlayer::P_LEFT);
	}
}

FVector ABall::RotateRandomly(FVector vector) const
{
	return FRotator(0.0f, (FMath::FRand() - 0.5f) * RandomHitRotationAngle, 0.0f).RotateVector(vector);
}
