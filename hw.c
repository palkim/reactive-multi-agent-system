#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define _agentNoGold 0
#define _agentHasGold 1
#define _goldCluster 2                               
#define _obstacle 5
#define _depot 6
#define _crumb 9
#define _empty -1
           
typedef struct Agent{ 
  int hasGold;
  int agent_id;
  int x_coordinate;
  int y_coordinate;
  int** percepts_to_action;
  int first_empty_percept_to_action_index;
};

typedef struct GoldCluster{ 
  int number_of_golds;
  int x_coordinate;
  int y_coordinate; 
};

typedef struct Obstacle{ 
  int x_coordinate;
  int y_coordinate;
};

typedef struct Depot { 
  int x_coordinate;
  int y_coordinate;
  int number_of_golds;
};

typedef struct Crumb{ 
  int x_coordinate;
  int y_coordinate;
  int number_of_crumbs;
};

struct Agent* robots;
struct GoldCluster* gold_clusters;
struct Obstacle* obstacles;
struct Crumb* crumbs;
struct Depot depot;

int n = 0;
int*** grid;

int number_of_robots = 0;
int number_of_gold_clusters = 0;
int number_of_obstacles = 0;
int number_of_crumbs = 0;

void randomWalk(int robot_index){
  int robot_x = robots[robot_index].x_coordinate;
  int robot_y = robots[robot_index].y_coordinate;
 
  int best_x = robots[robot_index].x_coordinate;
  int best_y = robots[robot_index].y_coordinate;

  int candidate_x;
  int candidate_y;

  int i;
  int isDepot = 0;
  int num_crumb = 0;

}

int canRandomWalk(int robot_index){
  int robot_x = robots[robot_index].x_coordinate;
  int robot_y = robots[robot_index].y_coordinate;
 
  int canGoSomewhere = 0; 
  robots[robot_index].first_empty_percept_to_action_index = 0;

  if(robot_x - 1 >= 0){
    

    if(grid[robot_y][robot_x-1][0] == _empty || grid[robot_y][robot_x-1][0] == _depot || 
      grid[robot_y][robot_x-1][0] == _goldCluster || grid[robot_y][robot_x-1][0] == _crumb ){
      
      robots[robot_index].percepts_to_action[robots[robot_index].first_empty_percept_to_action_index][0] = robot_x-1;
      robots[robot_index].percepts_to_action[robots[robot_index].first_empty_percept_to_action_index][1] = robot_y;
      robots[robot_index].first_empty_percept_to_action_index++;
      canGoSomewhere = 1;

    }

    if(robot_y - 1 >= 0){
      
      if(grid[robot_y-1][robot_x-1][0] == _empty || grid[robot_y-1][robot_x-1][0] == _depot || 
        grid[robot_y-1][robot_x-1][0] == _goldCluster || grid[robot_y-1][robot_x-1][0] == _crumb ){
        
        robots[robot_index].percepts_to_action[robots[robot_index].first_empty_percept_to_action_index][0] = robot_x-1;
        robots[robot_index].percepts_to_action[robots[robot_index].first_empty_percept_to_action_index][1] = robot_y-1;
        robots[robot_index].first_empty_percept_to_action_index++;
        canGoSomewhere = 1;

      }
      
    } 

    if(robot_y + 1 < n){
      
      if(grid[robot_y+1][robot_x-1][0] == _empty || grid[robot_y+1][robot_x-1][0] == _depot || 
        grid[robot_y+1][robot_x-1][0] == _goldCluster || grid[robot_y+1][robot_x-1][0] == _crumb ){
        
        robots[robot_index].percepts_to_action[robots[robot_index].first_empty_percept_to_action_index][0] = robot_x-1;
        robots[robot_index].percepts_to_action[robots[robot_index].first_empty_percept_to_action_index][1] = robot_y+1;
        robots[robot_index].first_empty_percept_to_action_index++;
        canGoSomewhere = 1;

      }
      
    } 
 
  }
  if(robot_y - 1 >= 0){
    
    if(grid[robot_y-1][robot_x][0] == _empty || grid[robot_y-1][robot_x][0] == _depot || 
        grid[robot_y-1][robot_x][0] == _goldCluster || grid[robot_y-1][robot_x][0] == _crumb ){
        
        robots[robot_index].percepts_to_action[robots[robot_index].first_empty_percept_to_action_index][0] = robot_x;
        robots[robot_index].percepts_to_action[robots[robot_index].first_empty_percept_to_action_index][1] = robot_y-1;
        robots[robot_index].first_empty_percept_to_action_index++;
        canGoSomewhere = 1;

      }
  }
  if(robot_y + 1 < n){
    
    if(grid[robot_y+1][robot_x][0] == _empty || grid[robot_y+1][robot_x][0] == _depot || 
        grid[robot_y+1][robot_x][0] == _goldCluster || grid[robot_y+1][robot_x][0] == _crumb ){
        
        robots[robot_index].percepts_to_action[robots[robot_index].first_empty_percept_to_action_index][0] = robot_x;
        robots[robot_index].percepts_to_action[robots[robot_index].first_empty_percept_to_action_index][1] = robot_y+1;
        robots[robot_index].first_empty_percept_to_action_index++;
        canGoSomewhere = 1;

      }
  }
  if(robot_x + 1 < n){
    
    if(grid[robot_y][robot_x+1][0] == _empty || grid[robot_y][robot_x+1][0] == _depot || 
      grid[robot_y][robot_x+1][0] == _goldCluster || grid[robot_y][robot_x+1][0] == _crumb ){
      
      robots[robot_index].percepts_to_action[robots[robot_index].first_empty_percept_to_action_index][0] = robot_x+1;
      robots[robot_index].percepts_to_action[robots[robot_index].first_empty_percept_to_action_index][1] = robot_y;
      robots[robot_index].first_empty_percept_to_action_index++;
      canGoSomewhere = 1;

    }
    
    if(robot_y - 1 >= 0){
      
      if(grid[robot_y-1][robot_x+1][0] == _empty || grid[robot_y-1][robot_x+1][0] == _depot || 
        grid[robot_y-1][robot_x+1][0] == _goldCluster || grid[robot_y-1][robot_x+1][0] == _crumb ){
        
        robots[robot_index].percepts_to_action[robots[robot_index].first_empty_percept_to_action_index][0] = robot_x+1;
        robots[robot_index].percepts_to_action[robots[robot_index].first_empty_percept_to_action_index][1] = robot_y-1;
        robots[robot_index].first_empty_percept_to_action_index++;
        canGoSomewhere = 1;

      }
    } 

    if(robot_y + 1 < n){
      
      if(grid[robot_y+1][robot_x+1][0] == _empty || grid[robot_y+1][robot_x+1][0] == _depot || 
        grid[robot_y+1][robot_x+1][0] == _goldCluster || grid[robot_y+1][robot_x+1][0] == _crumb ){
        
        robots[robot_index].percepts_to_action[robots[robot_index].first_empty_percept_to_action_index][0] = robot_x+1;
        robots[robot_index].percepts_to_action[robots[robot_index].first_empty_percept_to_action_index][1] = robot_y+1;
        robots[robot_index].first_empty_percept_to_action_index++;
        canGoSomewhere = 1;

      }
    } 

  }
  return canGoSomewhere;

}

