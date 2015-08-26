#include "ScoreData.h"
#include "AIE.h"
#include "Decl.h"
#include <cstring>
#include <sstream>
#include <iostream>


sqlite3* ScoreDatabase::myDatabase = NULL;

// opens database file and creates a table with columns to add and organize scores
void ScoreDatabase::Open(const char *a_filename)
{
	std::cout <<  sqlite3_open(a_filename, &myDatabase) << std::endl;

	const char *sqlStatement = "CREATE TABLE IF NOT EXISTS scores (NAME TEXT, LEVEL INT, KILLS INT);";
	std::cout << sqlite3_exec(myDatabase, sqlStatement, 0, 0, 0) << std::endl;

}

// adds a score to the score table
void ScoreDatabase::AddScore(const char* a_name, int a_lvl, int a_kills)
{
	// Using stringstream
	std::stringstream ss;
	ss << "INSERT INTO scores (NAME, LEVEL, KILLS) VALUES (" << "'" << a_name << "'" << ", " << a_lvl << ", " << a_kills << ");";

	std::cout << ss.str() << std::endl;
	std::cout << sqlite3_exec(myDatabase, ss.str().c_str(), 0, 0, 0) << std::endl;

	m_numScores++;
}

// used in "DrawScores()" to print scores to screen
int PrintScore(void* row, int numArgs, char **data, char **columnName)
{
	int &t = *(int*)row;

	if (t > 10) return 0;

	DrawString(data[0], g_screenW / 7, g_screenH / 1.5 - t * 40);
	DrawString(data[0 + 1], g_screenW / 7 + ((g_screenW / 7) * 2), g_screenH / 1.5 - t * 40);
	DrawString(data[0 + 2], g_screenW / 7 + ((g_screenW / 7) * 4), g_screenH / 1.5 - t * 40);
	t++;

	return 0;
}

// draws the scores to the screen
void ScoreDatabase::DrawScores()
{
	const char *sqlStatement = "SELECT * FROM scores ORDER BY KILLS desc;";
	int row = 0;
	DrawString("Name", g_screenW / 7, g_screenH / 1.28 - row * 40);
	DrawString("Level", g_screenW / 7 + ((g_screenW / 7) * 2), g_screenH / 1.28 - row * 40);
	DrawString("Kills", g_screenW / 7 + ((g_screenW / 7) * 4), g_screenH / 1.28 - row * 40);

	sqlite3_exec(myDatabase, sqlStatement, PrintScore, &row, 0);
}

//closes the score database file
void ScoreDatabase::Close()
{
	sqlite3_close(myDatabase);
}
