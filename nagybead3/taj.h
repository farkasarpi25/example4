
#pragma once
#include <string>
#include <ostream>
#include <stdlib.h>


class Taj
{
public:
    virtual std::string type() const = 0;
    virtual ~Taj() {}
    virtual Taj* improve() const = 0;
    friend std::ostream &operator<<(std::ostream &os, const Taj &taj);
};


//Puszta class
class Puszta : public Taj
{
public:
  static Puszta* instance();
  std::string type() const override;
  Taj* improve() const override;
  static void destroy();
protected:
  Puszta(){}
private:
  static Puszta* _instance;
};

//Zold class
class Zold : public Taj
{
public:
  static Zold* instance();
  std::string type() const override;
  Taj* improve() const override;
  Taj* scaledown() const;
  static void destroy();
protected:
  Zold() {}
private:
  static Zold* _instance;
};

//Tavas class
class Tavas : public Taj
{
public:
  static Tavas* instance();
  std::string type() const override;
  Taj* improve() const override;
  static void destroy();
protected:
  Tavas() {}
private:
  static Tavas* _instance;
};
