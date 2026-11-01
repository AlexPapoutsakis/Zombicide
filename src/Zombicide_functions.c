#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/Zombicide.h"

/* board creation function*/
int **create_board( int  size_r , int size_c ){
    int **board = (int**)malloc( size_r * sizeof(int *)); 
      
    if ( board == NULL ) 
         exit(1); 

    for(int i = 0; i<size_r; i++){
         board[i] = (int*)malloc(size_c * sizeof(int)); 
    
          if( board[i] == NULL) 
             exit(1); 
    
     for(int j = 0; j < size_c; j++) 
         board[i][j] = 0; 
    
    }

  return board; 

}

/* function that prints the board */
void print_board ( int **board , int size_r , int size_c , int level , int score , int sound_source){



        printf("    ");
        for ( int j = 0; j<size_c; j++){
            printf("%3d " , j+1); 
        } 
        printf("\n");

    for (int j=0; j<size_c*4+3; j++){
        printf("-"); 
    }
      printf("\n");



    for( int i = 0; i<size_r; i++){
        printf("%2d |", i+1);
      for ( int j = 0; j<size_c; j++){
        if(board[i][j] == 0)
          printf("%3s " , ".");
          else if(board[i][j] == -1 )
            printf("%3s " , "#");
            else 
             printf( "%3d " , board[i][j] ); 
      } 
      printf("\n");
    }
     printf("\n");
     print_sound_source(sound_source);
     printf("  Level  %d    -   Score  %d\n" , level , score);
     printf("\n");
     printf("   The zombies overrun us,\n   make your move: \n\n");

}

/* function that moves the zombies towards the sound source */
void sound_mov(int **board, int size_r, int size_c, int sound_source) {
    switch(sound_source) {
        
        case 1: /* UP */
            for (int j = 0; j < size_c; j++) {
                for (int i = 0; i < size_r; i++) {
                    if (board[i][j] == 0) {
                        for (int check = i + 1; check < size_r; check++) {
                            if (board[check][j] == -1)
                                break;
                            if (board[check][j] > 0) {
                                board[i][j] = board[check][j];
                                board[check][j] = 0;
                                break;
                            }
                        }
                    }
                }
            }
            break;

        case 2: /* DOWN */
            for (int j = 0; j < size_c; j++) {
                for (int i = size_r - 1; i >= 0; i--) {
                    if (board[i][j] == 0) {
                        for (int check = i - 1; check >= 0; check--) {
                            if (board[check][j] == -1)
                                break;
                            if (board[check][j] > 0) {
                                board[i][j] = board[check][j];
                                board[check][j] = 0;
                                break;
                            }
                        }
                    }
                }
            }
            break;

        case 3: /* LEFT */
            for (int i = 0; i < size_r; i++) {
                for (int j = 0; j < size_c; j++) {
                    if (board[i][j] == 0) {
                        for (int check = j + 1; check < size_c; check++) {
                            if (board[i][check] == -1)
                                break;
                            if (board[i][check] > 0) {
                                board[i][j] = board[i][check];
                                board[i][check] = 0;
                                break;
                            }
                        }
                    }
                }
            }
            break;

        case 4: /* RIGHT */
            for (int i = 0; i < size_r; i++) {
                for (int j = size_c - 1; j >= 0; j--) {
                    if (board[i][j] == 0) {
                        for (int check = j - 1; check >= 0; check--) {
                            if (board[i][check] == -1)
                                break;
                            if (board[i][check] > 0) {
                                board[i][j] = board[i][check];
                                board[i][check] = 0;
                                break;
                            }
                        }
                    }
                }
            }
            break;
    }
}

