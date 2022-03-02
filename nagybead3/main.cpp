#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <time.h>
#include <string>
#include "taj.h"
#include "simulate.h"

using namespace std;

void create(const string &filename, vector<Taj*> &tajak, vector<int> &vizek, int &para)
{
    ifstream f(filename);
    if(f.fail())
    {
        cout << "Wrong file name!\n";
        exit(1);
    }
    unsigned int n;
    f >> n;
    tajak.resize(n);
    vizek.resize(n);
    for( unsigned int i = 0; i < n; ++i )
    {
        char type;
        string name;
        int water;
        f >> name >> type >> water;
        if (water > 0)
        {
            switch(type)
            {
                case 'p' :
                    tajak[i] = Puszta::instance();
                    vizek[i] = water;
                    break;
                case 'z' :
                    tajak[i] = Zold::instance();
                    vizek[i] = water;
                    break;
                case 't' :
                    tajak[i] = Tavas::instance();
                    vizek[i] = water;
                    break;
            }
        }
    }
    f >> para;
}

void simulate_whole(vector<Taj*> &tajak, vector<int> &vizek, int &para)
{
    for(int i = 0; i < tajak.size(); i++)
    {
        if(tajak[i]->type() == "Puszta"){
            simulates((Puszta *)tajak[i], vizek[i], para, tajak, i);
        }
        else if (tajak[i]->type() == "Zold"){
            simulates((Zold *)tajak[i], vizek[i], para, tajak, i);
        }
        else{
            simulates((Tavas *)tajak[i], vizek[i], para, tajak, i);
        }
    }
}

bool allequal(vector<Taj*> &tajak)
{
    bool igaze = true;
    for(int i = 1; i < tajak.size(); i++)
    {
        if(tajak.at(i)->type() != tajak.at(0)->type()){
            igaze = false;
        }
    }
    return igaze;
}

void test_run(vector<Taj*> &tajak, vector<int> &vizek, int &para)
{
    for(int k = 1; allequal(tajak) == false; k++ )
    {
        simulate_whole(tajak, vizek, para);
    }
}

bool isempty(const string &filename)
{
    ifstream f(filename);
    if(f.fail())
    {
        cout << "Wrong file name!\n";
        exit(1);
    }
    return f.peek() == ifstream::traits_type::eof();
}

template <typename Item>
void deleteVector(vector<Item*> &tajak)
{
    for(int i = 0; i < tajak.size(); i++)
    {
        delete tajak[i];
    }
}

void deleteTajak()
{
    Puszta::destroy();
    Zold::destroy();
    Tavas::destroy();
}

// Change between manual and test mode
#define NORMAL_MODE
#ifdef NORMAL_MODE

int main()
{
    vector<Taj*> tajak;
    vector<int> vizek;
    int para;
    string file;
    cout << "Kerjuk adjon meg egy filet!" << endl;
    cin >> file;

    create(file, tajak, vizek, para);
    if(isempty(file) == true)
    {
        cout << "Ures filet adott meg!" << endl;
    }else{
        cout << "Tajak szimulacio elott: " << endl;
        cout << "-----------------------------------" << endl;
        for(int i = 0; i < tajak.size(); i++){
            cout << tajak.at(i)->type() << " " << vizek.at(i) << endl;
        }
        cout << "Paratartalom: " << para << endl;
        cout << "-----------------------------------" << endl;
    }
    for(int k = 1; allequal(tajak) == false; k++ )
    {
        simulate_whole(tajak,vizek,para);
        cout << "Tajak a " << k << ". szimulacio utan:" << endl;
        cout << "-----------------------------------" << endl;
        for(int i = 0; i < tajak.size(); i++){
            cout << tajak.at(i)->type() << " " << vizek.at(i) << endl;
        }
        cout << "Paratartalom: " << para << endl;
        cout << "-----------------------------------" << endl;
    }
    deleteVector(tajak);
    deleteTajak();

    return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Ures file 1", "inputures.txt")
{
    string filename = "inputures.txt";
    CHECK(isempty(filename));
}

TEST_CASE("Ures file 2", "inputures2.txt")
{
    string filename = "inputures2.txt";
    CHECK(isempty(filename));
}

TEST_CASE("File 6 tajjal","input2.txt")
{
    string file = "input2.txt";
    vector<Taj*> tajak;
    vector<int> vizek;
    int para;
    SECTION("first simulation")
    {
        create(file,tajak,vizek,para);
        simulate_whole(tajak,vizek,para);
        CHECK_FALSE(allequal(tajak));
        CHECK(tajak[0]->type() == "Puszta");
        CHECK(tajak[3]->type() == "Puszta");
        CHECK(vizek[2] == 6);
    }
    SECTION("whole simulation")
    {
        test_run(tajak,vizek,para);
        CHECK(allequal(tajak));
    }
}

TEST_CASE("File 7 tajjal","input3.txt")
{
    string file = "input3.txt";
    vector<Taj*> tajak;
    vector<int> vizek;
    int para;
    SECTION("first simulation")
    {
        create(file,tajak,vizek,para);
        simulate_whole(tajak,vizek,para);
        CHECK_FALSE(allequal(tajak));
        CHECK(tajak[0]->type() == "Tavas");
        CHECK(tajak[3]->type() == "Puszta");
        CHECK(tajak[6]->type() == "Tavas");
        CHECK(vizek[3] == 15);
        CHECK(vizek[2] == 16);
    }
    SECTION("whole simulation")
    {
        test_run(tajak,vizek,para);
        CHECK(allequal(tajak));
    }
}

TEST_CASE("File 2 tajjal","input4.txt")
{
    string file = "input4.txt";
    vector<Taj*> tajak;
    vector<int> vizek;
    int para;
    SECTION("first simulation")
    {
        create(file,tajak,vizek,para);
        simulate_whole(tajak,vizek,para);
        CHECK_FALSE(allequal(tajak));
        CHECK(tajak[0]->type() == "Zold");
        CHECK(tajak[1]->type() == "Puszta");
        CHECK(vizek[0] == 44);
        CHECK(vizek[1] == 10);
    }
    SECTION("whole simulation")
    {
        test_run(tajak,vizek,para);
        CHECK(allequal(tajak));
    }
}




#endif // NORMAL_MODE
