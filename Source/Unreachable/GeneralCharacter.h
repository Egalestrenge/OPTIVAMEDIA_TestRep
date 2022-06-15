// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnreachableLight.h"
#include "GameFramework/Character.h"
#include "GeneralCharacter.generated.h"

UCLASS()
class UNREACHABLE_API AGeneralCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGeneralCharacter();

	////
	//// EVENT DISPATCHERS 
	///
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFormChangedDelegate, bool, bIsInMaterialForm);
    //Event broadcasted when the character changes its material form (either be from material to soul, or viceversa)
    UPROPERTY(BlueprintAssignable, BlueprintCallable)
    FFormChangedDelegate FFormChangedEvent;
    
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMoveToEndedDelegate);
	//Event broadcasted when we can make an action with this character
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FMoveToEndedDelegate FMoveToEndedEvent;

	////
	//// TIMERS
	///
	
	FTimerDelegate MovementTimerDelegate;
	UPROPERTY(BlueprintReadWrite)
	FTimerHandle MovementTimerHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//Is the character in material form (false means it is in spirit form)
	UPROPERTY(BlueprintReadWrite)
	bool bIsInMaterialForm = true;	
	
	//List of lights that the character is interacting with
	UPROPERTY(BlueprintReadWrite)
    TArray<AUnreachableLight*> Lights;

	//Gets a socket light info, given the socket position
	UFUNCTION(Blueprintcallable)
	void GetSocketLightInfo(FVector SocketPos, AUnreachableLight* LightActor, bool& bBoneIsLighted, FVector& LightAxis,
		FVector& LightPos, float& LightAngle, float& LightRadius);

	//Sets a socket light state, given the socket name and the material parameter collection MPC
	UFUNCTION(Blueprintcallable)
	void SetSocketLightState(FString SocketName, UMaterialParameterCollectionInstance* MPCInst, int& NLightedBones);
	
	//Sets the all the sockets light state, given the material parameter collection MPC
    UFUNCTION(Blueprintcallable)
    void SetSocketsLightState(UMaterialParameterCollection* MPC);
	

	//Move the character to a point, given the destination transform
	UFUNCTION(BlueprintNativeEvent)
	void MoveCharacterTo(FTransform DestinationTransform);
	virtual void MoveCharacterTo_Implementation(FTransform DestinationTransform);

	////
	//// CHECK FUNCTIONS
	///
	UFUNCTION(BlueprintCallable)
	bool HasMoveToEnded(FVector DestinationPoint);
	UFUNCTION(BlueprintCallable)
	void CheckIfHasMoveToEnded(FVector DestinationPoint);
};

