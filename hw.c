#include <stdio.h>
#include <stdlib.h>

int main(){
	
	FILE *fp = fopen("env.inp","r");
	
    if(fp == NULL){	
		perror("Unable to find the input file!");
		exit(1);
	}

    int n = 0;
    int number_of_robots = 0;
	int number_of_gold_clusters = 0;
	int number_of_obstacles = 0;

	char line[100];
    char** descriptions;
    char** grid;

    int** robots;
    int** gold;
    int** obstacles;
    int depot[2];
    
	int i, j;
	int lineCount = 0;
    
    int number_of_descriptions = 0;
    int description_index = 0;
    int num_of_chars_in_line = 0;

	while(fgets(line, sizeof(line), fp ) ){
        num_of_chars_in_line = 0;
		switch(lineCount){
			case 0:
                n = atoi(line);
                grid = malloc(n * sizeof(char*));
                for(i = 0 ; i < n ; i++){
                    grid[i] = malloc( ( (n * 2) + (n - 1) ) * sizeof(char));
                }
                
                for(i = 0 ; i < n ; i++){
                    for(j = 0 ; j < ( (n*2) + (n-1) ) ; j++){
                        if( ( j + 1 ) % 3 == 0){
                            grid[i][j] = ' ';
                        } else {
                            grid[i][j] = '_';
                        }
                    }
                }
                
                for(i = 0 ; i < n ; i++){
                    for(j = 0 ; j < ( (n*2) + (n-1) ) ; j++){
                        printf("%c", grid[i][j]);
                    }
                    printf("\n");
                }

                break;
            case 1:
                number_of_robots = atoi(line);
                break;
            case 2:
                number_of_gold_clusters = atoi(line);
                break;
            case 3:
                number_of_obstacles = atoi(line);
                break;
            case 4:
                number_of_descriptions += number_of_robots; 
                number_of_descriptions += number_of_gold_clusters;
                number_of_descriptions += number_of_obstacles;
                number_of_descriptions += 1;

                descriptions = malloc(number_of_descriptions * sizeof(char*));
                
                i = 0;
                while(line[i] != 10){
                    num_of_chars_in_line++;
                    i++;
                }
                
                descriptions[description_index] = (char*) malloc(num_of_chars_in_line+1 * sizeof(char));

                for(i = 0; i < num_of_chars_in_line; i++){
                    descriptions[description_index][i] = line[i];
                }
                descriptions[description_index][num_of_chars_in_line] = '\0';
                description_index++;                 
                break;
            default:
                i = 0;
                while(line[i] != 10){
                    num_of_chars_in_line++;
                    i++;
                }
                descriptions[description_index] = (char*) malloc(num_of_chars_in_line+1 * sizeof(char));

                for(i = 0; i < num_of_chars_in_line; i++){
                    descriptions[description_index][i] = line[i];
                }
                descriptions[description_index][num_of_chars_in_line] = '\0';
                description_index++;
                break;
		}
        lineCount++;
	}
    
    for(i = 0; i < number_of_descriptions; i++){
        j = 0;
        while(descriptions[i][j] != '\0'){
            printf("%c", descriptions[i][j]);
            j++;
        }
        printf("\n");
    }
    for (i = 0; i < number_of_descriptions; i++)
        free(descriptions[i]);
 
    free(descriptions);
	return 0;
}
