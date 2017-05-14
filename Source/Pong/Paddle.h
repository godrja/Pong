// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Paddle.generated.h"

UCLASS()
class PONG_API APaddle : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APaddle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float CurrentSpeed = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	 * Sets the new speed, clamps it between -1.0 and 1.0 
	 */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void SetCurrentSpeed(float NewSpeed);

	// Resets the paddle's position to the initial one and sets the current speed to 0.0
	UFUNCTION(BlueprintCallable, Category = "Position")
	void ResetPosition();

private:
	FVector InitialLocation = FVector::ZeroVector;
};
