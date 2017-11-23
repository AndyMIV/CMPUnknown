// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "CMPUnknown.h"
#include "CMPUnknownGameMode.h"
#include "CMPUnknownCharacter.h"

ACMPUnknownGameMode::ACMPUnknownGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Dynamic/Character/Blueprints/Ue4ASP_Character_Depreceated"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Dynamic/Character/Blueprints/CharacterPlayer_BP"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
//		DefaultPawnClass = PlayerPawnBPClass.Class;
	//}
}