/* fucntion that prints the sound source */
void print_sound_source(int sound_source){
    if(sound_source == 1 )
       printf("   Sound source: UP\n");
    else if(sound_source == 2)
       printf("   Sound source: DOWN\n");
    else if(sound_source == 3)
       printf("   Sound source: LEFT\n");
    else 
       printf("   Sound source: RIGHT\n");
}

  /* function that checks if there are zombies on the board*/

  int zombies_dead(int **board ,int size_r , int size_c){
    int i,j; 

     for( i=0; i<size_r; i++){
        for(j=0; j<size_c; j++){
            if ( board[i][j] > 0 ) 
              return 0; 
              
           }
       }
    return 1; 
}

 /* function that places the buildings on the board */
  void place_buildings(int **board , int size_r , int size_c){
      int num_building ,  random_i , random_j , building_size , total_cell, direction ;
      int new_i , new_j;
      int count_1 = 0 , count_2; 

     /* calculates space for zombies and buildings in the board */ 
      total_cell = size_r * size_c ; 
      
      /* as the board gets bigger , the probability of buildings spawning increases*/
        if ( total_cell < 40 )
           num_building = 1; 
       else if ( total_cell < 100 )
           num_building = 1 + (int) (( double ) rand() / ((double)RAND_MAX + 1 ) * 3); 
       else if ( total_cell < 225) 
           num_building = 2 +  ( (int) (( double ) rand() / ((double)RAND_MAX + 1 ) * 4) + 1 )  ;
       else if ( total_cell < 450)
           num_building = 3 + ( (int) (( double ) rand() / ((double)RAND_MAX + 1 ) * 5 ) + 1 );
        else if ( total_cell < 700 )
           num_building = 4 + ( (int) (( double ) rand() / ((double)RAND_MAX + 1 ) * 6 ) + 2 );
        else 
           num_building = 5 + ( (int) (( double ) rand() / ((double)RAND_MAX + 1 ) * 6 ) + 3 );
           

        
        while ( count_1 < num_building ) { /* repeats the loop depending on how many buildings are created on the board*/
            count_2 = 0; /* counts how many times the loop will be repeated to calculate how much space of the board each building will take*/
              do{
                  random_i = (int) ((double) rand() / ((double)RAND_MAX + 1) * size_r); 
                  random_j = (int) ((double) rand() / ((double)RAND_MAX + 1) * size_c); 
                }while(board[random_i][random_j] == -1 );
         
                board[random_i][random_j] = -1;

              building_size = (int) ((double) rand() / ((double)RAND_MAX + 1) * 5 ) + 2; 

              int attempts = 0; 
              int max_attempts = size_r * size_c *3 ; /* adds a small limit in case the building can't find available space to expand */

                 while ( count_2 < building_size-1 && attempts < max_attempts ) { 
                     direction =  (int) ((double) rand() / ((double)RAND_MAX + 1) * 4 ); 

                     new_i = random_i; 
                     new_j = random_j; 

                     switch(direction){
                         case 0: new_i = random_i - 1;
                                break;
                         case 1: new_i = random_i + 1;
                                break;
                         case 2: new_j = random_j - 1;
                                break;
                         case 3: new_j = random_j + 1;
                                break;
                         
                     }

                       if (new_i >= 0 && new_i < size_r && new_j >= 0 && new_j < size_c && board[new_i][new_j] != -1 ){
                           random_i = new_i; 
                           random_j = new_j; 

                           board[random_i][random_j] = -1; 
                            count_2++; 
                       }
                       attempts++;
                 }
                        count_1++;
                    
            }
  }

  /* function to fill the board with zombies */
  void place_zombies(int **board , int size_r , int size_c , int z){ 
     int i , j; 

      for( i = 0; i < size_r; i++){
        for( j = 0; j < size_c; j++){ 
            if ( board[i][j] == 0 )
               board[i][j] = (int)( (double) rand() / ((double)RAND_MAX + 1 ) * z) + 1; 
        }
      } 
    }

    /* fucntion for the available commands of the player*/
    char command(){
        char cmd; 
        printf("Press 'X/x' to exit the game \n");
        printf("Press 'B/b' to select the BOMB as your weapon of choice\n");
        printf("Press 'P/p' to select the PLASMAGUN as your weapon of choice\n");
        printf("Press 'N/n' to select the NEUROGUN as your weapon of choice\n"); 

          do{ 
             scanf(" %c" , &cmd ); 
               if( cmd != 'X' && cmd != 'x' && cmd != 'B' && cmd != 'b' && cmd != 'P' && cmd != 'p' && cmd != 'N' && cmd != 'n')
                    printf("Please enter a different move:   \n");

          }while( cmd != 'X' && cmd != 'x' && cmd != 'B' && cmd != 'b' && cmd != 'P' && cmd != 'p' && cmd != 'N' && cmd != 'n' );

        return cmd; 
    }

    /* function for the bomb */
    
    int bomb(int **board, int size_i, int size_j, int target_i, int target_j) {
    int kills = 0;

    for (int i = target_i - 1; i <= target_i + 1; i++) {
        for (int j = target_j - 1; j <= target_j + 1; j++) {
            if (i >= 0 && i < size_i && j >= 0 && j < size_j) {
                if (board[i][j] > 0) {
                    board[i][j] = 0;
                    kills++;
                }
            }
        }
    }
    return kills;
}

