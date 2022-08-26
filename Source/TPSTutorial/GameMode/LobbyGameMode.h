// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TPSTUTORIAL_API ALobbyGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	// check if enough players have entered the lobby
	// if so, travel to the actual game map
	virtual void PostLogin(APlayerController* NewPlayer) override;
	
};
