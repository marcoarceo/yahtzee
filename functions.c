/*******************************************************************************************
* Programmer: Marco Arceo                                                                      
* Class: CptS 121, Fall  2017; Lab Section 21                                    
* Programming Assignment: Yahtzee (PA5)                                                    
* Date: October 11th, 2017                                                                         
* Description: Create the game of 'yahtzee'
*******************************************************************************************/

#include "header.h"

void greetings() // Welcomes the user to the game
{
	printf("Welcome to YAHTZEE!\n\n");
}

void rules() // Displays the rules of yahtzee
{
	printf("The scorecard used for Yahtzee is composed of two sections. A upper section and a lower section.\nA total of thirteen boxes or thirteen scoring combinations are divided amongst the sections.\nThe upper section consists of boxes that are scored by summing the value of the dice matching the faces of the box.\nIf a player rolls four 3's, then the score placed in the 3's box is the sum of the dice which is 12.\nOnce a player has chosen to score a box, it may not be changed and the combination is no longer in play for future rounds.\nIf the sum of the scores in the upper section is greater than or equal to 63, then 35 more points are added to the players overall score as a bonus.\nThe lower section contains a number of poker like combinations.\n\n");
}

void display_menu() // Displays the menu options
{
	int menu_option = 0;

		printf("1. Display game rules\n");
		printf("2. Play Game\n");
		printf("3. Exit\n");
}

int get_option(void) // Gets the option from the user
{
	int option = 0, status = 0;

	status = scanf("%d", &option);
	if (status == 0)
	{
		printf("Failed at reading in an integer!\n");
	}
	return option;
}

int determine_option(void) // Determines if the option is valid
{
	int option = 0;

	do // input validation loop
	{
		display_menu();
		option = get_option();
		system("cls");
	} while ((option < 1) || (option > 3));

	return option;
}

void roll_dice(int dice[5], int total_rolls) // Rolls the dice and puts values into the array
{
	int index = 0;

	for (; index < 5; ++index)
	{
		dice[index] = rand() % 6 + 1;
	}
}

void display_dice(int dice[5]) // Displays ASCII dice
{
	int index = 0;
	for (; index < 5; ++index)
	{
		// printf("Die%d: %d\n", index + 1, dice[index]);
		switch (dice[index])
		{
		case 1:
			printf("[     ]\n[  o  ]\n[     ]\n\n");
			break;

		case 2:
			printf("[     ]\n[ o o ]\n[     ]\n\n");
			break;

		case 3:
			printf("[  o  ]\n[ o o ]\n[     ]\n\n");
			break;

		case 4:
			printf("[ o o ]\n[     ]\n[ o o ]\n\n");
			break;

		case 5:
			printf("[ o o ]\n[  o  ]\n[ o o ]\n\n");
			break;

		case 6:
			printf("[ o o ]\n[ o o ]\n[ o o ]\n\n");
			break;

		}
	}
}
int reroll_or_combination() // Asks the user if they want to roll again or choose a combination
{
	int choice = 0;
	printf("Would you like to reroll or choose a combination? Reroll = '1', Combination = '-1': ");
	scanf("%d", &choice);
	return choice;
}

int new_roll(int dice[5], int total_rolls) // Creates a new roll based on the user's needs
{
	int num_die = 0, index = 0, rolls = 1;

	do
	{
		printf("\nHow many dice do you want to reroll?\n");
		scanf("%d", &num_die);
	} while((num_die >= 6) && (num_die < 0)); 

	for(int i = 0; i < num_die; i++)
	{
		printf("\nWhich die do you want to change?\n");
		scanf("%d", &index);
		printf("\n");
		dice[index - 1] = rand() % 6 + 1;
	}
	system("cls");
	display_dice(dice, total_rolls);
	return total_rolls += 1;
}

void add_values(int dice[], int values[]) // Adds the values of the dice into another array
{
	// Changed O'fallons code so value index starts at 0, easier for me to understand
	int i = 0;

	for (; i < 5; ++i)
	{
		values[dice[i] - 1]++;
	}
}

void combinations() // Displays the combination options
{
	printf("\n1. Sum of 1's \n");
	printf("2. Sum of 2's \n");
	printf("3. Sum of 3's \n");
	printf("4. Sum of 4's \n");
	printf("5. Sum of 5's \n");
	printf("6. Sum of 6's \n");
	printf("7. Three-of-a-kind \n");
	printf("8. Four-of-a-kind \n");
	printf("9. Full House \n");
	printf("10. Small Straight \n");
	printf("11. Large Straight \n");
	printf("12. Chance \n");
	printf("13. Yahtzee \n\n");
}

int choose_combo() // Gather's the users combination request
{
	int combo = 0;
	printf("Which combination do you want to use?: ");
	scanf(" %d", &combo);
	return combo;
}

