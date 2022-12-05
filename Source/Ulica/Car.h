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
	int Speed;
	int PreferredSpeed;
	int Acceleration;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SpeedUp(float DeltaTime);
	void SlowDown(float DeltaTime);
	int GetSpeed();

};
