// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UnreachableCPPFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class UNREACHABLE_API UUnreachableCPPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:	
	// Returns the position in the screen ([-0.5,0.5]x[-0.5,0.5]) of the point "Pos" given a camera component. 
	UFUNCTION(BlueprintCallable)
	static FVector2D WorldToScreenPosition(FVector Pos, UCameraComponent* CameraComponent, FVector2D& CameraSize);

	// Returns the displacement of the camera if it's facing a point outside a viewing volume (it assumes the position
	// of the camera is an aproximation of a Isometric camera)
	UFUNCTION(BlueprintCallable)
	static FVector GetCameraDisplacement(UCameraComponent* CameraComponent, UBoxComponent* ViewVolume);

	
	// Checks if a point is inside of a cone, given the cone vertex, angle and axis
	UFUNCTION(BlueprintCallable)
	static bool IsPointInsideACone(FVector Point, FVector ConeVertex, FVector ConeAxis, float ConeAngle);

	
};
