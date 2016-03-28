#include "ExeTime.h"



ExeTime::ExeTime(): LastTick(0)
{
	Tick();
}

ExeTime::ExeTime(const ExeTime & Tm): LastTick(Tm.LastTick)
{
}


ExeTime::~ExeTime()
{
}

ExeTime & ExeTime::operator=(const ExeTime & Tm)
{
	LastTick = Tm.LastTick;
	return *this;
}

void ExeTime::Tick()
{
	LastTick = (int)clock();
}

int ExeTime::GetTime() const
{
	return int(clock() - LastTick);
}

double ExeTime::GetSecs() const
{
	return double(clock() - LastTick) / double(CLOCKS_PER_SEC);
}

int ExeTime::GetSecInt()
{
	return (int)floor(GetSecs());
}

const char * ExeTime::GetStr() const
{
	return nullptr;
}

const char * ExeTime::GetTmStr() const
{
	static char TmStr[32];
	if (GetSecs() < 3600)
	{
		sprintf(TmStr, "%.2fs", GetSecs());
	}
	else if (GetSecs() < 3600)
	{
		sprintf(TmStr, "%02dm%02ds", int(GetSecs()) / 60, int(GetSecs()) % 60);
	}
	else
	{
		sprintf(TmStr, "%02dh%02dm", int(GetSecs()) / 3600, (int(GetSecs()) % 3600) / 60);
	}
	return TmStr;
}

