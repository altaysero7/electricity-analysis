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
#include "methods.h"

int main()
{
    int selection;
    char file[20];
    node *head = NULL;
    node *tail = NULL;

    do
    {
        printf("1)Read the file\n");
        printf("2)Analyze consumption\n");
        printf("3)Analyze production\n");
        printf("0)Stop\n");
        printf("Select an Item:\n");
        scanf("%d", &selection);

        switch (selection)
        {
        case 1:
            printf("Please enter the file name\n");
            scanf("%s", file);
            if (head != NULL)
            {
                tail = clearLinkedList(head);
                head = tail;
            }
            head = readFile(file, head, tail);
            break;
        case 2:
            if (head == NULL)
            {
                printf("Please read a file before this option.\n");
                break;
            }
            else
            {
                analyzeConsumption(head);
            }
            break;
        case 3:
            if (head == NULL)
            {
                printf("Please read a file before this option.\n");
                break;
            }
            else
            {
                analyzeProduction(head);
            }
            break;
        case 0:
            tail = clearLinkedList(head);
            head = tail;
            exit(0);
        default:
            printf("Unknown selection, please try again.\n");
        }
    } while (selection != 0);
}