// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class FREEFALLINGGAME_API APlayerCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION() void BeginOverlap(class UPrimitiveComponent* thisguy, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	UFUNCTION() void EndOverlap(class UPrimitiveComponent* thisguy, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION() void MoveX(float AxisValue);
	UFUNCTION() void MoveY(float AxisValue);

	UFUNCTION(BlueprintCallable, Category = "Player Controller")
	void Teleport(FVector NewLocation);
	UFUNCTION(BlueprintCallable, Category = "Player Controller")
	void RedirectMomemtum(FVector Direction);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components") USphereComponent* SphereComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components") UStaticMeshComponent* Model;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components") USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components") UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings") float PlayerSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings") float DefaultCameraDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings") float AccelRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings") float MaxVelocity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings") FVector Gravity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State") FVector MovementInput;

};
