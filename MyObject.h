// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyObject.generated.h"

/**
 * Declaration Part
 */
UCLASS(Blueprintable)
class PRAC1_API UMyObject : public UObject
{
	GENERATED_BODY()

	public:
		UMyObject();

		UPROPERTY(BlueprintReadOnly, Category = "VariableList")
		float myFloat;

		UFUNCTION(BlueprintCallable, Category = "FunctionList")
		void myFunction();
	
};
