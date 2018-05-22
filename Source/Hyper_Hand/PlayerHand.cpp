// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerHand.h"


// Sets default values
APlayerHand::APlayerHand()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NewLocation = OrigPunchStart = MoveInput = FVector(0, 0, 0);
	PreviousLocation = GetActorLocation();

	CanMove = true;
	IsMoving = IsDodging = IsFastPunching = IsHeavyPunching = false;
}

// Called when the game starts or when spawned
void APlayerHand::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerHand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckIfMoving();

	if (IsDodging)
		PlayerIsDodging();

	if (IsFastPunching)
		PlayerIsFastPunching();

	if (IsHeavyPunching)
		PlayerIsHeavyPunching();
}

// Called to bind functionality to input
void APlayerHand::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
//====================================================================================
/*Checks if Player is currently moving*/
void APlayerHand::CheckIfMoving()
{
	if (PreviousLocation == GetActorLocation())
		IsMoving = IsDodging = false;
}
//====================================================================================
void APlayerHand::PlayerMoveInput(float MoveUpDownInput, float MoveLeftRightInput)
{
	MoveInput.X = MoveUpDownInput;
	MoveInput.Y = MoveLeftRightInput;
}
//------------------------------------------------------------------------------------
/*Moves the Player in the given directions*/
void APlayerHand::PlayerMove(float PlayerSpeed)
{
	if (!CanMove)
		return;

	FVector OrigLocation = PreviousLocation = GetActorLocation();

	if (!IsMoving)
		IsMoving = true;

	OrigLocation += (FVector(1, 0, 0) * MoveInput.X * PlayerSpeed * FApp::GetDeltaTime());
	OrigLocation += (FVector(0, 1, 0) * MoveInput.Y * PlayerSpeed * FApp::GetDeltaTime());

	SetActorLocation(OrigLocation);
}
//====================================================================================
/*Has Player move a set distance very quickly in direction moving in*/
void APlayerHand::PlayerDodge(float DodgeDistance)
{
	if ( CanMove && !IsDodging && (MoveInput.X != 0 || MoveInput.Y != 0) )
		IsDodging = true;
	else
		return;

	NewLocation = GetActorLocation() + (MoveInput * DodgeDistance);

	CanMove = false;
}
//------------------------------------------------------------------------------------
void APlayerHand::PlayerIsDodging()
{
	SetActorLocation(FMath::Lerp(GetActorLocation(), NewLocation, .35f));

	if (FVector::Dist(GetActorLocation(), NewLocation) <= 10.0f)
	{
		IsDodging = false;
		CanMove = true;
	}
}
//====================================================================================
/*Rotates the Player to the desired direction*/
void APlayerHand::PlayerAim(float LookUpDownInput, float LookLeftRightInput)
{
	if (!CanMove)
		return;

	FRotator Rotation = GetActorRotation();
	
	if (LookUpDownInput != 0 && LookLeftRightInput != 0)
	{
		Rotation.Yaw = FMath::RadiansToDegrees(FMath::Atan2(LookLeftRightInput, -LookUpDownInput));
		SetActorRotation(Rotation);
	}

}
//==================================================================================================
/*Fast Punch forward in direction currently looking*/
void APlayerHand::PlayerFastPunch(float PunchDistance)
{
	if (CanMove && !IsFastPunching)
		IsFastPunching = true;
	else
		return;

	OrigPunchStart = GetActorLocation();

	NewLocation = OrigPunchStart + (GetActorForwardVector() * PunchDistance);

	CanMove = PullBack = false;
}
//-------------------------------------------------------------------------------------------------
void APlayerHand::PlayerIsFastPunching()
{
	if (!PullBack)
	{
		SetActorLocation(FMath::Lerp(GetActorLocation(), NewLocation, .35f));

		if (FVector::Dist(GetActorLocation(), NewLocation) <= 10.0f)
			PullBack = true;
	}
	else
	{
		SetActorLocation(FMath::Lerp(GetActorLocation(), OrigPunchStart, .35f));

		if (FVector::Dist(GetActorLocation(), OrigPunchStart) <= 250.0f)
		{
			IsFastPunching = PullBack = false;
			CanMove = true;
		}
	}
}

//==============================================================================================
void APlayerHand::PlayerHeavyPunch(float PunchDistance, float PunchHeight)
{
	if (CanMove && !IsHeavyPunching)
		IsHeavyPunching = true;
	else
		return;

	OrigPunchStart = GetActorLocation();

	PunchEndHeight = OrigPunchStart + (GetActorUpVector() * PunchHeight);
	NewLocation = OrigPunchStart + (GetActorForwardVector() * PunchDistance);

	CanMove = false;
	CurrentPhase = 0;
}

void APlayerHand::PlayerIsHeavyPunching()
{
	if (CurrentPhase == 0)
	{
		SetActorLocation(FMath::Lerp(GetActorLocation(), PunchEndHeight, .1f));

		if (FVector::Dist(GetActorLocation(), PunchEndHeight) <= 10.0f)
			CurrentPhase++;
	}
	else if (CurrentPhase == 1)
	{
		SetActorLocation(FMath::Lerp(GetActorLocation(), NewLocation, .35f));

		if (FVector::Dist(GetActorLocation(), NewLocation) <= 10.0f)
			CurrentPhase++;
	}
	else if (CurrentPhase == 2)
	{
		SetActorLocation(FMath::Lerp(GetActorLocation(), OrigPunchStart, .2f));

		if (FVector::Dist(GetActorLocation(), OrigPunchStart) <= 10.0f)
		{
			CurrentPhase = 0;
			IsHeavyPunching = false;
			CanMove = true;
		}
	}
}
