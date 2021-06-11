#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "MacroSet.h"
#include "StructSet.h"
#include "BaseSystem.h"
#include "BuildingSystem.h"
#include "DisplaySystem.h"

short BuildingConfirm(short BuildingType) {

	char UserInput;

	SystemMessage(Confirm);

	UserInput = _getch();

	if (BuildingType == Power && UserInput == 'e') {

		Beep((DWORD)_C, 100);
		return True;
	}
	if (BuildingType == Factory && UserInput == 't') {

		Beep((DWORD)_D, 100);
		return True;
	}
	if (BuildingType == Residence && UserInput == 'm') {

		Beep((DWORD)_E, 100);
		return True;
	}

	return False;
}

void BuildingRepair(City* CityPtr) {

	if (CityPtr->Res.TechnologyState < 15) return;

	switch (CityPtr->OccupyState[CityPtr->UserPosition]) {

	case Blank:

		return;

	case Power:

		if (CityPtr->Health[CityPtr->UserPosition] == PowerHeight) return;
		++CityPtr->Health[CityPtr->UserPosition];
		break;

	case Factory:

		if (CityPtr->Health[CityPtr->UserPosition] == FactoryHeight) return;
		++CityPtr->Health[CityPtr->UserPosition];
		break;

	case Residence:

		if (CityPtr->Health[CityPtr->UserPosition] == ResidenceHeight) return;
		++CityPtr->Health[CityPtr->UserPosition];
		break;

	default:

		return;
	}

	CityPtr->Res.TechnologyState -= 15;
}

void MakePower(short UserPosition, short Health) {

	short Floor = 0;

	StringColor(Yellow);

	for (short i = 4; i > 0; --i) {

		CurPos(CityLeft + UserPosition, 16 + i);

		++Floor;

		if (Floor <= Health)
			putchar('E');
		else
			putchar(' ');
	}

	StringColor(White);

	CurPos(0, 23);
}

void MakeFactory(short UserPosition, short Health) {

	short Floor = 0;

	StringColor(Red);

	for (short i = 4; i > 0; --i) {

		CurPos(CityLeft + UserPosition, 16 + i);

		++Floor;

		if (Floor <= Health)
			putchar('T');
		else
			putchar(' ');
	}

	StringColor(White);

	CurPos(0, 23);
}

void MakeResidence(short UserPosition, short Health) {

	short Floor = 0;

	StringColor(Green);

	for (short i = 4; i > 0; --i) {

		CurPos(CityLeft + UserPosition, 16 + i);

		++Floor;

		if (Floor <= Health)
			putchar('M');
		else
			putchar(' ');
	}

	StringColor(White);

	CurPos(0, 23);
}

void BuildingBuilder(City City) {

	for (short i = 0; i < CityWidth; ++i) {

		if (!City.OccupyState[i]) MakePower(i, 0);
		if (City.OccupyState[i] == Power) MakePower(i, City.Health[i]);
		else if (City.OccupyState[i] == Factory) MakeFactory(i, City.Health[i]);
		else if (City.OccupyState[i] == Residence) MakeResidence(i, City.Health[i]);
	}
}