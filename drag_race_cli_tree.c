/*
Copyright 2016 Eddie N. <en@sector572.com>

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

Author:		Eddie N. <en@sector572.com>
Date:		2017-01-07
Filename:	drag_race_cli_tree.c
Version:	0.1.0
Description:	This program was written for fun to print and animate an ascii
		drag racing light tree. It reprints itself every 10 seconds.

*/

#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>

#define MIN_ROWS 	16
#define MIN_COLUMNS 	22

void millisleep(long milliseconds);
void sigintHandler(int sig);
void printTree();
void printStageLight(int row, int col, int minCol);
void printLight(int row, int col, int minCol);

int main(int argc, char* argv[])
{
	int rows, columns;
	int row = 0;
	int col = 0;
	int proceed = 1;
	int leftFalseStart = 0;
	int rightFalseStart = 0;
	int cursorRow = 0;
	int cursorCol = 0;
	srand((unsigned) time(NULL));

	initscr();

	while(1 && proceed)
	{

		leftFalseStart = 0;
		rightFalseStart = 0;

		clear();
		getmaxyx(stdscr, rows, columns);

		if(rows >= MIN_ROWS && columns >= MIN_COLUMNS)
		{
			proceed = 1;
		}
		else
		{
			proceed = 0;
			fprintf(stderr, "Sorry in order to run this program, your terminal must be set to at least %d rows and %d columns.\n", MIN_ROWS, MIN_COLUMNS);
		}

		if(proceed)
		{
			/* Set the cursor position after printing tree. */
			cursorRow = rows - 1;
			cursorCol = columns - 1;

			/* Initialize colours. */
			start_color();
			init_pair(1, COLOR_YELLOW, COLOR_BLACK);
			init_pair(2, COLOR_GREEN, COLOR_BLACK);
			init_pair(3, COLOR_RED, COLOR_BLACK);

			mvprintw(cursorRow, 0, "Press CTRL+C to exit.");
			printTree();

			move(cursorRow, cursorCol);

			refresh();
			sleep(1);

			row = 1;

			/* Left side */
			attron(COLOR_PAIR(1));
			printStageLight(row, 3, 1);
			attroff(COLOR_PAIR(1));
			move(cursorRow, cursorCol);
			refresh();
			millisleep(50);

			/* Right side */
			attron(COLOR_PAIR(1));
			printStageLight(row, 10, 8);
			attroff(COLOR_PAIR(1));
			move(cursorRow, cursorCol);
			refresh();
			sleep(1);

			row = 3;

			/* Left side */
			attron(COLOR_PAIR(1));
			printStageLight(row, 3, 1);
			attroff(COLOR_PAIR(1));

			millisleep(50);
			/* Right side */
			attron(COLOR_PAIR(1));
			printStageLight(row, 10, 8);
			attroff(COLOR_PAIR(1));

			move(cursorRow, cursorCol);
			refresh();
			millisleep(500);
			for(row = 4; row < 9; row += 2)
			{
				attron(COLOR_PAIR(1));
				/* Left side */
				printLight(row, 3, 0);

				/* Right side */
				printLight(row, 11, 8);

				attroff(COLOR_PAIR(1));
			}

			move(cursorRow, cursorCol);
			refresh();

			millisleep(100);
			row = 10;
			attron(COLOR_PAIR(2));

			/* Left side */
			printLight(row, 3, 0);

			/* Right side */
			printLight(row, 11, 8);

			attroff(COLOR_PAIR(2));

			move(cursorRow, cursorCol);
			refresh();

			/* Print false start lights. */
			leftFalseStart = rand() % 2;
			rightFalseStart = rand() % 2;

			row = 12;
			attron(COLOR_PAIR(3));

			if(leftFalseStart)
			{
				printLight(row, 3, 0);
			}

			if(rightFalseStart)
			{
				printLight(row, 11, 8);
			}

			attroff(COLOR_PAIR(3));
			move(cursorRow, cursorCol);
			refresh();

			sleep(10);
		}
	}

	endwin();
	return 0;
}

void millisleep(long milliseconds)
{
	struct timespec ts;
	ts.tv_sec = milliseconds / 1000;
	ts.tv_nsec = (milliseconds % 1000) * 1000000;
	nanosleep(&ts, NULL);
}

void sigintHandler(int sig)
{
	signal(sig, SIG_IGN);
	endwin();
}

void printTree()
{
	move(0, 0);
	printw("[ PRE-STAGE ]\n");
	printw("  ** ||| **\n");
	printw("[   STAGE   ]\n");
	printw("  ** ||| **\n");
	printw(" (*)-|||-(*)\n");
	printw("     |||\n");
	printw(" (*)-|||-(*)\n");
	printw("     |||\n");
	printw(" (*)-|||-(*)\n");
	printw("     |||\n");
	printw(" (*)-|||-(*)\n");
	printw("     |||\n");
	printw(" (*)-|||-(*)\n");
	printw("     |||\n");
}

void printStageLight(int row, int col, int minCol)
{
	int i = 0;
	int c = 0;

	for(int i = col; i > minCol; i--)
	{
		mvdelch(row, i);
	}

	for(i = minCol; i < col; i++)
	{
		mvinsch(row, i + 1, '*');
	}
}

void printLight(int row, int col, int minCol)
{
	int i = 0;
	int c = 0;
	char light[3] = { '(', '*', ')' };

	for(c = col; c > minCol; c--)
	{
		mvdelch(row, c);
	}

	for(i = i, c = minCol + 1; i < 3; i++, c++)
	{
		mvinsch(row, c, light[i]);
	}
}
