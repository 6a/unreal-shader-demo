#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Car.generated.h"

UCLASS()
class SHADERDEMO_API ACar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACar();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion")
	float MPH;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion")
	float WheelRotationFactor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion")
	FVector2D Direction;

	/* The mesh for this actor, with read access for blueprints */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Geometry")
	UStaticMeshComponent* Mesh;

	/* The Wheels for this actor, with read access for blueprints */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Geometry")
	UStaticMeshComponent* WheelFR;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Geometry")
	UStaticMeshComponent* WheelFL;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Geometry")
	UStaticMeshComponent* WheelRR;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Geometry")
	UStaticMeshComponent* WheelRL;

	UFUNCTION(BlueprintCallable, Category = "Manipulation")
	void StartMove(float TargetMPH, float RampUpTime);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	TArray<UStaticMeshComponent*> Wheels;
	bool bIsMoving;
	float TargetSpeedMPH;
	float RampUpTimeSeconds;
	float AccelerationLerp;

};
