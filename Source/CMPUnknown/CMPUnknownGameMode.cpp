// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "CMPUnknown.h"
#include "CMPUnknownGameMode.h"
#include "CMPUnknownCharacter.h"

ACMPUnknownGameMode::ACMPUnknownGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Dynamic/Character/Blueprints/CharacterPlayer_BP"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
