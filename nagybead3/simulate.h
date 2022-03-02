#pragma once
#include <string>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <time.h>
#include "taj.h"


//Ha eltavolitod a kommenteket a random meghívásnál és az ifeknél, illetve az ifek alatt lévõ ifeket kikommenteled, random számmal lehet futtatni
//ahogy kéri a feladat. Viszont tesztelés miatt fix számmal van.
void simulates(Puszta *p, int &vizmennyiseg, int &para, std::vector<Taj*> &tajak, int n)
{
    //srand (time(NULL));
    //static int random = rand() % 101;
    int num = 29;
    if (para < 40)
    {
        if (vizmennyiseg - 3 > 0)
        {
            vizmennyiseg -= 3;
        }
    }
    if (para > 70)
    {
        vizmennyiseg += 5;
        para = 30;
    }
    if (40 < para && para < 70)
    {
        //if( random < (para - 40)*3.3 ){
        if (num < (para - 40) * 3.3)
        {
            vizmennyiseg += 5;
        }
        else
        {
            vizmennyiseg += 1;
        }
    }
    if ((para + 3) < 100)
    {
        para += 3;
    }
    if (vizmennyiseg > 15)
    {
        tajak[n] = p->improve();
    }
}
void simulates(Zold *z, int &vizmennyiseg, int &para, std::vector<Taj*> &tajak, int n)
{
    //srand (time(NULL));
    //static int random = rand() % 101;
    int num = 29;
    if (para < 40)
    {
        if (vizmennyiseg - 6 > 0)
        {
            vizmennyiseg -= 6;
        }
    }
    if (para > 70)
    {
        vizmennyiseg += 10;
        para = 30;
    }
    if (40 < para && para < 70)
    {
        //if( random < (para - 40)*3.3 ){
        if (num < (para - 40) * 3.3)
        {
            vizmennyiseg += 10;
        }
        else
        {
            vizmennyiseg += 2;
        }
    }
    if ((para + 7) < 100)
    {
        para += 7;
    }
    if (vizmennyiseg > 50)
    {
        tajak[n] = z->improve();
    }

    if (vizmennyiseg < 16)
    {
        tajak[n] = z->scaledown();
    }
}
void simulates(Tavas *t, int &vizmennyiseg, int &para, std::vector<Taj*> &tajak, int n)
{
    //srand (time(NULL));
    //static int random = rand() % 101;
    int num = 29;
    if (para < 40)
    {
        if (vizmennyiseg - 10 > 0)
        {
            vizmennyiseg -= 10;
        }
    }
    if (para > 70)
    {
        vizmennyiseg += 15;
        para = 30;
    }
    if (40 < para && para < 70)
    {
        //if( random < (para - 40)*3.3 ){
        if (num < (para - 40) * 3.3)
        {
            vizmennyiseg += 15;
        }
        else
        {
            vizmennyiseg += 3;
        }
    }
    if ((para + 10) < 100)
    {
        para += 10;
    }
    if (vizmennyiseg < 50)
    {
        tajak[n] = t->improve();
    }
}
