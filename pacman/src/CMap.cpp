//
// @author Jan Kousalík <kousaja1@fit.cvut.cz>
// @date 10.05.2021.
//

#include "CMap.h"
#include "CObjectCherry.h"
#include "CObjectCanal.h"
#include "CObjectGold.h"
#include "CObjectDiamond.h"
#include "SRandom.h"

#include <istream>
#include <fstream>
#include <algorithm>

using namespace std;
CMap::CMap(string filePath) : m_FilePath(move(filePath)), m_Height(0), m_Width(0), m_Gold(0) {}

bool CMap::IsValid(const CCoord & coord) const
{
    return coord.m_X < m_Width && coord.m_Y < m_Height && coord.m_X > 0 && coord.m_Y > 0;
}

bool CMap::IsWall(const CCoord &coord) const
{
    return m_Walls[coord.m_Y][coord.m_X];
}

void CMap::LoadObject(const CCoord & coord, const CObject & object)
{
    if(!m_Objects.insert({coord, object.Clone()}).second)
        throw ifstream::failure("Map file is corrupted!");
}

size_t CMap::GetHeight() const
{
    return m_Height;
}

size_t CMap::GetWidth() const
{
    return m_Width;
}

void CMap::Initialize()
{
    ifstream input(m_FilePath);
    input.exceptions(ifstream::failbit | ifstream::badbit);
    if(!input.good())
        throw ifstream::failure("Map file is corrupted!");
    input >> m_Height >> m_Width;
    if(m_Height < 5 || m_Width < 5 || m_Height > 50 || m_Width > 50)
        throw ifstream::failure("The map is too small");

    // resize vectors, set all empty
    m_Walls.resize(m_Height);
    for (size_t i = 0; i < m_Height; ++i)
        m_Walls[i].resize(m_Width, false);

    LoadWalls(input);
    ValidWalls();
    LoadCherries(input);
    LoadCanals(input);
    LoadDiamonds(input);
    LoadStartingCoord(input);
    input.close();
    FillWithGold();
}

void CMap::ValidWalls() const
{
    size_t counter = 0;
    CCoord tmp;
    for (size_t i = 1; i < m_Height - 1; ++i)
        for (size_t j = 1; j < m_Width - 1; ++j)
        {
            if(IsWall({i,j}))
                continue;
            counter = 0;
            for (size_t k = 0; k < DIRECTIONS; ++k)
            {
                tmp = CCoord(i,j) + static_cast<EDirection>(k);
                if(IsWall(tmp))
                    counter++;
            }
            if(counter == DIRECTIONS)
                throw ifstream::failure("Too many walls!");
        }
}

void CMap::LoadWalls(ifstream & input)
{
    string line;
    getline(input, line);
    for (size_t i = 0; i < m_Height; ++i)
    {
        getline(input, line);
        if(line.length() != m_Width || line[0] != '#' || line[m_Width-1] != '#')
            throw ifstream::failure("Error while loading map (walls)!");
        for (size_t j = 0; j < m_Width; ++j)
            if(line[j] == '#')
                m_Walls[i][j] = true;
    }
    for (size_t i = 0; i < m_Width; ++i) {
        if (!m_Walls[0][i] || !m_Walls[m_Height - 1][i])
            throw ifstream::failure("Error while loading map (walls)!");
    }
}

void CMap::LoadCherries(ifstream & input)
{
    string line;
    int amount = 0;
    getline(input, line);
    if(line != "BONUS")
        throw ifstream::failure("Error while loading map (cherries)!");
    input >> amount;
    if(amount < 1)
        throw ifstream::failure("Error while loading map (cherries)!");
    for (int i = 0; i < amount; ++i)
    {
        CCoord coord;
        input >> coord.m_Y >> coord.m_X;
        if(!IsValid(coord) || IsWall(coord))
            throw ifstream::failure("Error while loading map (cherries)!");
        LoadObject(coord, CObjectCherry());
    }
}
void CMap::LoadCanals(ifstream & input)
{
    string line;
    getline(input, line);
    getline(input, line);
    if(line != "CANALS")
        throw ifstream::failure("Error while loading map (canals)!");
    CCoord coord1, coord2;
    input >> coord1.m_Y >> coord1.m_X;
    input >> coord2.m_Y >> coord2.m_X;
    if(!IsValid(coord1) || IsWall(coord1)
    || !IsValid(coord2) || IsWall(coord2))
        throw ifstream::failure("Error while loading map (canals)!");
    LoadObject(coord1, CObjectCanal(coord2));
    LoadObject(coord2, CObjectCanal(coord1));
}

void CMap::LoadDiamonds(ifstream & input)
{
    string line;
    int amount = 0;
    getline(input, line);
    getline(input, line);
    if(line != "DIAMONDS")
        throw ifstream::failure("Error while loading map (diamonds)!");
    input >> amount;
    if(amount < 1)
        throw ifstream::failure("Error while loading map (diamonds)!");
    for (int i = 0; i < amount; ++i)
    {
        CCoord coord;
        input >> coord.m_Y >> coord.m_X;
        if(!IsValid(coord) || IsWall(coord))
            throw ifstream::failure("Error while loading map (diamonds)!");
        LoadObject(coord, CObjectDiamond());
        m_Gold+=CObjectDiamond::DIAMOND_VALUE;
    }
}


void CMap::LoadStartingCoord(ifstream & input)
{
    string line;
    getline(input, line);
    getline(input, line);
    if(line != "PLAYERS")
        throw ifstream::failure("Error while loading map (players)!");
    set<CCoord> characterCoords;
    for (size_t i = 0; i < CHARACTERS; ++i)
    {
        CCoord coord;
        input >> coord.m_Y >> coord.m_X;
        if(!IsValid(coord) || IsWall(coord))
            throw ifstream::failure("Error while loading map (players)!");
        if(!characterCoords.insert(coord).second)
            throw ifstream::failure("Error while loading map (players)!");
        m_StartingCoord.insert({static_cast<ECharacter>(i), coord});

    }
    getline(input, line);
    getline(input, line);
    if(line != "KONEC")
        throw ifstream::failure("Error while loading map (players)!");
}

void CMap::FillWithGold()
{
    for (size_t i = 0; i < m_Height; ++i)
        for (size_t j = 0; j < m_Width; ++j)
            if (AddObject(CCoord(i, j), CObjectGold()))
                m_Gold++;
}
bool CMap::AddObject(const CCoord & coord, const CObject & object)
{
    if (!IsValid(coord) || IsWall(coord))
        return false;
    return m_Objects.insert({coord, object.Clone()}).second;
}

CCoord CMap::GetStartingCoords(ECharacter character) const
{
    return m_StartingCoord.at(character);
}

size_t CMap::GetTargetScore() const
{
    return m_Gold;
}

void CMap::InteractObjects(CGameState & state)
{
    auto it = m_Objects.find(state.m_Player->Coord());
    if(it == m_Objects.end())
        return;
    if(it->second->Interact(state))
        m_Objects.erase(it);
}

char CMap::GetObjectValue(const CCoord & coord) const
{
    auto it = m_Objects.find(coord);
    if(it == m_Objects.end())
        return ' ';
    return it->second->Value();
}

void CMap::AddCherry()
{
    CCoord coord = SRandom::RandomCoord(m_Height, m_Width);
    for (int i = 0; i < 10; ++i)
    {
        if(AddObject(coord,CObjectCherry()))
            break;
        coord = SRandom::RandomCoord(m_Height, m_Width);
    }
}



