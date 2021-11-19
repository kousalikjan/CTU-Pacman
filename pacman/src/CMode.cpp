//
// @author Jan Kousalík <kousaja1@fit.cvut.cz>
// @date 28.05.2021.
//

#include "CMode.h"
#include <algorithm>

using namespace std;

CMode::CMode(const CConfig & config, bool frenzy) : m_Difficulty(config.GetDifficulty()), m_Bonus(frenzy)
{
    m_Time = frenzy ? config.GetFrenzyTime() : config.GetNormalTime();
}

size_t CMode::GetTime() const
{
    return m_Time;
}
bool CMode::IsFrenzy() const
{
    return m_Bonus;
}

CMode & CMode::DecTime()
{
    --m_Time;
    return *this;
}

EDifficulty CMode::GetDifficulty() const
{
    return m_Difficulty;
}





