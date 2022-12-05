// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Car.generated.h"

UCLASS()
class ULICA_API ACar : public AActor
{
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* VisualMesh;

	UPROPERTY(VisibleAnywhere)
		class USceneComponent* RootScene;

	UPROPERTY(VisibleInstanceOnly)
		UMaterialInterface* CarMaterial = nullptr;

	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//car speed in cm/s
	int Speed;
	//if possible, car will accelerate until it reaches this speed, and will not accelerate above it (cm/s)
	int PreferredSpeed;
	//car acceleration in cm/s^2
	int Acceleration;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//increase according to set acceleration
	void SpeedUp(float DeltaTime);
	//decrease according to set acceleration
	void SlowDown(float DeltaTime);
	//return current speed
	int GetSpeed();

};
