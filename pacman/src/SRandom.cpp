//
// @author Jan Kousalík <kousaja1@fit.cvut.cz>
// @date 31.05.2021
//

#include "SRandom.h"
#include <cstdlib>

using namespace std;

void SRandom::Initialize()
{
    srand(0); // NOLINT(cert-msc51-cpp)
}

size_t SRandom::RandomIdx(size_t limit)
{
    return static_cast<size_t>(rand()) % limit; // NOLINT(cert-msc50-cpp)
}

EDirection SRandom::RandomDireciton()
{
    return static_cast<EDirection>(RandomIdx(DIRECTIONS));
}

CCoord SRandom::RandomCoord(size_t height, size_t width)
{
    return {RandomIdx(height), RandomIdx(width)};
}
