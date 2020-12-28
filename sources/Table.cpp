//
// Created by euvie on 27.09.2020.
//
// Copyright 2020 euvie
#include <iostream>
#include "Table.hpp"
#include <fstream>
Table::Table(const json& j):
    m_students(0), m_w(0){
  w_name = 4;
  w_group = 5;
  w_avg = 3;
  w_debt = 4;
  w_space = 2;

  m_w.push_back(w_name);
  m_w.push_back(w_group);
  m_w.push_back(w_avg);
  m_w.push_back(w_debt);

  for (json::const_iterator i = j.at("items").begin();
    // инициализация полей  классов Student
       i != j.at("items").end(); ++i) {
    Student student;
    Student::from_json(i.value(), student);
    m_students.push_back(student);
  }

  for (size_t i =0; i < m_students.size(); i++)
  {
    m_w[0] = (m_students[i].length_name() > m_w[0])?
             m_students[i].length_name():m_w[0];
    //a,b; y=(a>b)? a:b; a-true, b-false
    m_w[1] = (m_students[i].length_group() > m_w[1])?
             m_students[i].length_group():m_w[1];
    m_w[2] = (m_students[i].length_avg() > m_w[2])?
             m_students[i].length_avg():m_w[2];
    m_w[3] = (m_students[i].length_debt() > m_w[3])?
             m_students[i].length_debt():m_w[3];
  }
  m_w[0]+=w_space;
  m_w[1]+=w_space;
  m_w[2]+=w_space;
  m_w[3]+=w_space;
}


Table Table::parseFile(const std::string& s) {
  std::ifstream file(s); //чтение

  if (!file) {
    throw std::runtime_error("unable to open json: " + s);
  }

  json j;//создание json строки
  file >> j;//записываем содержимое файла в строку

  if (j.find("items") == j.end())
  {
    throw std::runtime_error("Items should be in file " + s);
  }
  if (j.find("_meta") == j.end())
  {
    throw std::runtime_error("_meta should be in file " + s);
  }
  if (!j.at("items").is_array())
  {
    throw std::runtime_error("Items should be array in " + s);
  }
  if (j.at("items").size() != std::any_cast<std::size_t>
      (j.at("_meta").at("count").get<std::size_t>()))
  {
    throw std::runtime_error
        ("Count elements in array items != _meta in file " + s);
  }
  Table table(j);
  return table;
}

std::ostream& operator << (std::ostream &out, Table& obj)
{
  int column = 4;
  out << "| name ";
  for (size_t i = 0; i < obj.m_w[0] - obj.w_name - obj.w_space; i++)
    out << " ";
  out << "| group ";
  for (size_t i = 0; i < obj.m_w[1] - obj.w_group - obj.w_space; i++)
    out << " ";
  out << "| avg ";
  for (size_t i = 0; i < obj.m_w[2] - obj.w_avg - obj.w_space; i++)
    out << " ";
  out << "| debt ";
  for (size_t i = 0; i < obj.m_w[3] - obj.w_debt - obj.w_space; i++)
    out << " ";
  out << "|" << std::endl;
  std::string stick  = "|";
  for (int i = 0; i < column; ++i) {
    for (size_t j = 0; j < obj.m_w[i]; ++j)
      stick += "-";
    stick += "|";
  }
  out << stick << std::endl;

  for (size_t m = 0; m < obj.m_students.size(); m++)
  {
    out << "| ";
    obj.m_students[m].print_name(out);
    for (size_t i = 0;
         i < obj.m_w[0] - obj.m_students[m].length_name() - obj.w_space; i++)
      out << " ";
    out << " | ";

    obj.m_students[m].print_group(out);

    out << " ";
    for (size_t i = 0;
         i < obj.m_w[1] - obj.m_students[m].length_group() - obj.w_space; i++)
      out << " ";
    out << "| ";
    obj.m_students[m].print_avg(out);
    out << " ";
    for (size_t i = 0;
         i < obj.m_w[2] - obj.m_students[m].length_avg() - obj.w_space; i++)
      out << " ";
    out << "| ";
    obj.m_students[m].print_debt(out);
    out << " ";
    for (size_t i = 0;
         i < obj.m_w[3] - obj.m_students[m].length_debt() - obj.w_space; i++)
      out << " ";
    out << "|" << std::endl << stick << std::endl;
  }
  return out;
}

Table::~Table(){
}
