#pragma once

#include "Engine.h"

UENUM(BlueprintType)
enum class EStencilColor : uint8
{
    SC_Green = 250 UMETA(DisplayName="Green"),
    SC_Blue = 251 UMETA(DisplayName="Blue"),
    SC_Red = 252 UMETA(DisplayName="Red"),
    SC_White = 253 UMETA(DisplayName="White")
};
