// Fill out your copyright notice in the Description page of Project Settings.

#include "Actor/AuraEffectActor.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
    PrimaryActorTick.bCanEverTick = false;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
    SetRootComponent(Mesh);

    Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
    Sphere->SetupAttachment(GetRootComponent());
}

void AAuraEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
    {
        const UAuraAttributeSet* AuraAttributeSet =
            Cast<UAuraAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));
        UAuraAttributeSet* MuttableAuraAttributeSet = const_cast<UAuraAttributeSet*>(AuraAttributeSet);
        MuttableAuraAttributeSet->SetHealth(AuraAttributeSet->GetHealth() + 25.f);
        MuttableAuraAttributeSet->SetMana(AuraAttributeSet->GetMana() - 25.f);
        Destroy();
    }
}

void AAuraEffectActor::EndOverlap(
    UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AAuraEffectActor::BeginPlay()
{
    Super::BeginPlay();
    Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnOverlap);
    Sphere->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::EndOverlap);
}
