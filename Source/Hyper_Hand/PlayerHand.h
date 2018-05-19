// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerHand.generated.h"

UCLASS()
class HYPER_HAND_API APlayerHand : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerHand();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	UPROPERTY()
	FVector PreviousLocation;

	UPROPERTY()
	FVector MoveInput;

	UPROPERTY()
	bool IsDodging;

	UPROPERTY(EditAnywhere)
	bool IsMoving;

	UFUNCTION()
	void CheckIfMoving();

	UFUNCTION(BlueprintCallable)
	void PlayerMoveInput(float MoveUpDownInput, float MoveLeftRightInput);

	UFUNCTION(BlueprintCallable)
	void PlayerMove(float PlayerSpeed);

	UFUNCTION(BlueprintCallable)
	void PlayerDodge(float DodgeDistance, float PlayerSpeed);

	UFUNCTION(BlueprintCallable)
	void PlayerAim(float LookUpDownInput, float LookLeftRightInput);

};
