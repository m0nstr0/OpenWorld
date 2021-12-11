// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "OWPathAssetNode.h"
#include "OWPathAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class OPENWORLDPLUGIN_API UOWPathAsset : public UObject
{
	GENERATED_BODY()

public:

	UOWPathAsset() : Height(180.f), Radius(33.f) {}

	UPROPERTY(EditAnywhere, meta = (ClampMin = "10.0"))
	float Height;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "10.0"))
	float Radius;

	UPROPERTY()
	TArray<UOWPathAssetNode*> Nodes;

	UFUNCTION(BlueprintCallable)
	TArray<UOWPathAssetNode*> GetNodes() const
	{
		return Nodes;
	};
};
