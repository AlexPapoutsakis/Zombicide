#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/Zombicide.h"

int main(void) { 
    int **board;
    int size_r , size_c , z ; /* z = number of zombie types chosen by the user */
    int level = 1; 
    int score = 0 , game_end = 0; 
    char cmd = '1'; 


    srand(time(NULL));
       
    
   printf(" give a size for the rows of the board ( more than 3 and less than 30): "); 
     do{ 
         scanf("%d" , &size_r); 
            if ( size_r < 3 || size_r > 30 ){
             printf("Please enter a different size for the rows of the board ( 3-30 ): \n");
          }
       }while ( size_r < 3 || size_r > 30 ); 

  printf(" give a size for the collumns of the board ( more than 3 and less than 30): "); 
     do{ 
         scanf("%d" , &size_c); 
           if ( size_c < 3 || size_c > 30 ){
            printf("Please enter a different size for the columns of the board ( 3-30 ): \n");
       }
       }while ( size_c < 3 || size_c > 30 ); 

    printf(" How many types of zombies do you want on the board ? ( 1-9 ):  ");
      do{
          scanf("%d" , &z);
            if ( z < 1 || z > 9 ){
                printf("Please enter a different number for the type of zombies: \n"); 
            }
      }while ( z < 1 || z > 9 );



 while ( !game_end ){ /* main game loop */

     int sound_source = (int)( (double)rand() / ((double)RAND_MAX + 1 ) *4 ) + 1 ; 

     board =  create_board( size_r , size_c );
     place_buildings ( board , size_r , size_c );
     place_zombies ( board , size_r , size_c , z );
     print_board ( board , size_r , size_c , level , score , sound_source );


        while (!zombies_dead(board , size_r , size_c)) {
            cmd = command(); 

              if(cmd == 'X' || cmd == 'x'){
                game_end = 1; 
                 break; 
                } 

              if(cmd == 'B' || cmd == 'b'){
                 int bomb_i , bomb_j , bomb_kills;
                 
                 do{
                  printf("Enter the coordinates where you want to drop the bomb (for example 3,4 for rows and columns): ");
                    int input = scanf("%d,%d" , &bomb_i , &bomb_j );

                    if ( input != 2 ) { 
                        printf("Please enter different coordinates , wrong format ( for example 3,4 ) \n");
                          while(getchar() != '\n'); /* cleans up the buffer in case the user puts a wrong input */
                           continue;  
                    }
                    else if( bomb_i < 1 || bomb_i > size_r || bomb_j < 1 || bomb_j > size_c ){
                        printf("Please enter different coordinates , out of bounds\n");
                     }
                    
                  }while( bomb_i < 1 || bomb_i > size_r || bomb_j < 1 || bomb_j > size_c );

                 bomb_kills = bomb( board,  size_r,  size_c, bomb_i-1, bomb_j-1);
                 score += level *  (bomb_kills*bomb_kills) * 10;
                 print_board(board , size_r , size_c , level , score , sound_source );


              }


        if(cmd == 'P' || cmd == 'p'){
          int p_target , plasma_kills , p_check=0; /* variable that will handle the loop*/
          char direction;

           do{  /*loop that forces the user to put the right input for the coordinates */ 
            printf("Enter the side and the coordinates where you want to use the plasmagun on the board ( U/u = Up , R/r = right etc...) , for example: L5 ( left side 5th row ) :\n");
              int input2 = scanf(" %c%d", &direction, &p_target);

               if ( input2 != 2 ) {
                   printf("Please enter a different input!\n");
                    while (getchar() != '\n'); 
                     continue;
                    }

              if (direction != 'L' && direction != 'l' && direction != 'R' && direction != 'r' &&
                   direction != 'U' && direction != 'u' && direction != 'D' && direction != 'd') {
                     printf("Not a valid direction, try again!\n");
                      continue;
                   }

              if ((direction == 'L' || direction == 'l' || direction == 'R' || direction == 'r') &&
                     (p_target < 1 || p_target > size_r)) {
                       printf("not a valid row!\n");
                              continue;
                              }

                        if ((direction == 'U' || direction == 'u' || direction == 'D' || direction == 'd') &&
                               (p_target < 1 || p_target > size_c)) {
                                printf("Not a valid column!\n");
                                 continue;
                                  }

                                p_check = 1;

                    }while(!p_check);

                 plasma_kills = plasmagun(board , size_r , size_c , direction , p_target-1);
                 score += level *  (plasma_kills*plasma_kills) * 20;
                 print_board(board , size_r , size_c , level , score , sound_source );
             
                       
              }


        if(cmd == 'n' || cmd == 'N'){
        int n_i, n_j , target_type , n_check = 0 , neur_kills; 

                do{    
                    printf("Enter the coordinates where you want to use the neurogun x,y (for example 3,4 for rows and columns):\n");
                    int input3 = scanf(" %d,%d" , &n_i , &n_j);

                     if( input3 != 2) { 
                         printf("Please enter different coordinates , wrong format ( for example 3,4 ) \n");
                          while(getchar() != '\n'); /* cleans up the buffer in case the user puts a wrong input */
                           continue;  
                     }

                     else if( n_i < 1 || n_i > size_r || n_j < 1 || n_j > size_c ){
                        printf("Please enter different coordinates , out of bounds\n");
                        continue; 

                    } 

                    else if ( board [n_i-1][n_j-1] == -1 ){
                        printf("Thats a building , please pick different coordinates! ( x,y )\n");
                        continue;
                    }

                    else if ( board [n_i-1][n_j-1] == 0 ){
                        printf("There is nothing there , please pick different coordinates! ( x,y)\n");
                        continue;
                    }

                      n_check = 1;


                 }while(!n_check);  

                 target_type = board[n_i -1][n_j -1];

                   neur_kills = neurogun(board , size_r , size_c , n_i-1 , n_j-1 , target_type , 1);
                   score += level *  (neur_kills*neur_kills) * 30;
                   print_board(board , size_r , size_c , level , score , sound_source );
            
            }




            sound_mov(board,size_r, size_c, sound_source); 
            printf("THE ZOMBIES MOVED TOWARDS THE SOUND SOURCE\n\n");
            print_board(board , size_r , size_c , level , score , sound_source );

     
        }

   
     for (int i = 0; i < size_r; i++) {
       free(board[i]);
         }

      free(board); 
         

      size_r++;
      size_c++;

    if(size_r > MAX) {
         game_end = 1;
    }
    if(size_c > MAX) {
         game_end = 1;
    }
    

    level++;


}


    if(game_end){
       if( size_r > MAX || size_c > MAX ){
           printf("YOU WON THE GAME , CONGRATULATIONS !!! .\n You completed %d levels!\n" , level-1);
       }
       else{ 
          printf("Game over! You completed %d levels.\n", level-1);
       }

    printf("Final score: %d\n", score);
    printf("Goodbye!\n");
    }

     return 0;    

    }