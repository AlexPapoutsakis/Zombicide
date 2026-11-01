#ifndef ZOMBICIDE_H
#define ZOMBICIDE_H

#define MAX 30 


int **create_board( int size_r , int size_c ); 
void print_board ( int **board , int size_r , int size_c , int level , int score , int sound_source);
void sound_mov(int **board, int size_r, int size_c, int sound_source); 
void print_sound_source(int sound_source);
int zombies_dead(int **board ,int size_r , int size_c);
void place_buildings(int **board , int size_r , int size_c);
void place_zombies(int **board , int size_r , int size_c , int z);
char command();
int bomb(int **board, int size_i, int size_j, int target_i, int target_j);
int plasmagun(int **board, int size_i, int size_j, char side, int target);
int neurogun(int **board, int size_i, int size_j , int i ,int j, int target_type, int flag);







#endif