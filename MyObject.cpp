// Fill out your copyright notice in the Description page of Project Settings.

// Definition Part
#include "MyObject.h"

UMyObject::UMyObject()
{
	myFloat = 0;
}

void UMyObject::myFunction()
{
	UE_LOG(LogTemp, Warning, TEXT("Test Warning Text !"));
}