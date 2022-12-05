// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Car.h"
#include "Manager.generated.h"


UCLASS()
class ULICA_API AManager : public AActor
{
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* VisualMesh;

	UPROPERTY(VisibleAnywhere)
		class USceneComponent* RootScene;

	UPROPERTY(VisibleInstanceOnly)
		UMaterialInterface* StreetMaterial = nullptr;


	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SpawnCar();


protected:
	int StreetLength;
	int NextSpawn;
	TArray<ACar*> Cars;
};
