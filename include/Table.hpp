//
// Created by euvie on 27.09.2020.
//
// Copyright 2018 euvie
#ifndef INCLUDE_TABLE_HPP_
#define INCLUDE_TABLE_HPP_

#include <vector>
#include <string>
#include "Student.hpp"

class Table {
 public:
  explicit Table(const json& j);

  ~Table();
  static Table parseFile(const std::string& s);
  //вызов метода без  создания экземпляра класса

  size_t w_name, w_group, w_avg, w_debt, w_space;

  void print(std::ostream& out) const;

  std::vector<Student> m_students;
  std::vector<size_t> m_w;
};
#endif  // INCLUDE_TABLE_HPP_