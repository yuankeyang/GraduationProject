#pragma once
#include <iostream>
#include <ctime>
#include <cmath>
class ExeTime
{
private:
	int LastTick;
public:
	ExeTime();
	ExeTime(const ExeTime& Tm);
	~ExeTime();
	ExeTime& operator=(const ExeTime& Tm);
	void Tick();
	int GetTime() const;
	double GetSecs() const;
	int GetSecInt();
	const char* GetStr() const;
	const char* GetTmStr() const;
};

