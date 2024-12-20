//
//  cal_diets.c
//  Diets for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_DIETS 100      			// Maximum number of diets
#define MAX_FOOD_NAME_LEN 50		// Maximum length of the name of food


// list of diets 
static Diet diet_list[MAX_DIETS]; // �ִ� 100�� ����ü ���� 
static int diet_list_size = 0; // ���� ����� ���� �ʱ�ȭ 


/*
    description : read the information in "diets.txt"
*/

void loadDiets(const char* DIETFILEPATH) {
    FILE *file = fopen("diets.txt", "r"); //������ �б���� ���� //�ʹ� �ȿ����淡 �����߽��ϴ�.. 
    if (file == NULL) 
	{ //���Ͽ��� ���н�  
        printf("There is no file for diets! \n");
        return;
    }

     // ToCode: to read a list of the diets from the given file
    char line[256];
    while (fgets(line, sizeof(line), file)) 
	{
        char *name = strtok(line, " ");
        char *calories = strtok(NULL, " ");
        if (name && calories) 
		{
            strncpy(diet_list[diet_list_size].food_name, name, MAX_FOOD_NAME_LEN - 1);
            diet_list[diet_list_size].food_name[MAX_FOOD_NAME_LEN - 1] = '\0';
            diet_list[diet_list_size].calories_intake = atoi(calories);
            diet_list_size++;
        if (diet_list_size >= MAX_DIETS){//�ִ뿡 �����ߴ���  
        	break;
		}
    }
	}	
    fclose(file);
}

/*
    description : to enter the selected diet and the total calories intake in the health data
    input parameters : health_data - data object to which the selected diet and its calories are added 
    return value : No
    
    operation : 1. provide the options for the diets to be selected
    			2. enter the selected diet and the total calories intake in the health data
*/

void inputDiet(HealthData* health_data) {
    int choice, i;
    
    // ToCode: to provide the options for the diets to be selected
    printf("The list of diets:\n");
    for (i=0; i<diet_list_size; i++){ //���̾�Ʈ ��� ��� 
    	printf("%d. %s(%d kcal)\n", i+1, diet_list[i].food_name, diet_list[i].calories_intake);
	}
	printf("%d. Exit\n", diet_list_size +1); //���� �ɼ� 
    
	// ToCode: to enter the diet to be chosen with exit option
    printf("Choose a diet (1-%d) or %d to exit: ", diet_list_size, diet_list_size + 1);
    scanf("%d", &choice);

    // ToCode: to enter the selected diet in the health data
    if (choice > 0 && choice <= diet_list_size) 
	{
        strcpy(health_data->diet[health_data->diet_count].food_name, diet_list[choice-1].food_name);
        health_data->diet[health_data->diet_count].calories_intake = diet_list[choice-1].calories_intake;
        health_data->diet_count++;

    // ToCode: to enter the total calories intake in the health data
	health_data->total_calories_intake += diet_list[choice-1].calories_intake;
	printf("Added %s to your diet. Total calories intake: %d\n", 
               diet_list[choice-1].food_name, health_data->total_calories_intake);
    } 
	else if (choice != diet_list_size + 1) {
        printf("Invalid choice. Please try again.\n");
    }
}

