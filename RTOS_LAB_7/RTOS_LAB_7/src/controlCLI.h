/*
 * controlCLI.h
 *
 * Created: 2/22/2023 1:02:34 PM
 *  Author: michael.bottita
 */ 


#ifndef CONTROLCLI_H_
#define CONTROLCLI_H_

portBASE_TYPE prvTaskStatsCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString);
portBASE_TYPE prvChangeMaxSpeed(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);
portBASE_TYPE prvChangeAcceleration(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);
portBASE_TYPE prvSendToFloor(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);
portBASE_TYPE prvEmergencyStop(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);
portBASE_TYPE prvEmergencyClear(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);


ToggleInfo_s LEDStructInfo;

bool LedTask1Active;
bool LedTask2Active;
bool LedTask3Active;

void RegisterCommands(void);

#endif /* CONTROLCLI_H_ */