// Fill out your copyright notice in the Description page of Project Settings.

#include "Pong.h"
#include "PongGameModeBase.h"
#include "Ball.h"


// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetStaticMeshComponent()->bGenerateOverlapEvents = true;
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
	const float RelaunchDelay = 0.5f;
	ResetPosition();

	FTimerHandle Handle; // throw away handle
	
	GetWorldTimerManager()
		.SetTimer(Handle, FTimerDelegate::CreateUObject(this, &ABall::Launch, Player), RelaunchDelay, false);
}

void ABall::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// TODO: Extract tags as constants

	if (OtherActor->ActorHasTag("Paddle"))
	{
		// The following logic is a little complicated for what it does. It calculated the degree or lines that go
		// from the center to the corners of the ball. This is not really required because the ball is always square
		// so the angle will always be 45 degrees ~ 0.785398 radians. 

		FVector Origin /* throwaway */, Size;
		GetActorBounds(true, Origin, Size);
		const FVector ForwardVector = GetActorForwardVector();

		const FVector LeftUpVector = FVector(-Size.X / 2, Size.Y / 2, 0).GetSafeNormal2D();
		const float LeftUpRad = FMath::Acos(FVector::DotProduct(LeftUpVector, ForwardVector));

		const FVector LeftDownVector = FVector(Size.X / 2, Size.Y / 2, 0).GetSafeNormal2D();
		const float LeftDownRad = FMath::Acos(FVector::DotProduct(LeftDownVector, ForwardVector));

		// Vector that points from the middle of the paddle to the impact point
		const float ImpactVectorRad = 
			FMath::Acos(FVector::DotProduct((GetActorLocation() - Hit.ImpactPoint).GetSafeNormal2D(), ForwardVector));
		
		// Decide whether the ball will be reflected in vertical axis or horizontal.
		if (ImpactVectorRad <= LeftUpRad && ImpactVectorRad >= LeftDownRad)
		{
			ReflectHorizontal(OtherActor, Hit);
		}
		else
		{
			ReflectVertical(Hit);
		}
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

void ABall::ReflectHorizontal(AActor* Paddle, const FHitResult &Hit)
{
	// Horizontal reflection calculates the angle of reflection based on the section of the paddle that got hit
	const FVector ImpactVector = (Paddle->GetActorLocation() - Hit.ImpactPoint).GetSafeNormal2D();
	const FVector ImpactPointBasedVelocity = ImpactVector * FVector(1.0f, -1.0f, 1.0f) * Velocity.Size();
	Velocity = RotateRandomly(ImpactPointBasedVelocity);
	// Speed-up in the current direction
	Velocity += Velocity.GetSafeNormal2D() * DefaultSpeedIncrement;
}

void ABall::ReflectVertical(const FHitResult &Hit)
{
	// This section makes sure the ball only inverts it's velocity if it has to
	// Velocity should not be inverted when the ball and the paddle that hit it move in the same direction
	// Otherwise it simply gets stuck.

	bool bNeedToInvertDirection;
	if (Hit.ImpactPoint.X > GetActorLocation().X)
	{ // hit upper side
		bNeedToInvertDirection = Velocity.X > 0;
	}
	else
	{ // hit lower side
		bNeedToInvertDirection = Velocity.X < 0;
	}

	if (bNeedToInvertDirection)
	{
		// Invert velocity in Y axis
		Velocity *= FVector(-1.0f, 1.0f, 1.0f);
	}
}

FVector ABall::RotateRandomly(FVector vector) const
{
	return FRotator(0.0f, (FMath::FRand() - 0.5f) * RandomHitRotationAngle, 0.0f).RotateVector(vector);
}
