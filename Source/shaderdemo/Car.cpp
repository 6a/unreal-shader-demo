#include "Car.h"

const float MPH_TO_CMS = 44.704f;

// Sets default values
ACar::ACar()
{
	 PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	WheelFR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelFR"));
	WheelFL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelFL"));
	WheelRR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelRR"));
	WheelRL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelRL"));

	const FAttachmentTransformRules AttachmentRule(EAttachmentRule::KeepRelative, true);
	WheelFR->AttachToComponent(Mesh, AttachmentRule);
	WheelFL->AttachToComponent(Mesh, AttachmentRule);
	WheelRR->AttachToComponent(Mesh, AttachmentRule);
	WheelRL->AttachToComponent(Mesh, AttachmentRule);

	Wheels.Add(WheelFR);
	Wheels.Add(WheelFL);
	Wheels.Add(WheelRR);
	Wheels.Add(WheelRL);

	MPH = 10;
	WheelRotationFactor = 1.3;
	Direction = FVector2D(0, 1);
}

void ACar::StartMove(float TargetMPH, float RampUpTime)
{
	bIsMoving = true;
	TargetSpeedMPH = TargetMPH;
	RampUpTimeSeconds = RampUpTime;
	AccelerationLerp = 0;
}

// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsMoving)
	{
		if (AccelerationLerp < 1)
		{
			float ChangePerTick = (RampUpTimeSeconds / DeltaTime) / 1;

			AccelerationLerp = FMath::Min(AccelerationLerp + ChangePerTick, 1.f);

			MPH = FMath::InterpEaseInOut(0.f, TargetSpeedMPH, AccelerationLerp, 2.f);
		}
	}

	float CMPerSecond = MPH * MPH_TO_CMS;

	for (auto WheelIter = Wheels.CreateConstIterator(); WheelIter; ++WheelIter)
	{
		float AddedRotation = DeltaTime * CMPerSecond * WheelRotationFactor;
		(*WheelIter)->AddLocalRotation(FRotator(AddedRotation, 0, 0));
	}

	FVector DirectionV3 = FVector(Direction.X, Direction.Y, 0);
	DirectionV3.Normalize();

	FRotator NewRotation = DirectionV3.Rotation();

	// Ignore location as this is done in the sequencer
	//FVector NewLocation = GetActorLocation() + (DeltaTime * CMPerSecond * DirectionV3);

	SetActorRotation(NewRotation);
}

