/*******************************************************************************************
* Programmer: Marco Arceo                                                                      
* Class: CptS 121, Fall  2017; Lab Section 21                                    
* Programming Assignment: Yahtzee (PA5)                                                    
* Date: October 11th, 2017                                                                         
* Description: Create the game of 'yahtzee'
*******************************************************************************************/

#include "header.h"

// I tried getting a loop to make it start all over but couldnt quite figure it out *Started overthinking it*
// Everything is in working order besides the game reset

int main(void)
{
	// Player 1 Variables
	int player1[5] = { 0 }, player1_scorecard[13] = { 0 }, player1_combo_selected[13] = { 0 };

	// Player 2 Variables
	int player2[5] = { 0 }, player2_scorecard[13] = { 0 }, player2_combo_selected[13] = { 0 };

	// Other Variables
	int values[6] = { 0 }, rounds = 1, option = 0, total_rolls = 0, choice = 0, combo = 0, score1 = 0, score2 = 0;

	bool game = true;
	srand((unsigned int)time(NULL));

	FILE *outfile = NULL;


	// Do while loop in order to bring the menu up when the game ends
	while (game)
	{
		outfile = fopen("Highscore.txt", "w");
		// Introductory Information
		greetings();

		// Set the score to 0 for both players
		score1 = 0;
		score2 = 0;

		// Do while loop for the menu options
		do
		{
			option = determine_option();
			switch (option)
			{
			case 1: rules();
				break;
			case 3: printf("Goodbye!\n");
				game = false;
				return 0;
			}
		} while (option != 2 && option != 3);

		// Pauses the system and clears the screen
		system("pause");
		system("cls");

		// The main game loop which goes up 
		for (; rounds < 2; ++rounds)
		{
			// player 1 loop information
			printf("Player 1, Round %d\n\n", rounds);
			roll_dice(player1, total_rolls); // rolls dice
			total_rolls += 1; // adds to the roll count
			display_dice(player1); // ASCII representation of the dice, inspired by code from one of my python programs
			choice = reroll_or_combination(); // asks for another roll or a combination decision
			// Loop for a new roll
			if (choice == 1)
			{
				do
				{

					new_roll(player1, total_rolls);
					total_rolls += 1;
					choice = reroll_or_combination();
				} while (choice == 1 && total_rolls < 3);
			}
			add_values(player1, values); // Adds the dice numbers together into a values array
			combinations(); // Displays all the possible combinations
			combo = choose_combo(); // Lets the user choose a combination
			combo = validate_combo(player1_combo_selected, combo); // Checks to see if user's choice is valid
			combo_selection(player1, player1_scorecard, values, combo); // Rewards points to the user based on choice
			score(player1_scorecard); // Displays the scoreboard with the users points
			get_bonus(player1_scorecard); // The formula for a bonus
			system("pause");
			system("cls");
			total_rolls = 0; // reset the rolls to 0
			reset_dice_values(player1, values); // Reset other arrays to zero for future rounds

			// player 2 (Same code is used as player 1, use comments on top for referrence)
			printf("Player 2, Round %d\n\n", rounds);
			roll_dice(player2, total_rolls);
			total_rolls += 1;
			display_dice(player2);
			choice = reroll_or_combination();
			if (choice == 1)
			{
				do
				{

					new_roll(player2, total_rolls);
					total_rolls += 1;
					choice = reroll_or_combination();
				} while (choice == 1 && total_rolls < 3);
			}
			add_values(player2, values);
			combinations();
			combo = choose_combo();
			combo = validate_combo(player2_combo_selected, combo);
			combo_selection(player2, player2_scorecard, values, combo);
			score(player2_scorecard);
			get_bonus(player2_scorecard);
			system("pause");
			system("cls");
			total_rolls = 0;
			reset_dice_values(player2, values);
		}
		printf("Player 1:");
		score1 = total_score(player1_scorecard); // Combines the scores for the player
		printf("Player 2:");
		score2 = total_score(player2_scorecard); // Combines the scores for the player

		// Displays who won based on the scores
		if (score1 > score2)
		{
			printf("\nCongrats! Player 1 Won!\n");
		}
		else if (score2 > score1)
		{
			printf("\nCongrats! Player 2 Won!\n");
		}
		else if (score1 == score2)
		{
			printf("\nTied Game!\n");
		}

		// Reset the scorecard for future games
		scorecard_reset(player1_scorecard);
		scorecard_reset(player2_scorecard);
		fclose(outfile);
		system("pause");
		system("cls");
	}
	return 0;
}