int validate_combo(int combo_selected[], int combo) // Validates the users request
{
	bool flag = true;

	while (flag)
	{
		if (combo_selected[combo - 1] == 1)
		{
			printf("Sorry, that combination has already been used, choose a new one: ");
			scanf(" %d", &combo);
		}
		else
		{
			flag = false;
		}
	}
	combo_selected[combo - 1] = 1;
	return combo;
}

void combo_selection(int dice[5], int scorecard[13], int values[6], int combo) // I was given help by multiple TA's on how to do this along with my own style of code
{
	switch (combo)
	{
	case ones: scorecard[0] = values[0];
		break;
	case twos: scorecard[1] = (values[1] * 2);
		break;
	case threes: scorecard[2] = (values[2] * 3);
		break;
	case fours: scorecard[3] = (values[3] * 4);
		break;
	case fives: scorecard[4] = (values[4] * 5);
		break;
	case sixes: scorecard[5] = (values[5] * 6);
		break;
	case three_of_a_kind: 
		if (values[0] >= 3 || values[1] >= 3 || values[2] >= 3 || values[3] >= 3 || values[4] >= 3 || values[5] >= 3)
		{
			scorecard[6] = values[0] + (values[1] * 2) + (values[2] * 3) + (values[3] * 4) + (values[4] * 5) + (values[5] * 6);
		}
		break;
	case four_of_a_kind:
		if (values[0] >= 4 || values[1] >= 4 || values[2] >= 4 || values[3] >= 4 || values[4] >= 4 || values[5] >= 4)
		{
			scorecard[7] = values[0] + (values[1] * 2) + (values[2] * 3) + (values[3] * 4) + (values[4] * 5) + (values[5] * 6);
		}
		break;
	case full_house:
		for (int i = 0; i < 6; i++)
		{
			if (values[i] == 3)
			{
				for (int j = 0; j < 6; j++)
				{
					if (values[j] == 2)
					{
						scorecard[8] = 25;
					}
				}
			}
		}
		break;
	case small_straight:
		if (one_to_four || two_to_five || three_to_six)
		{
			scorecard[9] = 30;
		}
		break;
	case large_straight:
		if (one_to_five || two_to_six)
		{
			scorecard[10] = 40;
		}
		break;
	case chance:
		scorecard[11] = sum;
		break;
	case yahtzee:
		if (big_score)
		{
			scorecard[12] = 50;
		}
		break;
	}
}

void get_bonus(int scorecard[]) // Determines if the user qualifies for a bonus
{
	int bonus = 0;
	
	bonus = scorecard[0] + scorecard[1] + scorecard[2] + scorecard[3] + scorecard[4] + scorecard[5];

	if (bonus >= 63)
	{
		printf("Your combined score for the top half is %d, you have recieved 35 points!\n", bonus);
		scorecard[0] + 35;
	}
	else 
	{
		printf("Your combined score for the top half is %d, you dont qualify for the 35 points!\n", bonus);
	}
}

void score(int scorecard[13]) // Displays the user's scoreboard with results
{
	printf("\nOnes: %d\n", scorecard[0]);
	printf("Twos: %d\n", scorecard[1]);
	printf("Threes: %d\n", scorecard[2]);
	printf("Fours: %d\n", scorecard[3]);
	printf("Fives: %d\n", scorecard[4]);
	printf("Sixes: %d\n", scorecard[5]);
	printf("3 of A Kind: %d\n", scorecard[6]);
	printf("4 of A Kind: %d\n", scorecard[7]);
	printf("Full House: %d\n", scorecard[8]);
	printf("Small Straight: %d\n", scorecard[9]);
	printf("Large Straight: %d\n", scorecard[10]);
	printf("Chance: %d\n", scorecard[11]);
	printf("Yahtzee: %d\n", scorecard[12]);
}

void reset_dice_values(int dice[], int values[]) // Resets the arrays to zero
{
	for (int i = 0; i < 6; i++)
	{
		
		dice[i] = 0;
		values[i] = 0;
	}
}

void scorecard_reset(int scorecard[]) // Resets the array to zero
{
	for (int i = 0; i < 13; i++)
	{
		scorecard[i] = 0;
	}
}

int total_score(int scorecard[]) // Calculates the sum of the scoreboard
{
	int score = 0;
	for (int i = 0; i < 13; i++)
	{
		score += scorecard[i];
	}
	printf("Total Score = %d\n", score);
	return score;
}

// Never got around to finishing this portion of the program
//void highscore_record(FILE *outfile, int score)
//{
//	time_t current_time;
//	char* time_string;
//
//	current_time = time(NULL);
//	time_string = ctime(&current_time);
//
//	fprintf("Date Played: %s", time_string);
//
//}
// Courtesy of 'techcrashcourse.com'