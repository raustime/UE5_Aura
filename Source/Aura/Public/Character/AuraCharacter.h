// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Character/AuraCharacterBase.h"
#include "CoreMinimal.h"
#include "Interaction/PlayerInterface.h"
#include "AuraCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase, public IPlayerInterface
{
    GENERATED_BODY()

public:
    AAuraCharacter();
    virtual void PossessedBy(AController* NewController) override;
    virtual void OnRep_PlayerState() override;

    /** Players Interface */
    virtual void AddToXP_Implementation(int32 InXP) override;
    virtual void LevelUp_Implementation() override;
    /** end Player Interface */

    /** Combat Interface */
    virtual int32 GetPlayerLevel_Implementation() override;
    /** end Combat Interface */

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components") USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

private:
    virtual void InitAbilityActorInfo() override;
};
