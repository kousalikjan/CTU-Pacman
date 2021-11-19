//
// @author Jan Kousalík <kousaja1@fit.cvut.cz>
// @date  28.05.2021.
//



#include "CConfig.h"

#include <fstream>

using namespace std;

CConfig::CConfig(std::string filepath) : m_FilePath(move(filepath)), m_NormalTime(0), m_FrenzyTime(0), m_Difficulty(EDifficulty::EASY), m_Probability(0){}

void CConfig::Initialize()
{
    size_t difficulty = 0;
    char a = '0';
    ifstream input(m_FilePath);
    input.exceptions(ifstream::failbit | ifstream::badbit);
    if(!input.good())
        throw ifstream::failure("Config file is corrupted!");
    input >> m_NormalTime >> m_FrenzyTime >> difficulty >> m_Probability >> a;
    if(m_NormalTime > 50 || m_NormalTime == 0 || m_FrenzyTime > 50 || m_FrenzyTime == 0 ||
        difficulty < 1 || difficulty > 2 || m_Probability > 100 || a != 'a')
        throw ifstream::failure("Config file is corrupted!");
    m_Difficulty = static_cast<EDifficulty>(difficulty);
    input.close();
}

size_t CConfig::GetNormalTime() const
{
    return m_NormalTime;
}

size_t CConfig::GetFrenzyTime() const
{
    return m_FrenzyTime;
}

EDifficulty CConfig::GetDifficulty() const
{
    return m_Difficulty;
}

size_t CConfig::GetProbability() const
{
    return m_Probability;
}








