#ifndef BaseStruct
#define BaseStruct

typedef struct {

	char UserName[11];
	char CityName[11];
}User;

typedef struct {

	short PowerLeft;
	short FactoryLeft;
	short ResidenceLeft;
}Buildings;

typedef struct {

	int EnergyState;
	int TechnologyState;
	int CapitalState;
}Resources;

typedef struct City {

	User Usr;

	short UserPosition;

	Buildings Buil;

	short OccupyState[12];
	short Health[12];
	short BuildingLeft;

	Resources Res;

	int Score;
}City;

typedef struct Rain {

	short IsStarExist[12];
	short StarHeight[12];
}Rain;

#endif
