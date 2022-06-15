// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelSequenceActor.h"
#include "UnreachableLevelSequenceActor.generated.h"

/**
 * 
 */
UCLASS()
class UNREACHABLE_API AUnreachableLevelSequenceActor : public ALevelSequenceActor
{
	GENERATED_BODY()
	
public:

    UPROPERTY(BlueprintReadWrite)
    TArray<AActor*> SequenceActors;

    UPROPERTY(BlueprintReadWrite)
    TArray<FTransform> SequenceActorsTransforms;
    
    UFUNCTION(BlueprintCallable)
    void LoadSequenceActors();	
};
