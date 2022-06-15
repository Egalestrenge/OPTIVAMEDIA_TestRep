// Fill out your copyright notice in the Description page of Project Settings.


#include "UnreachableLevelSequenceActor.h"

#include "MovieScene.h"
#include "Channels/MovieSceneChannelProxy.h"
#include "Kismet/GameplayStatics.h"
#include "Tracks/MovieScene3DTransformTrack.h"


void AUnreachableLevelSequenceActor::LoadSequenceActors()
{
	/*SequenceActors.Empty();
	SequenceActorsTransforms.Empty();

	ULevelSequence* Sequence = GetSequence();
	UMovieScene* movieScene = Sequence->GetMovieScene();

	//Set all spawnable actors and their corresponding transforms
	int SpawnablesCount = movieScene->GetSpawnableCount();	

	for(int i=0;i<SpawnablesCount;i++)
	{
		FMovieSceneSpawnable Spawnable = movieScene->GetSpawnable(i);
		FMovieSceneObjectBindingID SpawnableBindingID = FMovieSceneObjectBindingID(Spawnable.GetGuid());
		AActor* ActorTemplate = Cast<AActor>(Spawnable.GetObjectTemplate());
		AActor* Actor = UGameplayStatics::GetActorOfClass(GetWorld(),ActorTemplate->GetClass());

		//If we have found the actor in the world
		if(Actor)
		{
			//Bind the actor
			AddBinding(SpawnableBindingID,Actor);
			SequenceActors.Add(Actor);

			//Save the cutscene starting transform
			static const FName TransformTrackName(TEXT("Transform"));
 
			// Every object should have only one transform track
			const UMovieScene3DTransformTrack* TransformTrack = movieScene->FindTrack<UMovieScene3DTransformTrack>(SpawnableBindingID.GetGuid(), TransformTrackName);
			if(TransformTrack)
			{
				const TArray<UMovieSceneSection*>& TrackSections = TransformTrack->GetAllSections();
				if(TrackSections.Num() > 0)
				{
					// Take the 1st section since we are getting initial transform
					const UMovieSceneSection* Section0 = TrackSections[0];
					const FMovieSceneChannelProxy& ChannelProxy = Section0->GetChannelProxy();
					auto ChannelArray = ChannelProxy.GetChannels<FMovieSceneFloatChannel>();

					// Assuming order: Translation X 3 -> Rotation X 3 -> Scale X 3
					const int32 TranslationStartIndex = 0;
					const int32 RotationStartIndex = 3;
					const int32 ScaleStartIndex = 6;

					FVector InitialTranslation = FVector::ZeroVector;
					FVector InitialRotationVec = FVector::ZeroVector;
					FVector InitialScale = FVector::OneVector;

					int32 NumOfTransformChannels = ChannelArray.Num() - 1; // Exclude weight channel

					for (int32 ChannelIndex = 0; ChannelIndex < NumOfTransformChannels; ChannelIndex++)
					{
						const FMovieSceneFloatChannel* Channel = ChannelArray[ChannelIndex];

						float ChannelValue = 0.0f;
						bool Result = Channel->Evaluate(FFrameTime(0), ChannelValue);
						if(Result)
						{
							if (ChannelIndex < TranslationStartIndex + 3)
							{ // Translation channels
								InitialTranslation[ChannelIndex - TranslationStartIndex] = ChannelValue;
							}
							else if (ChannelIndex < RotationStartIndex + 3)
							{ // Rotation channels
								InitialRotationVec[ChannelIndex - RotationStartIndex] = ChannelValue;
							}
							else if (ChannelIndex < ScaleStartIndex + 3)
							{ // Scale channels
								InitialScale[ChannelIndex - ScaleStartIndex] = ChannelValue;
							}
						}
						
					}

					FRotator InitialRotation(InitialRotationVec[1], InitialRotationVec[2], InitialRotationVec[0]);
					SequenceActorsTransforms.Add(FTransform(InitialRotation,InitialTranslation,InitialScale));
				}
				else
				{
					SequenceActorsTransforms.Add(Actor->GetTransform());
				}

				
			}
			//If there is no Transform track, just copy the actor transform in the world
			else
			{
				SequenceActorsTransforms.Add(Actor->GetTransform());
			}
			
		}
		
	}

	//Set all spawnable actors and their corresponding transforms
	int PossesableCount = movieScene->GetPossessableCount();

	for(int i=0;i<PossesableCount;i++)
	{
		FMovieScenePossessable Possessable = movieScene->GetPossessable(i);		
		UObject* PossesableObject = Possessable.GetPossessedObjectClass()->GetDefaultObject();	
			
		FMovieSceneObjectBindingID PossessableBindingID = FMovieSceneObjectBindingID(Possessable.GetGuid());		
		AActor* Actor = Cast<AActor>(PossesableObject);

		//If we have found the actor in the world
		if(Actor)
		{			
			SequenceActors.Add(Actor);

			//Save the cutscene starting transform
			static const FName TransformTrackName(TEXT("Transform"));
 
			// Every object should have only one transform track
			const UMovieScene3DTransformTrack* TransformTrack = movieScene->FindTrack<UMovieScene3DTransformTrack>(PossessableBindingID.GetGuid(), TransformTrackName);
			if(TransformTrack)
			{
				const TArray<UMovieSceneSection*>& TrackSections = TransformTrack->GetAllSections();
				if(TrackSections.Num() > 0)
				{
					// Take the 1st section since we are getting initial transform
					const UMovieSceneSection* Section0 = TrackSections[0];
					const FMovieSceneChannelProxy& ChannelProxy = Section0->GetChannelProxy();
					auto ChannelArray = ChannelProxy.GetChannels<FMovieSceneFloatChannel>();

					// Assuming order: Translation X 3 -> Rotation X 3 -> Scale X 3
					const int32 TranslationStartIndex = 0;
					const int32 RotationStartIndex = 3;
					const int32 ScaleStartIndex = 6;

					FVector InitialTranslation = FVector::ZeroVector;
					FVector InitialRotationVec = FVector::ZeroVector;
					FVector InitialScale = FVector::OneVector;

					int32 NumOfTransformChannels = ChannelArray.Num() - 1; // Exclude weight channel

					for (int32 ChannelIndex = 0; ChannelIndex < NumOfTransformChannels; ChannelIndex++)
					{
						const FMovieSceneFloatChannel* Channel = ChannelArray[ChannelIndex];

						float ChannelValue = 0.0f;
						bool Result = Channel->Evaluate(FFrameTime(0), ChannelValue);
						if(Result)
						{
							if (ChannelIndex < TranslationStartIndex + 3)
							{ // Translation channels
								InitialTranslation[ChannelIndex - TranslationStartIndex] = ChannelValue;
							}
							else if (ChannelIndex < RotationStartIndex + 3)
							{ // Rotation channels
								InitialRotationVec[ChannelIndex - RotationStartIndex] = ChannelValue;
							}
							else if (ChannelIndex < ScaleStartIndex + 3)
							{ // Scale channels
								InitialScale[ChannelIndex - ScaleStartIndex] = ChannelValue;
							}
						}
						
					}

					FRotator InitialRotation(InitialRotationVec[1], InitialRotationVec[2], InitialRotationVec[0]);
					SequenceActorsTransforms.Add(FTransform(InitialRotation,InitialTranslation,InitialScale));
				}
				else
				{
					SequenceActorsTransforms.Add(Actor->GetTransform());
				}

				
			}
			//If there is no Transform track, just copy the actor transform in the world
			else
			{
				SequenceActorsTransforms.Add(Actor->GetTransform());
			}
			
		}
		
	}*/
}
