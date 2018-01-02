/*******************************************************************************************
* Programmer: Marco Arceo                                                                      
* Class: CptS 121, Fall  2017; Lab Section 21                                    
* Programming Assignment: Yahtzee (PA5)                                                    
* Date: October 11th, 2017                                                                         
* Description: Create the game of 'yahtzee'
*******************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

#define ones 1
#define twos 2
#define threes 3
#define fours 4
#define fives 5
#define sixes 6
#define three_of_a_kind 7
#define four_of_a_kind 8
#define full_house 9
#define small_straight 10
#define large_straight 11
#define chance 12
#define yahtzee 13

// Used for Small Straight
#define one_to_four (values[0] >= 1 && values[1] >= 1 && values[2] >= 1 && values[3] >= 1)
#define two_to_five (values[1] >= 1 && values[2] >= 1 && values[3] >= 1 && values[4] >= 1)
#define three_to_six (values[2] >= 1 && values[3] >= 1 && values[4] >= 1 && values[5] >= 1)

// Used for Large Straight
#define one_to_five (values[0] == 1 && values[1] == 1 && values[2] == 1 && values[3] == 1 && values[4] == 1)
#define two_to_six (values[1] == 1 && values[2] == 1 && values[3] == 1 && values[4] == 1 && values[5] == 1)

// Chance
#define sum values[0] + (values[1] * 2) + (values[2] * 3) + (values[3] * 4) + (values[4] * 5) + (values[5] * 6)

// Yahtzee
#define big_score (values[0] == 5 || values[1] == 5 || values[2] == 5 || values[3] == 5 || values[4] == 5 || values[5] == 5)

void greetings();
void rules();
void display_menu();
int get_option();
int determine_option();
void roll_dice(int dice[5], int total_rolls);
void display_dice(int dice[5]);
int reroll_or_combination();
int choose_combo();
int validate_combo(int combo_selected[], int combo);
int new_roll(int dice[5], int total_rolls);
void add_values(int dice[], int values[]);
void combinations();
void combo_selection(int dice[5], int scorecard[13], int values[6], int combo);
void score(int scorecard[13]);
void get_bonus(int scorecard[]);
void reset_dice_values(int dice[], int values[]);
void scorecard_reset(int scorecard[]);
int total_score(int scorecard[]);
// void highscore_record(FILE *outfile, int score);