#pragma once

#include "GameEngine.h"
#include "Object/Card.h"
#include "Excel.h"
class CClientManager
{
public:
    bool Init();
private:
    int Aiindex;
    int firstHero;
    std::vector<int> m_Normal1;
    std::vector<int> m_Hero1;

    int secondHero;
    std::vector<int> m_Normal2;
    std::vector<int> m_Hero2;
public:
    int GetAiIndex() const
    {
        return Aiindex;
    }
    void SetAiindex(int index)
    {
        Aiindex = index;
    }
    void SetMapIndex()
    {
        CExcel tempexcel;

        tempexcel.Start(Aiindex, firstHero, m_Normal1, m_Hero1, secondHero, m_Normal2, m_Hero2, "mapdata.csv");
    }
    void Clear()
    {
        m_Normal1.clear();
        m_Hero1.clear();
        m_Normal2.clear();
        m_Hero2.clear();
    }
    int Getsecond() const
    {
        return secondHero;
    }
    void Setsecond(int second)
    {
        secondHero = second;
    }
    int Getfirst() const
    {
        return firstHero;
    }
    void Setfirst(int first)
    {
        firstHero = first;
    }

    void SetHero2Card(int card)
    {
        m_Hero2.push_back(card);
    }
    void SetNormal2Card(int card)
    {
        m_Normal2.push_back(card);
    }
    int GetNormal2Card(int index)
    {
        if (m_Normal2.size() <= index)
            return -1;
        return m_Normal2[index];
    }
    int GetHero2Card(int index)
    {
        if (m_Hero2.size() <= index)
            return -1;
        return m_Hero2[index];
    }
    void SetHero1Card(int card)
    {
        m_Hero1.push_back(card);
    }
    void SetNormal1Card(int card)
    {
        m_Normal1.push_back(card);
    }
    int GetNormal1Card(int index)
    {
        if (m_Normal1.size() <= index)
            return -1;
       return m_Normal1[index];
    }
    int GetHero1Card(int index)
    {
        if (m_Hero1.size() <= index)
            return -1;
        return m_Hero1[index];
    }

private:
    void CreateMouse();






    DECLARE_SINGLE(CClientManager)
};

