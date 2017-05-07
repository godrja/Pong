// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/StaticMeshActor.h"
#include "Ball.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBallOut);

UCLASS()
class PONG_API ABall : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABall();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Resets the ball's position to it's initial state. Sets Velocity to zero.
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void ResetPosition();

	// Gives the ball some initial velocity
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Launch();

	UPROPERTY(BlueprintAssignable)
	FBallOut OnBallOut;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float InitialSpeed = 500.0f;

	// Max angle of random rotation to be applied when hitting a Paddle
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float RandomHitRotationAngle = 10.0f;

	// Current velocity of the ball
	FVector Velocity = FVector::ZeroVector;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Add random rotation to vector
	FVector RotateRandomly(FVector vector) const;

	FVector InitialLocation;
};
