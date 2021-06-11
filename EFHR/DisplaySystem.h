#pragma once

void SplashScreen(void);
void PAC(void);

void DialogDisplay(char toPrint[]);
void StoryDescriptor(void);
void GameSetup(void);

void UserInfo(char UserName[]);
void CityInfo(char CityName[]);

void UserPrint(short UserPosition);
void BuildingHeight(void);
void AvailableBuilding(Buildings Buil);
void ResourceDisplayer(City City);
void UserInfoDisplayer(City CityStr);
void GameInitialize(short GamePhase);

void SystemMessage(short MessageType);
void HardrainAlert(short Timer);