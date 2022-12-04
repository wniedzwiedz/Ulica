// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Samochod.generated.h"

UCLASS()
class ULICA_API ASamochod : public AActor
{
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* VisualMesh;

	UPROPERTY(VisibleAnywhere, Category = "MoveActor")
		class USceneComponent* RootScene;

	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASamochod();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	int speed;
	int PreferredSpeed;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SpeedUp();
	void SlowDown();
	int GetSpeed();
	
};
