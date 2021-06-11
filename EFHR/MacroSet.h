#pragma once

#define CityHeight 20
#define CityWidth 12

#define CityTop 1
#define CityLeft 52

#define MaxHeight 4
#define PowerHeight 4
#define FactoryHeight 3
#define ResidenceHeight 2

#define DialogLength 63

#define Tic 500

#define _C 1046.502
#define _D 1108.731
#define _E 1318.510
#define _G 1760.000
#define Morse 800

enum TF { False, True };

enum ConsoleColor {

	Black,
	D_Blue,
	D_Green,
	D_Cyan,
	D_Red,
	D_Violet,
	D_Yellow,
	Gray,
	D_Gray,
	Blue,
	Green,
	Cyan,
	Red,
	Violet,
	Yellow,
	White
};

enum KBArrow{

	LEFT = 75,
	RIGHT = 77,
	UP = 72,
	DOWN = 80
};

enum ConsoleBGColor{

	Back_Cyan = 191,
	Back_Yellow = 224
};

enum BuildingType
{

	Blank,
	Power,
	Factory,
	Residence
};

enum PhaseState {

	BuildingPhase,
	EnterProductionPhase,
	ProductionPhase,
	HardrainPhase,
	EndingPhase
};

enum ErrorCode {

	Canceled = -4,
	Confirm,
	NotingLeft,
	AlreadyOccupied
};