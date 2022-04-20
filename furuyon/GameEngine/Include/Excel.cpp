#include "Excel.h"
#include <fstream>
#include <iostream>

using namespace std;
CExcel::CExcel()
{
  
}

CExcel::~CExcel()
{
}

void CExcel::Start(int index, int& hero1, std::vector<int>& Normal1, std::vector<int>& Hero1, int& hero2, std::vector<int>& Normal2, std::vector<int>& Hero2, const char* FileName,
	const std::string& PathName)
{
	char	FullPath[MAX_PATH] = {};

	const PathInfo* Info = CPathManager::GetInst()->FindPath(PathName);

	if (Info)
		strcpy_s(FullPath, Info->pPathMultibyte);

	strcat_s(FullPath, FileName);
	string str_buf;
	fstream fs;

	fs.open(FullPath,ios::in);

	while (!fs.eof())
	{
		getline(fs, str_buf, ',');
		if (str_buf == to_string(index))
		{
			getline(fs, str_buf, ',');
			hero1 = stoi(str_buf);
			getline(fs, str_buf, ',');
			while (str_buf != to_string(-1))
			{
				if (stoi(str_buf) > 7)
				{
					Hero1.push_back(stoi(str_buf)-8);
					getline(fs, str_buf, ',');
				}
				else
				{
					Normal1.push_back(stoi(str_buf));
					getline(fs, str_buf, ',');
				}
				
			}
			getline(fs, str_buf, ',');
			hero2 = stoi(str_buf);
			getline(fs, str_buf, ',');
			while (str_buf != "-1")
			{
				if (stoi(str_buf) > 7)
				{
					Hero2.push_back(stoi(str_buf) - 8);
					getline(fs, str_buf, ',');
				}
				else
				{
					Normal2.push_back(stoi(str_buf));
					getline(fs, str_buf, ',');
				}

			}


			break;
		}
		getline(fs, str_buf, '\n');
	}

	fs.close();
}

void CExcel::StageSetting(int index, int& range, int& dust, int& playerlife, int& playerora, int& playermana, int& playerfocus, int& ailife, int& aiora, int& aimana, int& aifocus, const char* FileName, const std::string& PathName)
{

	char	FullPath[MAX_PATH] = {};

	const PathInfo* Info = CPathManager::GetInst()->FindPath(PathName);

	if (Info)
		strcpy_s(FullPath, Info->pPathMultibyte);

	strcat_s(FullPath, FileName);
	string str_buf;
	fstream fs;

	fs.open(FullPath, ios::in);

	while (!fs.eof())
	{
		getline(fs, str_buf, ',');
		if (str_buf == to_string(index))
		{
			getline(fs, str_buf, '\n');
			getline(fs, str_buf, ',');
			if (str_buf == to_string(index))
			{
				
				getline(fs, str_buf, ',');
				range = stoi(str_buf);
				getline(fs, str_buf, ',');
				dust = stoi(str_buf);
				getline(fs, str_buf, ',');
				playerlife = stoi(str_buf);
				getline(fs, str_buf, ',');
				playerora = stoi(str_buf);
				getline(fs, str_buf, ',');
				playermana = stoi(str_buf);
				getline(fs, str_buf, ',');
				playerfocus = stoi(str_buf);
				getline(fs, str_buf, ',');
				ailife = stoi(str_buf);
				getline(fs, str_buf, ',');
				aiora = stoi(str_buf);
				getline(fs, str_buf, ',');
				aimana = stoi(str_buf);
				getline(fs, str_buf, ',');
				aifocus = stoi(str_buf);
			}
			break;
		}
		getline(fs, str_buf, '\n');
	}

	fs.close();
}

bool CExcel::StageClearCheck(int index, const char* FileName, const std::string& PathName)
{

	char	FullPath[MAX_PATH] = {};

	const PathInfo* Info = CPathManager::GetInst()->FindPath(PathName);

	if (Info)
		strcpy_s(FullPath, Info->pPathMultibyte);

	strcat_s(FullPath, FileName);

	string str_buf;
	fstream fs;

	fs.open(FullPath, ios::in);

	while (!fs.eof())
	{
		for (int i = 0; i < index+1; i++)
		{
			getline(fs, str_buf, ',');
		}
		if (str_buf == "1")
		{
			fs.close();
			return true;
		}
		else
		{
			fs.close();
			return false;
		}
			
	}

	fs.close();
	return false;
	
}

int CExcel::StageTurn(int index, const char* FileName, const std::string& PathName)
{
	char	FullPath[MAX_PATH] = {};

	const PathInfo* Info = CPathManager::GetInst()->FindPath(PathName);

	if (Info)
		strcpy_s(FullPath, Info->pPathMultibyte);

	strcat_s(FullPath, FileName);
	string str_buf;
	fstream fs;
	int temp;
	fs.open(FullPath, ios::in);

	while (!fs.eof())
	{
		getline(fs, str_buf, ',');
		if (str_buf == to_string(index))
		{
			getline(fs, str_buf, '\n');
			getline(fs, str_buf, ',');
			if (str_buf == to_string(index))
			{

				getline(fs, str_buf, ',');
			
				getline(fs, str_buf, ',');
			
				getline(fs, str_buf, ',');
			
				getline(fs, str_buf, ',');
			
				getline(fs, str_buf, ',');
			
				getline(fs, str_buf, ',');
			
				getline(fs, str_buf, ',');
			
				getline(fs, str_buf, ',');
			
				getline(fs, str_buf, ',');
			
				getline(fs, str_buf, ',');
				getline(fs, str_buf, ',');

				temp = stoi(str_buf);
			}
			break;
		}
		getline(fs, str_buf, '\n');
	}

	fs.close();

	return temp;
}

bool CExcel::StageClear(int index, const char* FileName, const std::string& PathName)
{

	char	FullPath[MAX_PATH] = {};

	const PathInfo* Info = CPathManager::GetInst()->FindPath(PathName);

	if (Info)
		strcpy_s(FullPath, Info->pPathMultibyte);

	strcat_s(FullPath, FileName);

	string str_buf;
	fstream fs;

	fs.open(FullPath, ios::in | ios::out);

	string first1 = "1";

	fs.seekp(index*2, ios::beg);
	fs.put('1');
	fs.close();
	return true;
}



void CExcel::New()
{
}

void CExcel::Save()
{
}