/* function for plasmagun */

int plasmagun(int **board, int size_i, int size_j, char side, int target) {
    int kills = 0;

    if (side == 'l' || side == 'L') {
        for (int j = 0; j < size_j; j++) {

            if (board[target][j] == -1) 
              break;

            if (board[target][j] > 0) { 
                 board[target][j] = 0; 
                  kills++; 
                }
        }

    } else if (side == 'r' || side == 'R') {
        for (int j = size_j - 1; j >= 0; j--) {
           
            if (board[target][j] == -1) 
              break;

            if (board[target][j] > 0) { 
                board[target][j] = 0; 
                kills++; 
            }
        }
    } else if (side == 'u' || side == 'U') {
        for (int i = 0; i < size_i; i++) {

            if (board[i][target] == -1) 
               break;

            if (board[i][target] > 0) {
                 board[i][target] = 0;
                   kills++; 
                }
        }
    } else if (side == 'd' || side == 'D') {
        for (int i = size_i - 1; i >= 0; i--) {

            if (board[i][target] == -1) 
              break;

            if (board[i][target] > 0) {
                 board[i][target] = 0; 
                   kills++; 
                }
        }
    }

    return kills;
}


/*funcion for neurogun*/
int neurogun(int **board, int size_i, int size_j , int i ,int j, int target_type, int flag) {


      /*check for board edges or other zombie types*/
      if (i < 0 || i >= size_i || j < 0 || j >= size_j)
           return 0; 


     if (flag == 0 ) {
       if (board[i][j] != target_type)
           return 0;
     }
 

    //main weapon lonely zombie scan
    if (flag == 1){
        int cl_fr = 0; //cl_fr is close friend to scan for adjacent zombies
        if (i > 0 && board[i-1][j] == target_type)
         cl_fr = 1;
        if (i < size_i - 1 && board[i+1][j] == target_type)
         cl_fr = 1;
        if (j > 0 && board[i][j - 1] == target_type)
         cl_fr = 1;
        if (j < size_j - 1 && board[i][j+1] == target_type)
         cl_fr = 1;

        if (cl_fr == 0){
            printf("You cant shoot at a lone zombie! \n");
            return 0;
        }
        
    }
    board[i][j] = 0;
    int kills = 1;
    
    //main recursive loop
    kills += neurogun(board, size_i, size_j,i - 1,j,target_type, 0);
    kills += neurogun(board, size_i, size_j, i + 1, j, target_type, 0);
    kills += neurogun(board, size_i, size_j, i, j - 1, target_type, 0);
    kills += neurogun(board, size_i, size_j, i, j + 1, target_type, 0);

    return kills;


}