void buildGrid(){
  int i,j,k;
  int x;
  int y;
  int id;
  int hasGold;
  int depotGold;
  int clusterGold;
  int crumbNumber;

  for(i = 0 ; i < number_of_gold_clusters; i++){
    x = gold_clusters[i].x_coordinate;
    y = gold_clusters[i].y_coordinate;
    clusterGold = gold_clusters[i].number_of_golds;

    grid[y][x][0] = _goldCluster;
    grid[y][x][1] = clusterGold;

  }

  grid[depot.y_coordinate][depot.x_coordinate][0] = _depot;
  grid[depot.y_coordinate][depot.x_coordinate][1] = depot.number_of_golds;

  for(i = 0 ; i < number_of_crumbs; i++){
    x = crumbs[i].x_coordinate;
    y = crumbs[i].y_coordinate;
    crumbNumber = crumbs[i].number_of_crumbs;

    grid[y][x][0] = _crumb;
    grid[y][x][1] = crumbNumber;

  }

  for(i = 0 ; i < number_of_robots; i++){
    x = robots[i].x_coordinate;
    y = robots[i].y_coordinate;
    hasGold = robots[i].hasGold;
    id = robots[i].agent_id;

    if(hasGold == 0){
      grid[y][x][0] = _agentNoGold;
    } else { //1
      grid[y][x][0] = _agentHasGold;
    }
    grid[y][x][1] = id;
  }
  
  
  
  for(i = 0 ; i < number_of_obstacles; i++){
    x = obstacles[i].x_coordinate;
    y = obstacles[i].y_coordinate;

    grid[y][x][0] = _obstacle;
    grid[y][x][1] = _empty;


  }
  

}

