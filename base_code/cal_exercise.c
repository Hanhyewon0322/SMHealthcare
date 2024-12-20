//
//  cal_exercise.c
//  Excercise for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_EXERCISES 100  			// Maximum number of exercises
#define MAX_EXERCISE_NAME_LEN 50	// Maximum length of the name of exercise


// To declare the structure of the exercises
static Exercise exercise_list[MAX_EXERCISES]; //�ִ� 100�� � ����ü  
int exercise_list_size = 0;//���� �ʱ�ȭ 


/*
    description : read the information in "excercises.txt"
*/

void loadExercises(const char* EXERCISEFILEPATH) {
    FILE *file = fopen("exercises.txt", "r");//���� �б���� ���� , �ȿ����� �ٲ���ϴ�.. ������ EXERCISEFILEPATH Ȱ��.. 
    if (file == NULL) {//���� �������ٸ� 
        printf("There is no file for exercises! \n");
        return;
    }

    // ToCode: to read a list of the exercises from the given file
    char line[256];
    while (fgets(line, sizeof(line), file))//���Ͽ��� ���پ� �б� 
	{
        char *name = strtok(line, " "); //��̸� 
        char *calories = strtok(NULL, " "); // Į�θ� �Ҹ� 
        if (name && calories) //�Ѵ� �ִٸ� 
		{
            strncpy(exercise_list[exercise_list_size].exercise_name, name, MAX_EXERCISE_NAME_LEN - 1); //�迭�� ���� 
            exercise_list[exercise_list_size].calories_burned_per_minute = atoi(calories);
            exercise_list_size++;
        if (exercise_list_size >= MAX_EXERCISES){//�ִ� ���޽� 
        	break;
		}
    }
    
	}		

    fclose(file);
}


/*
    description : to enter the selected exercise and the total calories burned in the health data
    input parameters : health_data - data object to which the selected exercise and its calories are added 
    return value : No
    
    operation : 1. provide the options for the exercises to be selected
    			2. enter the duration of the exercise
    			3. enter the selected exercise and the total calories burned in the health data
*/

void inputExercise(HealthData* health_data) {
    int choice, duration, i;
    
    // ToCode: to provide the options for the exercises to be selected
    printf("The list of exercises: \n"); //� ��� ��� 
	for (i = 0; i < exercise_list_size; i++) 
	{
        printf("%d. %s (%d kcal per minute)\n", i+1, exercise_list[i].exercise_name, exercise_list[i].calories_burned_per_minute);
    }
    printf("%d. Exit\n", exercise_list_size + 1); //���� �ɼ� 

    // ToCode: to enter the exercise to be chosen with exit option
	printf("Choose an exercise (1-%d) or %d to exit: ", exercise_list_size, exercise_list_size + 1);
    scanf("%d", &choice); //�Է� �ޱ�  
    
  // To enter the duration of the exercise
    if (choice > 0 && choice <= exercise_list_size) 
	{
   
    printf("Enter the duration of the exercise (in min.): "); //������ � �ҿ�ð� �Է¹ޱ� 
    scanf("%d", &duration);

    // ToCode: to enter the selected exercise and total calcories burned in the health data
    strcpy(health_data->exercises[health_data->exercise_count].exercise_name, exercise_list[choice-1].exercise_name);
        health_data->exercises[health_data->exercise_count].calories_burned_per_minute = exercise_list[choice-1].calories_burned_per_minute;
        health_data->exercise_count++;
        
    int calories_burned = exercise_list[choice-1].calories_burned_per_minute * duration;
        health_data->total_calories_burned += calories_burned; //�� �Ҹ� Į�θ� ��� 
        
        printf("Added %s for %d minutes. Total calories burned: %d\n", 
               exercise_list[choice-1].exercise_name, duration, health_data->total_calories_burned);
    } 
	else if (choice != exercise_list_size + 1) 
	{
        printf("Invalid choice. Please try again.\n");
    }

}
