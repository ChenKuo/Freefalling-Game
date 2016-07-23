// Fill out your copyright notice in the Description page of Project Settings.

#include "FreefallingGame.h"
#include "PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerSize = 45.0f;
	DefaultCameraDistance = 1000.0f;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::BeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::EndOverlap);
	SphereComponent->SetSimulatePhysics(true);
	SphereComponent->SetEnableGravity(false);
	SphereComponent->SetLinearDamping(0.0f);
	SphereComponent->BodyInstance.bLockRotation = true;
	SphereComponent->BodyInstance.bLockXRotation = true;
	SphereComponent->BodyInstance.bLockYRotation = true;
	SphereComponent->BodyInstance.bLockZRotation = true;
	SphereComponent->BodyInstance.PositionSolverIterationCount = 16;
	SphereComponent->BodyInstance.VelocitySolverIterationCount = 16;
	SphereComponent->bShouldUpdatePhysicsVolume = true;

	Model = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Player Model"));
	const ConstructorHelpers::FObjectFinder<UStaticMesh> PlayerMeshFinder(TEXT("/Game/Models/Player/PlayerModel"));
	Model->SetStaticMesh(PlayerMeshFinder.Object);
	Model->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Model->SetupAttachment(SphereComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetupAttachment(SphereComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->InitSphereRadius(PlayerSize);
	SpringArm->AddLocalOffset(DefaultCameraDistance*FVector::RightVector);
	SpringArm->AddLocalRotation(FRotator(0.0f, -90.0f, 0.0f));

}

void print(FString text) {
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, text);
}

// Called every frame
void APlayerCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	// Clamp movement input.
	MovementInput = MovementInput.GetClampedToMaxSize(1.0f);
	print(MovementInput.ToString());
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAxis("MoveX", this, &APlayerCharacter::MoveX);
	InputComponent->BindAxis("MoveY", this, &APlayerCharacter::MoveY);
}

void APlayerCharacter::MoveX(float AxisValue) {
	MovementInput.X = AxisValue;
}

void APlayerCharacter::MoveY(float AxisValue) {
	MovementInput.Y = AxisValue;
}

void APlayerCharacter::BeginOverlap(UPrimitiveComponent * thisguy, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
}

void APlayerCharacter::EndOverlap(UPrimitiveComponent * thisguy, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
}

