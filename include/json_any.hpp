//
// Created by euvie on 26.09.2020.
//
// Copyright 2020 Your Name <euie>
#ifndef INCLUDE_JSON_ANY_HPP_
#define INCLUDE_JSON_ANY_HPP_
#include <nlohmann/json.hpp>
#include <any>
#include <string>
#include <vector>
namespace nlohmann { //пространство имен
template <>
struct adl_serializer<std::any> { //специализация шаблона
  static void from_json(const json& j, std::any& any_var) {
    //Эта функция обычно вызывается get()функцией класса
    // basic_json (либо явным образом, либо с помощью
    // операторов преобразования).
    if (j.is_null()) {
      any_var = nullptr;
    } else if (j.is_number_integer()) {
      any_var = j.get<int>();
    } else if (j.is_number_float()) {
      any_var = j.get<double>();
    } else if (j.is_string()) {
      any_var = j.get<std::string>();
    } else if (j.is_array()) {
      std::vector<std::string> v(0);
      for (json::const_iterator it = j.cbegin(); it != j.cend(); ++it) {
        std::string str = it.value();
        v.push_back(str);
      }
      any_var = v;
    }
  }
};

//cnncnscnzncibs
}// namespace nlohmann
#endif  // INCLUDE_JSON_ANY_HPP_