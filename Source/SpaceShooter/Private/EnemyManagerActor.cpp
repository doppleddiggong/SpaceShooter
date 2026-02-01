// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyManagerActor.h"

#include "EnemyActor.h"
#include "EngineUtils.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"

AEnemyManagerActor::AEnemyManagerActor()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);

	SpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPoint"));
	SpawnPoint->SetupAttachment(RootComponent);
	SpawnPoint->SetRelativeRotation(FRotator(-90.f, 180.f, 0.f));
}

void AEnemyManagerActor::BeginPlay()
{
	Super::BeginPlay();


	// 런타임 검증 추가
	const float MinSpawnFrequency = 0.1f;
	if (SpawnFrequency < MinSpawnFrequency)
	{
		UE_LOG(LogTemp, Warning,
			   TEXT("SpawnFrequency too low (%.6f). Clamped to %.2f"),
			   SpawnFrequency, MinSpawnFrequency);
		SpawnFrequency = MinSpawnFrequency;
	}
	
	SpawnPoints.Empty(10);
	for (TActorIterator<AActor> It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;
		if (Actor->GetActorNameOrLabel().Contains(TEXT("SpawnPoint")))
		{
			SpawnPoints.Add(Actor);
		}
	}
	SpawnPoints.Shrink();

	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AEnemyManagerActor::SpawnEnemy, SpawnFrequency, true);
}

void AEnemyManagerActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AEnemyManagerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyManagerActor::SpawnEnemy()
{
	// 최대 적 수 체크
	TArray<AActor*> ActiveEnemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyActor::StaticClass(), ActiveEnemies);

	if (ActiveEnemies.Num() >= MaxActiveEnemies)
	{
		return;
	}
	
	int32 SpawnIndex = FMath::RandRange(0, SpawnPoints.Num() - 1);

	// Avoid spawning at the same location consecutively
	if (SpawnIndex == PrevSpawnIndex)
	{
		SpawnIndex = (SpawnIndex + 1) % SpawnPoints.Num();
	}

	FTransform SpawnTransform = SpawnPoints[SpawnIndex]->GetActorTransform();
	GetWorld()->SpawnActor<AEnemyActor>(EnemyFactory, SpawnTransform);

	PrevSpawnIndex = SpawnIndex;
}
