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
	
	//Movement Variables
	FVector PreviousLocation;
	FVector MoveInput;

	bool CanMove;
	bool IsMoving;

	//Player Dodge Variables
	FVector NewLocation;
	bool IsDodging;

	//Player Punching Variables
	FVector OrigPunchStart;
	FVector PunchEndHeight;
	bool IsFastPunching;
	bool IsHeavyPunching;
	bool PullBack;
	int CurrentPhase;

	//Player Movement
	UFUNCTION(BlueprintCallable)
	void PlayerMoveInput(float MoveUpDownInput, float MoveLeftRightInput);
	UFUNCTION(BlueprintCallable)
	void PlayerMove(float PlayerSpeed);
	void CheckIfMoving();

	//Player Dodging
	UFUNCTION(BlueprintCallable)
	void PlayerDodge(float DodgeDistance);
	void PlayerIsDodging();

	//Player Aim
	UFUNCTION(BlueprintCallable)
	void PlayerAim(float LookUpDownInput, float LookLeftRightInput);

	//Player Fast Punch
	UFUNCTION(BlueprintCallable)
	void PlayerFastPunch(float PunchDistance);
	void PlayerIsFastPunching();

	//Player Heavy Punch
	UFUNCTION(BlueprintCallable)
	void PlayerHeavyPunch(float PunchDistance, float PunchHeight);
	void PlayerIsHeavyPunching();

};
