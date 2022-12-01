/************************************************************************
 * LES10A110 Principles of C-programming
 * Name: Serhat Altay
 * Date: 07/05/2022
 * By submitting this work for evaluation, I certify that
 * 1) I myself wrote all the code in this file
 * 2) I have not given this code to anyone else
 *
 *************************************************************************/

#ifndef METHODS_H
#define METHODS_H

struct electricityData
{
    char timestamp[20];
    short int timestampYear, timestampMonth, timestampDay, timestampHour, timestampMinute;
    int week, consumption, solarPower, windPower, hydroPower, nuclearPower, CHP, thermalPower;
    struct electricityData *next;
};

typedef struct electricityData node;

node *readFile(char *filename, node *head, node *tail);
void analyzeConsumption(node *head);
void analyzeProduction(node *head);
node *clearLinkedList(node *head);

#endif