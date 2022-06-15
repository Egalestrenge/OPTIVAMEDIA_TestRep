// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralCharacter.h"

#include "UnreachableLight.h"
#include "UnreachableCPPFunctionLibrary.h"
#include "Materials/MaterialParameterCollectionInstance.h"


// Sets default values
AGeneralCharacter::AGeneralCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGeneralCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGeneralCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AGeneralCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AGeneralCharacter::GetSocketLightInfo(FVector SocketPos, AUnreachableLight* LightActor, bool& bBoneIsLighted, FVector& LightAxis,
	FVector& LightPos, float& LightAngle, float& LightRadius)
{
	LightAxis = LightActor->GetActorForwardVector();
	LightPos = LightActor->GetActorLocation();
	LightAngle = LightActor->LightAngle;
	LightRadius = LightActor->LightRadius;
	if(LightActor->bIsActive && UUnreachableCPPFunctionLibrary::IsPointInsideACone(SocketPos,LightPos,LightAxis,LightAngle))
	{
		FHitResult HitResult;
		ECollisionChannel CollisionChannel = ECollisionChannel::ECC_Visibility;
		FCollisionQueryParams CollisionQueryParams;
		CollisionQueryParams.AddIgnoredActor(this);		
		for (int i = 0; i < Lights.Num(); i++) {
			CollisionQueryParams.AddIgnoredActor(Lights[i]);
		}
		if(LightActor->GetParentActor())
		{
			CollisionQueryParams.AddIgnoredActor(LightActor->GetParentActor());
		}

		if(!LightActor->ActorsToIgnore.IsEmpty())
		{
			for (AActor* Actor : LightActor->ActorsToIgnore)
			{
				CollisionQueryParams.AddIgnoredActor(Actor);
			}
		}
		
		bBoneIsLighted = !ActorLineTraceSingle(HitResult,SocketPos,LightPos,CollisionChannel,CollisionQueryParams);
		/*if(!bBoneIsLighted)
		{
			//DrawDebugLine(GetWorld(),SocketPos,HitResult.Location,FColor::Red);
			GEngine->AddOnScreenDebugMessage(-1,0.5f,FColor::Red,"Not lighted because no hit");
		}*/
		
		
	}
	else
	{
		bBoneIsLighted = false;
		//GEngine->AddOnScreenDebugMessage(-1,0.5f,FColor::Red,"Not lighted because is not inside cone");
		//DrawDebugSphere(GetWorld(),SocketPos,10.0f,18,FColor::Red);
	}
	
}

void AGeneralCharacter::SetSocketLightState(FString SocketName, UMaterialParameterCollectionInstance* MPCInst, int& NLightedBones)
{	
	FVector SocketPos = GetMesh()->GetSocketLocation(FName(SocketName));	
	
	bool bIsLighted = false;
	FVector LightAxis;
	FVector LightPos;
	float LightAngle = 45.0f;
	float LightRadius = 100.0f;	
	int LightIndex = 0;
	if(!Lights.IsEmpty()){
		
		bool FirstLightFound = false;
		
		
		for (int i=0;i<Lights.Num();i++)
		{								
			AUnreachableLight* Light = Lights[i];
			
			if(Light)
			{
				bool bIsLightedPrev = false;			
				FVector LightAxisPrev;
				FVector LightPosPrev;
				float LightAnglePrev = 45.0f;
				float LightRadiusPrev = 100.0f;
				
				GetSocketLightInfo(SocketPos,Light,bIsLightedPrev,LightAxisPrev,LightPosPrev,LightAnglePrev,LightRadiusPrev);

				if(bIsLightedPrev)
				{
					if(!FirstLightFound)
					{
						bIsLighted = true;
						LightAxis = Light->GetActorForwardVector();
						LightPos = Light->GetActorLocation();
						LightAngle = Light->LightAngle;
						LightRadius = Light->LightRadius;
						LightIndex = i;
						FirstLightFound = true;
					}
					
					else 
					{
						float LambdaPrev = (SocketPos.Z - LightPosPrev.Z) / LightAxisPrev.Z;
						FVector LightProjPrev = LightPosPrev + LambdaPrev * LightAxisPrev;
						float DistPrev = FVector::Distance(SocketPos, LightProjPrev);
						//float RPrev = FVector::Dist(LightPosPrev,LightProjPrev)

						float Lambda = (SocketPos.Z - LightPos.Z) / LightAxis.Z;
						FVector LightProj = LightPos + Lambda * LightAxis;
						float Dist = FVector::Distance(SocketPos, LightProj);

						//DrawDebugLine(GetWorld(), SocketPos, LightProj, FColor::Red);
						//DrawDebugLine(GetWorld(), SocketPos, LightProjPrev, FColor::Blue);

						/*FVector LightAxisProjPrev;
						float LightAxisDistPrev = FMath::PointDistToLine(SocketPos, LightAxisPrev, LightPos, LightAxisProjPrev);
						float RPrev = FVector::Dist(LightAxisProjPrev,LightPos)* FMath::Tan(FMath::DegreesToRadians(LightAnglePrev / 2.0f));

						FVector LightAxisProj;
						float LightAxisDist = FMath::PointDistToLine(SocketPos, LightAxis, LightPos, LightAxisProj);
						float R = FVector::Dist(LightAxisProj, LightPos) * FMath::Tan(FMath::DegreesToRadians(LightAngle / 2.0f));*/

						if (Dist > DistPrev) {
							//bIsLighted = true;
							LightAxis = Light->GetActorForwardVector();
							LightPos = Light->GetActorLocation();
							LightAngle = Light->LightAngle;
							LightRadius = Light->LightRadius;
							//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, "entro");
							LightIndex = i;
						}
						
						
					}					
				}
			}
			/*else
			{
				GEngine->AddOnScreenDebugMessage(-1,0.5f,FColor::Red,"No light pointer");
			}*/
		}
	}
	/*else
	{
		GEngine->AddOnScreenDebugMessage(-1,0.5f,FColor::Red,"No lights");
	}*/

	if(bIsLighted)
	{
		NLightedBones++;
		MPCInst->SetVectorParameterValue(FName(SocketName),SocketPos);		
		MPCInst->SetScalarParameterValue(FName(SocketName+"_LightAngle"),Lights[LightIndex]->LightAngle);
		MPCInst->SetScalarParameterValue(FName(SocketName+"_LightRadius"), Lights[LightIndex]->LightRadius);
		MPCInst->SetVectorParameterValue(FName(SocketName+"_LightAxis"), Lights[LightIndex]->GetActorForwardVector());
		MPCInst->SetVectorParameterValue(FName(SocketName+"_LightPos"), Lights[LightIndex]->GetActorLocation());
		float CurrentLight;
		MPCInst->GetScalarParameterValue(FName(SocketName+"_Light"),CurrentLight);
		float NewLight = FMath::FInterpTo(CurrentLight,1.0f,GetWorld()->GetDeltaSeconds(),10.0f);
		MPCInst->SetScalarParameterValue(FName(SocketName+"_Light"),NewLight);
		//GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, FString::Printf(TEXT("Light Index: %d"), LightIndex));
		/*GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, FString::Printf(TEXT("Light Pos: %f %f %f"), LightPos.X, LightPos.Y, LightPos.Z));
		GEngine->AddOnScreenDebugMessage(-1,0.5f,FColor::Red, FString::Printf(TEXT("Light Forward: %f %f %f"), LightAxis.X, LightAxis.Y, LightAxis.Z));
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, FString::Printf(TEXT("Socket Pos: %f %f %f"), SocketPos.X, SocketPos.Y, SocketPos.Z));*/
	}
	else
	{
		MPCInst->SetVectorParameterValue(FName(SocketName),SocketPos);
		float CurrentLight;
		MPCInst->GetScalarParameterValue(FName(SocketName+"_Light"),CurrentLight);
		float NewLight = FMath::FInterpTo(CurrentLight,-1.0f,GetWorld()->GetDeltaSeconds(),10.0f);
		MPCInst->SetScalarParameterValue(FName(SocketName+"_Light"),NewLight);
		//GEngine->AddOnScreenDebugMessage(-1,0.5f,FColor::Red, FString::Printf(TEXT("Light: %f"),NewLight));
	}

	

	
}

