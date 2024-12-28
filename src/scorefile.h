

#include <fstream>
#include <string>

class ScoreFile {
  public: 
  	ScoreFile();
  	void WriteToFile(std::string name, int score, int size ); 
  	void OpenFile();
  	void CloseFile();
  
  private: 
  	std::fstream log_file;
};