// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnreachableLight.generated.h"

UCLASS()
class UNREACHABLE_API AUnreachableLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnreachableLight();

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<AActor*> ActorsToIgnore;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float LightAngle = 30.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float LightDistance = 500.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float LightRadius = 250.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float LightRadiusDefault = 250.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsActive = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bUseAngle = true;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
