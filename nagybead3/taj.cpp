#include "taj.h"

using namespace std;

std::ostream &operator<<(std::ostream &os, const Taj &taj)
{
  os << taj.type() << " tipusu terulet";
  return os;
}

//Puszta class implement�ci�ja
Puszta* Puszta::_instance = nullptr;
Puszta* Puszta::instance()
{
  if(_instance == nullptr){
    _instance = new Puszta();
  }
  return _instance;
}

void Puszta::destroy()
{
  if( nullptr != _instance)
  {
    delete _instance;
    _instance = nullptr;
  }
}

std::string Puszta::type() const
{
  return "Puszta";
}

Taj* Puszta::improve() const
{
  return Zold::instance();
}

//Zold class implement�ci�ja
Zold* Zold::_instance = nullptr;
Zold* Zold::instance()
{
  if(_instance == nullptr)
  {
    _instance = new Zold();
  }
  return _instance;
}

void Zold::destroy()
{
  if ( nullptr != _instance)
  {
    delete _instance;
    _instance = nullptr;
  }
}

std::string Zold::type() const
{
  return "Zold";
}

Taj* Zold::improve() const
{
  return Tavas::instance();
}

Taj* Zold::scaledown() const
{
    return Puszta::instance();
}

//Tavas class implement�ci�ja
Tavas* Tavas::_instance = nullptr;
Tavas* Tavas::instance()
{
  if(_instance == nullptr)
  {
    _instance = new Tavas();
  }
  return _instance;
}

void Tavas::destroy()
{
  if ( nullptr != _instance)
  {
    delete _instance;
    _instance = nullptr;
  }
}

std::string Tavas::type() const
{
  return "Tavas";
}

Taj* Tavas::improve() const
{
  return Zold::instance();
}
