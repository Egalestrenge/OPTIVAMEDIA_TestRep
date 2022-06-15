// Fill out your copyright notice in the Description page of Project Settings.


#include "UnreachableCPPFunctionLibrary.h"

FVector2D UUnreachableCPPFunctionLibrary::WorldToScreenPosition(FVector Pos, UCameraComponent* CameraComponent, FVector2D& CameraSize){
	float FOV = CameraComponent->FieldOfView; //in degrees
	float AR = CameraComponent->AspectRatio;

	FVector PosC = CameraComponent->GetComponentTransform().InverseTransformPosition(Pos);
	float W = 2.0f*PosC.X*FMath::Tan(FOV/2.0f);
	float H = W / AR;

	CameraSize = FVector2D(W/H);
		
	FVector2D CameraPos = FVector2D(PosC.Y/W,PosC.Z/H);
	return CameraPos;
}

FVector UUnreachableCPPFunctionLibrary::GetCameraDisplacement(UCameraComponent* CameraComponent,
	UBoxComponent* ViewVolume)
{
	FVector TBL = ViewVolume->GetComponentLocation() + FVector(-ViewVolume->Bounds.BoxExtent.X,-ViewVolume->Bounds.BoxExtent.Y,ViewVolume->Bounds.BoxExtent.Z);
	FVector BFR = ViewVolume->GetComponentLocation() + FVector(ViewVolume->Bounds.BoxExtent.X,ViewVolume->Bounds.BoxExtent.Y,-ViewVolume->Bounds.BoxExtent.Z);
	FVector TBR = ViewVolume->GetComponentLocation() + FVector(ViewVolume->Bounds.BoxExtent.X,-ViewVolume->Bounds.BoxExtent.Y,ViewVolume->Bounds.BoxExtent.Z);
	FVector TFL = ViewVolume->GetComponentLocation() + FVector(-ViewVolume->Bounds.BoxExtent.X,ViewVolume->Bounds.BoxExtent.Y,ViewVolume->Bounds.BoxExtent.Z);


	FVector2D CameraPlaneSizeT;
	FVector2D T = WorldToScreenPosition(TBL,CameraComponent,CameraPlaneSizeT);

	FVector2D CameraPlaneSizeB;
	FVector2D B = WorldToScreenPosition(BFR,CameraComponent,CameraPlaneSizeB);

	FVector2D CameraPlaneSizeR;
	FVector2D R = WorldToScreenPosition(TBR,CameraComponent,CameraPlaneSizeR);

	FVector2D CameraPlaneSizeL;
	FVector2D L = WorldToScreenPosition(TFL,CameraComponent,CameraPlaneSizeL);

	//Do not make any displacement if:
	//the top of the volume is over the top of the camera screen AND
	//the bottom of the volume is under the bottom of the camera screen AND
	//the right of the volume is to the right of the camera screen AND
	//the left of the volume is to the left of the camera screen

	float DispX = 0.0f;
	float DispY = 0.0f;
	FVector Disp;

	if(T.Y<0.5f)
	{
		DispY = (T.Y - 0.5f)*CameraPlaneSizeT.Y;
	}
	else if(B.Y>-0.5f)
	{
		DispY = (B.Y + 0.5f)*CameraPlaneSizeB.Y;
	}

	if(R.X<0.5f)
	{
		DispX = (R.X - 0.5f)*CameraPlaneSizeR.X;
	}
	else if(L.X>-0.5f)
	{
		DispX = (L.X + 0.5f)*CameraPlaneSizeL.X;
	}

	Disp = CameraComponent->GetComponentTransform().TransformVector(FVector(0.0f,DispX,DispY));	
	
	return Disp;
}

bool UUnreachableCPPFunctionLibrary::IsPointInsideACone(FVector Point, FVector ConeVertex, FVector ConeAxis,
	float ConeAngle)
{
	/*FVector PointProj;
	float PointAxisDist = FMath::PointDistToLine(Point,ConeAxis,ConeVertex,PointProj);
	float ConeRadius = FVector::Dist(ConeVertex,PointProj)*FMath::Tan(FMath::DegreesToRadians(ConeAngle/2.0f));	
	if(PointAxisDist<=ConeRadius)
	{
		return true;
	}
	else
	{
		return false;
	}*/

	ConeAxis.Normalize();

	if (fabs(FVector::DotProduct((Point - ConeVertex),ConeAxis) / FVector::Distance(Point, ConeVertex)) >= cos(FMath::DegreesToRadians(ConeAngle / 2.0f))) {
		return true;
	}
	else {
		return false;
	}

}
	
	
	



