#pragma once
#include "sqlite3.h"

// Origin = Mr. Marco

class ScoreDatabase
{
	static sqlite3 *myDatabase;
	ScoreDatabase() { m_numScores = 0; }
public:

	//singleton; returns instance of score object so that 
	//there can be only one and is not created more than once
	static ScoreDatabase &score()
	{
		static ScoreDatabase scoreIns;
		return scoreIns;
	}

	int m_numScores;		// Number of scores

	void Open(const char *a_filename);
	//int PrintScore(void* notUsed, int numArgs, char **data, char **columnName);
	void AddScore(const char* a_name, int a_lvl, int a_kills);
	void DrawScores();
	void Close();
};