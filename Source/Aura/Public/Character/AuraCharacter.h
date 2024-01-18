// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Character/AuraCharacterBase.h"
#include "CoreMinimal.h"
#include "AuraCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
    GENERATED_BODY()

public:
    AAuraCharacter();
    virtual void PossessedBy(AController* NewController) override;
    virtual void OnRep_PlayerState() override;

    /** Combat Interface */
    virtual int32 GetPlayerLevel() override;
    /** end Combat Interface */

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components") USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

private:
    virtual void InitAbilityActorInfo() override;
};
