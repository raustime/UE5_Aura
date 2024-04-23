// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "Player/AuraPlayerState.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
    const UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
    check(AttributeInfo);

    for (auto& Pair : AS->TagsToAttributes)
    {
        BroadcastAttributeInfo(Pair.Key, Pair.Value());
    }
    AAuraPlayerState* AuraPlayerState = CastChecked<AAuraPlayerState>(PlayerState);
    AttributePointsChangedDelegate.Broadcast(AuraPlayerState->GetAttributePoints());
}

void UAttributeMenuWidgetController::UpgradeAttribute(const FGameplayTag& AttributeTag)
{
    UAuraAbilitySystemComponent* AuraASC = CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent);
    AuraASC->UpgradeAttribute(AttributeTag);
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
    UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
    check(AttributeInfo);
    for (auto& Pair : AS->TagsToAttributes)
    {
        AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value())
            .AddLambda([this, Pair](const FOnAttributeChangeData& Data) { BroadcastAttributeInfo(Pair.Key, Pair.Value()); });
    }

    AAuraPlayerState* AuraPlayerState = CastChecked<AAuraPlayerState>(PlayerState);
    AuraPlayerState->OnAttributePointsChangedDelegate.AddLambda([this](int32 Points) { AttributePointsChangedDelegate.Broadcast(Points); });
}


void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const
{
    FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
    Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
    AttributeInfoDelegate.Broadcast(Info);
}