void AGeneralCharacter::SetSocketsLightState(UMaterialParameterCollection* MPC)
{
	int NLightedSockets = 0;
	UMaterialParameterCollectionInstance* MPCInst = GetWorld()->GetParameterCollectionInstance(MPC);
			
    SetSocketLightState("CenterSocket",MPCInst,NLightedSockets);
    SetSocketLightState("FrontSocket",MPCInst,NLightedSockets);
    SetSocketLightState("BackSocket",MPCInst,NLightedSockets);
    SetSocketLightState("LeftSocket",MPCInst,NLightedSockets);
    SetSocketLightState("RightSocket",MPCInst,NLightedSockets);
	
	
	FVector HeartPos = GetMesh()->GetSocketLocation(FName(TEXT("Heart")));
	bool bIsHeartLighted = false;
	float HeartAlpha = 1.0f;	

	if(!Lights.IsEmpty())
	{
		for(int i=0;(i<Lights.Num() && !bIsHeartLighted);i++)
		{
			AUnreachableLight* Light = Lights[i];
			FVector LightAxis;
			FVector LightPos;
			float LightAngle;
			float LightRadius;
			GetSocketLightInfo(HeartPos,Light,bIsHeartLighted,LightAxis,LightPos,LightAngle,LightRadius);
		}

		if(bIsHeartLighted)
		{
			HeartAlpha = 0.0f;
		}
		else
		{
			HeartAlpha = ((float)(5-NLightedSockets))/5.0f;
		}		
	}	
	
	MPCInst->SetVectorParameterValue(FName(TEXT("HeartPos")),HeartPos);
	MPCInst->SetScalarParameterValue(FName(TEXT("HeartAlpha")),HeartAlpha);
	if(bIsInMaterialForm != bIsHeartLighted)
	{
		bIsInMaterialForm = bIsHeartLighted;
		FFormChangedEvent.Broadcast(bIsInMaterialForm);
	}
	
	
	
}

void AGeneralCharacter::MoveCharacterTo_Implementation(FTransform DestinationTransform)
{
	SetActorTransform(DestinationTransform);
	FMoveToEndedEvent.Broadcast();
	//UE_LOG(LogTemp,Warning,TEXT("Function called from C++!"));
}

bool AGeneralCharacter::HasMoveToEnded(FVector DestinationPoint)
{
	
	if(FVector::DistXY(GetActorLocation(),DestinationPoint)<=50.0f)
	{		
		return true;
	}
	else
	{
		return false;
	}
}

void AGeneralCharacter::CheckIfHasMoveToEnded(FVector DestinationPoint)
{
	if(HasMoveToEnded(DestinationPoint))
	{
		if(MovementTimerHandle.IsValid())
		{
			FMoveToEndedEvent.Broadcast();	
			MovementTimerHandle.Invalidate();					
		}
	}	
}



