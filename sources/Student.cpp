//
// Created by euvie on 26.09.2020.
//
// Copyright 2020 euvie
#include "Student.hpp"
#include <iostream>
#include <cstdlib> // для system
#include <string>

void Student::from_json(const json& j, Student& s) {
  j.at("name").get_to(s.name);
  j.at("group").get_to(s.group);
  j.at("avg").get_to(s.avg);
  j.at("debt").get_to(s.debt);
}

void Student::print_name(std::ostream &out) const//класс не поменяется
{
  out << std::any_cast<std::string>(name);
}

void Student::print_group(std::ostream &out) const
{
  if (group.type() == typeid(int))
    out << std::any_cast<int>(group);
  else if (group.type() == typeid(std::string))
    out << std::any_cast<std::string>(group);
  else
    out << "ERR";
}

void Student::print_avg(std::ostream &out) const
{
  if (avg.type() == typeid(int))
    out << std::any_cast<int>(avg);
  else if (avg.type() == typeid(std::string))
    out << std::any_cast<std::string>(avg);
  else if (avg.type() == typeid(double))
    out << std::any_cast<double>(avg);
  else
    out << "ERR";
}

void Student::print_debt(std::ostream &out) const
{
  if (debt.type() == typeid(std::string))
    out << std::any_cast<std::string>(debt);
  else if (debt.type() == typeid(nullptr))
    out << "null";
  else if (debt.type() == typeid(std::vector <std::string>))
    out << std::any_cast<std::vector<std::string>>(debt).size()
        << " items";
  else
    out << "ERR";
}

size_t Student::length_name() const
{
  return (std::any_cast<std::string>(name).length());
}

size_t Student::length_group() const
{
  if (group.type() == typeid(int))
    return (std::to_string(std::any_cast<int>(group)).length());
  else if (group.type() == typeid(std::string))
    return (std::any_cast<std::string>(group)).length();
  else
    return 3;
}

size_t Student::length_avg() const
{
  if (avg.type() == typeid(int)) {
    return (std::to_string(std::any_cast<int>(avg)).length());
  }else if (avg.type() == typeid(std::string)) {
    return (std::any_cast<std::string>(avg)).length();
  }else if (avg.type() == typeid(double)) {
    double b = std::any_cast<double>(avg);
    int k = static_cast<int>(b);
    int count = 1;
    do {
      count++;
      k/=10;
    } while (k != 0);
    while ((static_cast<int>(b))-b != 0){
      count++;
      b*=10;
    }
    return count;
  }else {
    return 3;
  }
}
size_t Student::length_debt() const
{
  if (debt.type() == typeid(std::string))
    return (std::any_cast<std::string>(debt)).length();
  else if (debt.type() == typeid(nullptr))
    return 4;
  else if (debt.type() == typeid(std::vector <std::string>))
    return (std::to_string \
        ((std::any_cast<std::vector<std::string>>(debt)).size()).length()+6);
  else
    return 3;
}

void Student::set_name(std::string _name)
{
  name = _name;
}
void Student::set_group(std::any _group)
{
  group = _group;
}
void Student::set_avg(std::any _avg)
{
  avg = _avg;
}
void Student::set_debt(std::any _debt)
{
  debt = _debt;
}
std::string Student::get_name() const{
  return name;
}
std::any Student::get_group() const{
  return group;
}
std::any Student::get_avg() const{
  return avg;
}
std::any Student::get_debt() const{
  return debt;
}