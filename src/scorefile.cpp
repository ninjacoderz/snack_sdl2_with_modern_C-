#include "scorefile.h"
#include <iostream>
#include <sstream>

ScoreFile::ScoreFile()
{
    //Open or create the file
    OpenFile();

    //Go the end of the file
    log_file.seekg(0, std::ios::end);

    //Dump the first line
    if (log_file.tellg() == 0)
    {
        log_file << "Player-Score-Size" << std::endl;
    }

    // Close
    CloseFile();
}


void ScoreFile::WriteToFile(std::string name, int score, int size)
{
    OpenFile();

    log_file << "Player name: " << name << ", Player score: " << score << ", Snake size: " << size << std::endl;

    CloseFile();
}

void ScoreFile::OpenFile()
{
    log_file.open("../SCORE_FILE.txt", std::fstream::in | std::fstream::out | std::fstream::app);
}

void ScoreFile::CloseFile()
{
    log_file.close();
}
