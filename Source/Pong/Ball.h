// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/StaticMeshActor.h"
#include "Ball.generated.h"

UCLASS()
class PONG_API ABall : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABall();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Current velocity of the ball
	FVector Velocity = FVector::ZeroVector;
	
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float InitialSpeed = 500.0f;

	// Max angle of random rotation to be applied when hitting a Paddle
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float RandomHitRotationAngle = 10.0f;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// Add random rotation to vector
	FVector RotateRandomly(FVector vector) const;
};