void printGrid(){
  int i, j, k;  

  printf("\n");
  
  for(i = 0 ; i < n ; i++){
      for(j = 0 ; j < n ; j++){
          
        switch(grid[i][j][0]){
          case _agentHasGold:
            printf("R");
            printf("%d", grid[i][j][1]);
            break;
          case _agentNoGold:
            printf("r");
            printf("%d", grid[i][j][1]);
            break;
          case _obstacle:
            printf("O ");
            break;
          case _goldCluster:
            printf("G");
            printf("%d", grid[i][j][1]);            
            break;
          case _depot:
            printf("D");
            printf("%d", grid[i][j][1]);
            break;
          case _empty:
            printf("__");
            break;
          case _crumb:
            printf("*");
            printf("%d", grid[i][j][1]);
            break;
          default:
            break;
        }

        printf(" ");
      }
      printf("\n");
  }
  printf("\n");
  
}

int main(){
	
  srand(time(0));

	FILE *fp = fopen("env.inp","r");
	
  if(fp == NULL){	
		perror("Unable to find the input file!");
		exit(1);
	}

	char line[100];
  char** descriptions;
    
	int i, j, k;
	int lineCount = 0;
    
  int number_of_descriptions = 0;
  int description_index = 0;
  int num_of_chars_in_line = 0;

  int golds_to_carry = 0;

	while(fgets(line, sizeof(line), fp ) ){
    num_of_chars_in_line = 0;
		switch(lineCount){
			case 0:
        n = atoi(line);
        grid = malloc(n * sizeof(int**));
        for(i = 0 ; i < n ; i++){
          grid[i] = malloc(n * sizeof(int*));
          
          //grid[i] = malloc( ( (n * 2) + (n - 1) ) * sizeof(char));
        }
        for(i = 0 ; i < n ; i++){
          for(j = 0 ; j < n ; j++){
            grid[i][j] = malloc(3 * sizeof(int));
          }
        }

        for(i = 0; i < n; i++){
          for(j = 0; j < n; j++){
            for(k = 0; k < 2; k++){
              grid[i][j][k] = _empty;
            }
          }
        }

        break;
      case 1:
          number_of_robots = atoi(line);
          robots = malloc(number_of_robots * sizeof(struct Agent));
          break;
      case 2:
          number_of_gold_clusters = atoi(line);
          gold_clusters = malloc(number_of_gold_clusters * sizeof(struct GoldCluster));
          break;
      case 3:
          number_of_obstacles = atoi(line);
          obstacles = malloc(number_of_obstacles * sizeof(struct Obstacle));
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
  int id = 0;
  for(i = 0; i < number_of_descriptions; i++){
      int x_decimal_places = 0;
      int y_decimal_places = 0;
      int z_decimal_places = 0;
      int x = 0;
      int y = 0;
      int z = 0;
      j = 0;
      
      if(descriptions[i][j] == 'r'){
        id++;
        j = 2;
        while(descriptions[i][j] != ' '){
          x_decimal_places++;
          j++;
        }
        j = 2;
        int x_decimal_places_holder = x_decimal_places;
        while(x_decimal_places_holder != 0) {
          if(descriptions[i][j] != ' '){
            x += (descriptions[i][j] - '0') * pow(10, x_decimal_places_holder-1);
            x_decimal_places_holder--;
          }
          j++; 
        }
        j = 2 + x_decimal_places;
        while(descriptions[i][j] != '\0'){
          if(descriptions[i][j] != ' '){
            y_decimal_places++;
          }
          j++;
        }

        j = 2 + x_decimal_places;
        
        int y_decimal_places_holder = y_decimal_places;
        while(y_decimal_places_holder != 0){
          if(descriptions[i][j] != ' '){
            y += (descriptions[i][j] - '0') * pow(10, y_decimal_places_holder-1);
            y_decimal_places_holder--;
          }
          j++;
        }

        struct Agent robot;
        robot.hasGold = 0;
        robot.agent_id = id;
        robot.x_coordinate = x - 1;
        robot.y_coordinate = y - 1;
        robot.percepts_to_action = malloc(8 * sizeof(int*));
        int p;
        for(p = 0; p < 8; p++){
          robot.percepts_to_action[p] = malloc(2 * sizeof(int));
        }
        robot.first_empty_percept_to_action_index = 0;

        robots[robot.agent_id - 1] = robot;

        
      } else if(descriptions[i][j] == 'g'){
          id++;
          j = 2;
          while(descriptions[i][j] != ' '){
            x_decimal_places++;
            j++;
          }

          j = 2;
          int x_decimal_places_holder = x_decimal_places;
          while(x_decimal_places_holder != 0) {
            if(descriptions[i][j] != ' '){
              x += (descriptions[i][j] - '0') * pow(10, x_decimal_places_holder-1);
              x_decimal_places_holder--;
            }
            j++; 
          }
          j = 2 + x_decimal_places + 1;
          while(descriptions[i][j] != ' '){
            y_decimal_places++;
            j++;
          }

          j = 2 + x_decimal_places + 1;

          int y_decimal_places_holder = y_decimal_places;
          while(y_decimal_places_holder != 0){
            if(descriptions[i][j] != ' '){
              y += (descriptions[i][j] - '0') * pow(10, y_decimal_places_holder-1);
              y_decimal_places_holder--;
            }
            j++;
          }

          j = 2 + x_decimal_places + 1 + y_decimal_places;
          while(descriptions[i][j] != '\0'){
            if(descriptions[i][j] != ' '){
              z_decimal_places++;
            }
            j++;
          }

          j = 2 + x_decimal_places + 1 + y_decimal_places;
          
          int z_decimal_places_holder = z_decimal_places;
          while(z_decimal_places_holder != 0){
            if(descriptions[i][j] != ' '){
              z += (descriptions[i][j] - '0') * pow(10, z_decimal_places_holder-1);
              z_decimal_places_holder--;
            }
            j++;
          }

          struct GoldCluster gold;
          gold.number_of_golds = z;
          gold.x_coordinate = x - 1;
          gold.y_coordinate = y - 1;

          golds_to_carry += gold.number_of_golds;

          gold_clusters[id - number_of_robots - 1] = gold;


      } else if(descriptions[i][j] == 'o'){
        id++;
        j = 2;
        while(descriptions[i][j] != ' '){
          x_decimal_places++;
          j++;
        }
        j = 2;
        int x_decimal_places_holder = x_decimal_places;
        while(x_decimal_places_holder != 0) {
          if(descriptions[i][j] != ' '){
            x += (descriptions[i][j] - '0') * pow(10, x_decimal_places_holder-1);
            x_decimal_places_holder--;
          }
          j++; 
        }
        j = 2 + x_decimal_places;
        while(descriptions[i][j] != '\0'){
          if(descriptions[i][j] != ' '){
            y_decimal_places++;
          }
          j++;
        }

        j = 2 + x_decimal_places;
        
        int y_decimal_places_holder = y_decimal_places;
        while(y_decimal_places_holder != 0){
          if(descriptions[i][j] != ' '){
            y += (descriptions[i][j] - '0') * pow(10, y_decimal_places_holder-1);
            y_decimal_places_holder--;
          }
          j++;
        }

        struct Obstacle obstacle;
        obstacle.x_coordinate = x - 1;
        obstacle.y_coordinate = y - 1;
        
        obstacles[id - number_of_robots - number_of_gold_clusters - 1] = obstacle;

        
        

      } else /*(descriptions[i][j] == "d")*/{
          id++;
          j = 2;
          while(descriptions[i][j] != ' '){
            x_decimal_places++;
            j++;
          }
          j = 2;
          int x_decimal_places_holder = x_decimal_places;
          while(x_decimal_places_holder != 0) {
            if(descriptions[i][j] != ' '){
              x += (descriptions[i][j] - '0') * pow(10, x_decimal_places_holder-1);
              x_decimal_places_holder--;
            }
            j++; 
          }
          j = 2 + x_decimal_places;
          while(descriptions[i][j] != '\0'){
            if(descriptions[i][j] != ' '){
              y_decimal_places++;
            }
            j++;
          }

          j = 2 + x_decimal_places;
          
          int y_decimal_places_holder = y_decimal_places;
          while(y_decimal_places_holder != 0){
            if(descriptions[i][j] != ' '){
              y += (descriptions[i][j] - '0') * pow(10, y_decimal_places_holder-1);
              y_decimal_places_holder--;
            }
            j++;
          }

          depot.x_coordinate = x - 1;
          depot.y_coordinate = y - 1;
          depot.number_of_golds = 0;

      }
  }
  
  buildGrid();
  printf("golds to carry: %d\n", golds_to_carry);
  int robot_index;
  while(golds_to_carry != 0){
    //randomize this!
    for(robot_index = 0; robot_index < number_of_robots; robot_index++){
      int robot_x = robots[robot_index].x_coordinate;
      int robot_y = robots[robot_index].y_coordinate;
      int hasGold = robots[robot_index].hasGold;
      int random;
      
      if(canRandomWalk(robot_index)){
        randomWalk(robot_index);
      } else {
        continue;
      }      

    }
    break;
  }
  buildGrid();
  printGrid();
  
  for (i = 0; i < n; i++){
    free(grid[i]);
  }

  for (i = 0; i < number_of_descriptions; i++){
    free(descriptions[i]);
  }

  free(descriptions);
  free(robots);
  free(gold_clusters);
  free(obstacles);
  free(grid);

	return 0;
}
