#pragma once

#include "GameEngine.h"
#include "PathManager.h"

class CExcel
{

public:
	CExcel();
	~CExcel();

private:


public:
	void Start(int index,int& hero1,std::vector<int>& Normal1,std::vector<int>& Hero1,int& hero2,std::vector<int>& Normal2, std::vector<int>& Hero2, const char* FileName,
		const std::string& PathName = MAP_PATH);
	void StageSetting(int index, int& range,int& dust,int& playerlife,int& playerora,int& playermana,int& playerfocus,int& ailife,int& aiora,int& aimana,int& aifocus, const char* FileName,const std::string& PathName = MAP_PATH);
	bool StageClearCheck(int index, const char* FileName,
		const std::string& PathName = MAP_PATH);
	int StageTurn(int index, const char* FileName,
		const std::string& PathName = MAP_PATH);
	bool StageClear(int index, const char* FileName,
		const std::string& PathName = MAP_PATH);
	void New();
	void Save();

};