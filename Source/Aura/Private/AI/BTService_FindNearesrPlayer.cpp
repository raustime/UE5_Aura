// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/BTService_FindNearesrPlayer.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BTFunctionLibrary.h"

void UBTService_FindNearesrPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APawn* OwningPawn = AIOwner->GetPawn();

    const FName TargetTag = OwningPawn->ActorHasTag(FName("Player")) ? FName("Enemy") : FName("Player");

    TArray<AActor*> ActorsWithTag;
    UGameplayStatics::GetAllActorsWithTag(OwningPawn, TargetTag, ActorsWithTag);

    float ClosestDistance = TNumericLimits<float>::Max();
    AActor* ClosestActor = nullptr;
    for (AActor* Actor : ActorsWithTag)
    {
        GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Orange, *Actor->GetName());

        if (IsValid(Actor) && IsValid(OwningPawn))
        {
            const float Distance = OwningPawn->GetDistanceTo(Actor);
            if (Distance < ClosestDistance)
            {
                ClosestDistance = Distance;
                ClosestActor = Actor;
            }
        }
    }
    UBTFunctionLibrary::SetBlackboardValueAsObject(this, TargetToFollowSelector, ClosestActor);
    UBTFunctionLibrary::SetBlackboardValueAsFloat(this, DistanceToTargetSelector, ClosestDistance);
}
