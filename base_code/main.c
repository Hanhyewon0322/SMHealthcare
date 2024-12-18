//
//  main.c
//  Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define EXERCISEFILEPATH "exercises.txt"
#define DIETFILEPATH "diets.txt"
#define HEALTHFILEPATH "health_data.txt"

static int choice;

int main() {
	// To initialize the health data object
    HealthData health_data = {0};
    
    // Tocode: to read the list of the exercises and diets
    loadExercises(EXERCISEFILEPATH);
    loadDiets(DIETFILEPATH);

    // ToCode: to run the "Healthcare Management Systems" until all calories are used up or the user wants to exit the system
    do {
    	if (health_data.total_calories_intake - 1300 - health_data.total_calories_burned<=0){
            printf("You have consumed all your calories for today! \n");
		} 
		else{
			printf("\n=======================================================================\n");
        	printf("[Healthcare Management Systems] \n");
        	printf("1. Exercise \n");
        	printf("2. Diet \n");
        	printf("3. Show logged information \n");
        	printf("4. Exit \n");
        	printf("Select the desired number: ");
        	scanf("%d", &choice);
        	printf("=======================================================================\n");
        }
        
		// ToCode: to run the sysmtem based on the user's choice
        switch (choice) {
            case 1:
            	inputExercise(&health_data);// 운동 정보 입력 함수 호출
                break;
                
            case 2:
            	inputDiet(&health_data);// 식단 정보 입력 함수 호출 
                break;
                
            case 3:
            	printHealthData(&health_data);// 건강 데이터 출력 함수 호출 
                break;
                
            case 4:
            	
    			printf("Exit the system.\n");
    			printf("=======================================================================\n");
                saveData(HEALTHFILEPATH, &health_data); // 종료 전 데이터 저장 
				break;
                
            default:
                printf("[Error] Invalid option. \n");
                printf("Please try again! \n");
        }
    } while (choice != 4 && health_data.total_calories_intake-1300- );//나가기 옵션 선택 아니면 남은 칼로리가 0이 될시 

    return 0;
}

