/************************************************************************
 * LES10A110 Principles of C-programming
 * Name: Serhat Altay
 * Date: 07/05/2022
 * By submitting this work for evaluation, I certify that
 * 1) I myself wrote all the code in this file
 * 2) I have not given this code to anyone else
 *
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "methods.h"
#define lineSize 1024
#define GWh 1000000

node *readFile(char *filename, node *head, node *tail)
{
    int firstRow = 0;
    char line[lineSize];
    FILE *fptr;

    // Reading the file.
    if ((fptr = fopen(filename, "r")) == NULL)
    {
        printf("Failed to open file, terminating\n");
        exit(0);
    }
    else
    {
        fptr = fopen(filename, "r");
        while (fgets(line, lineSize, fptr) != NULL)
        {
            int column = 0;    // Getting the semicolon separeted values from the row.
            if (firstRow != 0) // Getting rid of the first row (column names) of the file.
            {
                // Creating a new node for every row in the file.
                node *new = (node *)malloc(sizeof(node));
                if (head == NULL)
                {
                    head = new;
                    tail = new;
                }
                else
                {
                    tail->next = new;
                    tail = new;
                }
                for (char *token = strtok(line, ";"); token != NULL; token = strtok(NULL, ";"))
                {
                    // Storing the file data into the linked list.
                    if (column == 0)
                    {
                        strcpy(new->timestamp, token);
                        column++;
                    }
                    else if (column == 1)
                    {
                        new->week = atoi(token);
                        column++;
                    }
                    else if (column == 2)
                    {
                        new->consumption = atoi(token);
                        column++;
                    }
                    else if (column == 3)
                    {
                        new->solarPower = atoi(token);
                        column++;
                    }
                    else if (column == 4)
                    {
                        new->windPower = atoi(token);
                        column++;
                    }
                    else if (column == 5)
                    {
                        new->hydroPower = atoi(token);
                        column++;
                    }
                    else if (column == 6)
                    {
                        new->nuclearPower = atoi(token);
                        column++;
                    }
                    else if (column == 7)
                    {
                        new->CHP = atoi(token);
                        column++;
                    }
                    else if (column == 8)
                    {
                        new->thermalPower = atoi(token);
                        column++;
                    }
                }
                new->next = NULL;
            }
            firstRow = 1;
        }
    }
    fclose(fptr);

    // Taking the year, month, day, hour, and minute data from the timestamp character to save it internally.
    for (node *itr = head; itr != NULL; itr = itr->next)
    {
        char delimiters[4] = ". :";  // Data in timestamp is separated with the characters ".", " ", ":". 
        int tokenItr = 0;
        for (char *token = strtok(itr->timestamp, delimiters); token != NULL; token = strtok(NULL, delimiters))
        {
            if (tokenItr == 0)
            {
                itr->timestampDay = atoi(token);
                tokenItr++;
            }
            else if (tokenItr == 1)
            {
                itr->timestampMonth = atoi(token);
                tokenItr++;
            }
            else if (tokenItr == 2)
            {
                itr->timestampYear = atoi(token);
                tokenItr++;
            }
            else if (tokenItr == 3)
            {
                itr->timestampHour = atoi(token);
                tokenItr++;
            }
            else if (tokenItr == 4)
            {
                itr->timestampMinute = atoi(token);
                tokenItr++;
            }
        }
    }

    return head;
}

void analyzeConsumption(node *head)
{
    int numberOfMeasurements = 0;
    long totalConsumption = 0;
    int highestConsumption = 0;
    int lowestConsumption = 2147483647;
    char highestConsumptionDate[20], lowestConsumptionDate[20];

    // Analyzing the file.
    for (node *itr = head; itr != NULL; itr = itr->next)
    {
        numberOfMeasurements++;
        totalConsumption += itr->consumption;
        if (itr->consumption >= highestConsumption)
        {
            highestConsumption = itr->consumption;
            if (itr->timestampMinute == 0)
            {
                sprintf(highestConsumptionDate, "%d.%d.%d %d:%d0", itr->timestampDay, itr->timestampMonth, itr->timestampYear, itr->timestampHour, itr->timestampMinute);
            }
            else
            {
                sprintf(highestConsumptionDate, "%d.%d.%d %d:%d", itr->timestampDay, itr->timestampMonth, itr->timestampYear, itr->timestampHour, itr->timestampMinute);
            }
        }
        if (itr->consumption < lowestConsumption)
        {
            lowestConsumption = itr->consumption;
            if (itr->timestampMinute == 0)
            {
                sprintf(lowestConsumptionDate, "%d.%d.%d %d:%d0", itr->timestampDay, itr->timestampMonth, itr->timestampYear, itr->timestampHour, itr->timestampMinute);
            }
            else
            {
                sprintf(lowestConsumptionDate, "%d.%d.%d %d:%d", itr->timestampDay, itr->timestampMonth, itr->timestampYear, itr->timestampHour, itr->timestampMinute);
            }
        }
    }
    double averageConsumption = (double)totalConsumption / numberOfMeasurements;

    // Printing the results on the screen.
    printf("Statistics on %d measurements:\n", numberOfMeasurements);
    printf("Consumption totaled %ld kWh, and averaged %0.1f kWh.\n", totalConsumption, averageConsumption);
    printf("The highest consumption, %d kWh, occurred on %s.\n", highestConsumption, highestConsumptionDate);
    printf("The lowest consumption, %d kWh, occurred on %s.\n", lowestConsumption, lowestConsumptionDate);

    // Writing the results to a file.
    FILE *fptr;
    fptr = fopen("consumption.txt", "w");
    fprintf(fptr, "Statistics on %d measurements:\n", numberOfMeasurements);
    fprintf(fptr, "Consumption totaled %ld kWh, and averaged %0.1f kWh.\n", totalConsumption, averageConsumption);
    fprintf(fptr, "The highest consumption, %d kWh, occurred on %s.\n", highestConsumption, highestConsumptionDate);
    fprintf(fptr, "The lowest consumption, %d kWh, occurred on %s.\n", lowestConsumption, lowestConsumptionDate);
    fclose(fptr);

    return;
}

void analyzeProduction(node *head)
{
    double solarPower, windPower, hydroPower, nuclearPower, CHP, thermalPower;

    // Creating a new file and writing the header row.
    FILE *fptr;
    fptr = fopen("production.csv", "w");
    fprintf(fptr, "Week;Solar power;Wind power;Hydropower;Nuclear power;CHP;Thermal power\n");
    fclose(fptr);

    // Analyzing the csv file and writing the results to the new csv file.
    fptr = fopen("production.csv", "a");
    for (int week = 1; week < 54; week++)
    {
        solarPower = 0, windPower = 0, hydroPower = 0, nuclearPower = 0, CHP = 0, thermalPower = 0;
        for (node *itr = head; itr != NULL; itr = itr->next)
        {
            if (itr->week == week)
            {
                solarPower += itr->solarPower;
                windPower += itr->windPower;
                hydroPower += itr->hydroPower;
                nuclearPower += itr->nuclearPower;
                CHP += itr->CHP;
                thermalPower += itr->thermalPower;
            }
        }
        fprintf(fptr, "Week %d;%0.2f;%0.2f;%0.2f;%0.2f;%0.2f;%0.2f\n", week, solarPower / GWh, windPower / GWh, hydroPower / GWh, nuclearPower / GWh, CHP / GWh, thermalPower / GWh);
    }
    fclose(fptr);

    return;
}

node *clearLinkedList(node *head)
{
    // Clearing the linked list.
    node *itr = head;
    while (itr != NULL)
    {
        head = itr->next;
        free(itr);
        itr = head;
    }

    return head;
}