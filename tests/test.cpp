//
// Created by euvie on 26.09.2020.
//SALAM
// Copyright 2020 euvie
#include <gtest/gtest.h>
#include <iostream>
#include "Table.hpp"
#include <fstream>
#include <cstring>
#include "json_any.hpp"
#include <vector>

TEST(Example, EmptyTest) {
  EXPECT_TRUE(true);
}

TEST(Table, FromJson){

  std::string test_json = \
R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Petrov Nikita",
      "group": "IU8-31",
      "avg": 33.03,
      "debt": [
        "C++",
        "Linux",
        "Network",
        "SPO"
      ]
    }
  ],
  "_meta": {
    "count": 3
  }
})";

  std::ofstream file_json;//файловый вывод

  file_json.open("file_json1.json");
  file_json << test_json;
  file_json.close();
  Table table = Table::parseFile("file_json1.json");


  std::stringstream str;
  table.print(str);
  std::cout << str.str();
  std::string ref_string =\
R"(| name          | group  | avg   | debt    |
|---------------|--------|-------|---------|
| Ivanov Petr   | 1      | 4.25  | null    |
|---------------|--------|-------|---------|
| Sidorov Ivan  | 31     | 4     | C++     |
|---------------|--------|-------|---------|
| Petrov Nikita | IU8-31 | 33.03 | 4 items |
|---------------|--------|-------|---------|
)";

  EXPECT_EQ(str.str(), ref_string);
}

TEST(Table, Error_name_file) {
  std::string ref_string = "unable to open json: file_jso.json";

  try{
    Table table = Table::parseFile("file_jso.json");
  }
  catch(std::runtime_error& s)
  {
    EXPECT_EQ(s.what(), ref_string);
  }
}

TEST(Table, items) {
  std::string responseString = \
R"({
  "items": {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
  },
  "_meta": {
    "count": 3
  }
})";

  std::ofstream file_json;//файловый вывод

  file_json.open("file_json2.json");
  file_json << responseString;
  file_json.close();
  std::string ref_string = "Items should be array in file_json2.json";

  try{
    Table table = Table::parseFile("file_json2.json");
  }
  catch(std::runtime_error& s)
  {
    EXPECT_EQ(s.what(), ref_string);
  }
}

TEST(Table, _meta) {
  std::string responseString = \
R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    }
  ],
  "_meta": {
    "count": 2
  }
})";
  std::ofstream file_json;//файловый вывод

  file_json.open("file_json3.json");
  file_json << responseString;
  file_json.close();
  std::string ref_string = \
            "Count elements in array items != _meta in file file_json3.json";

  try{
    Table table = Table::parseFile("file_json3.json");
  }
  catch(std::runtime_error& s)
  {
    EXPECT_EQ(s.what(), ref_string);
  }
}

TEST(Json_any, From_json)
{
  std::string responseString = \
    R"(["Hello, MGTU", 22, 4.5, ["IU-1", "IU-2", "IU-3"]])";
  json responseJson = json::parse(responseString);

  std::any object_0;
  responseJson[0].get_to(object_0);
  EXPECT_EQ(std::any_cast<std::string>(object_0), "Hello, MGTU");

  std::any object_1;
  responseJson[1].get_to(object_1);
  EXPECT_EQ(std::any_cast<int>(object_1), 22);

  std::any object_2;
  responseJson[2].get_to(object_2);
  EXPECT_EQ(std::any_cast<double>(object_2), 4.5);

  std::any object_3;
  responseJson[3].get_to(object_3);
  EXPECT_EQ(std::any_cast<std::vector<std::string>>(object_3)[0], "IU-1");
  EXPECT_EQ(std::any_cast<std::vector<std::string>>(object_3)[1], "IU-2");
  EXPECT_EQ(std::any_cast<std::vector<std::string>>(object_3)[2], "IU-3");
}

TEST(Student, name) {
  Student student;

  student.set_name("NIKO");

  std::stringstream str;
  student.print_name(str);
  EXPECT_EQ(str.str(), "NIKO");
}

TEST(Student, group) {
  Student student;
  std::stringstream str;
  student.set_group(std::string("1"));
  student.print_group(str);
  EXPECT_EQ(str.str(), "1");

  student.set_group(31);
  str.str(std::string());
  student.print_group(str);
  EXPECT_EQ(str.str(), "31");

  student.set_group(31.55);
  str.str(std::string());
  student.print_group(str);
  EXPECT_EQ(str.str(), "ERR");
}

TEST(Student, avg) {
  Student student;
  std::stringstream str;

  student.set_avg(std::string("3"));
  student.print_avg(str);
  EXPECT_EQ(str.str(), "3");

  student.set_avg(4);
  str.str(std::string());
  student.print_avg(str);
  EXPECT_EQ(str.str(), "4");

  student.set_avg(4.25);
  str.str(std::string());
  student.print_avg(str);
  EXPECT_EQ(str.str(), "4.25");

  student.set_avg((size_t) 5);
  str.str(std::string());
  student.print_avg(str);
  EXPECT_EQ(str.str(), "ERR");
}

TEST(Student, debt) {
  Student student;
  std::stringstream str;
  student.set_debt(std::string("Assembler"));
  student.print_debt(str);
  EXPECT_EQ(str.str(), "Assembler");

  student.set_debt(nullptr);
  str.str(std::string());
  student.print_debt(str);
  EXPECT_EQ(str.str(), "null");

  student.set_debt((size_t) 5);
  str.str(std::string());
  student.print_debt(str);
  EXPECT_EQ(str.str(), "ERR");

  std::vector <std::string> data = {"C++", "Assembler"};
  student.set_debt(data);
  str.str(std::string());
  student.print_debt(str);
  EXPECT_EQ(str.str(), "2 items");
}

TEST(Student, length_name) {
  Student student;
  student.set_name("NIKO");
  EXPECT_EQ(student.length_name(), (size_t) 4);
}

TEST(Student, length_group) {
  Student student;
  student.set_group(std::string("1"));
  EXPECT_EQ(student.length_group(), (size_t) 1);

  student.set_group(31);
  EXPECT_EQ(student.length_group(), (size_t) 2);

  student.set_group(31.55);
  EXPECT_EQ(student.length_group(), (size_t) 3);
}

TEST(Student, length_avg) {
  Student student;
  student.set_avg(std::string("3.3"));
  EXPECT_EQ(student.length_avg(), (size_t) 3);

  student.set_avg(4);
  EXPECT_EQ(student.length_avg(), (size_t) 1);


  student.set_avg(4.25);
  EXPECT_EQ(student.length_avg(), (size_t) 4);

  student.set_avg((size_t) 5);
  EXPECT_EQ(student.length_avg(), (size_t) 3);
}

TEST(Student, length_debt) {
  Student student;
  student.set_debt(std::string("Assembler"));
  EXPECT_EQ(student.length_debt(), (size_t) 9);

  student.set_debt(nullptr);
  EXPECT_EQ(student.length_debt(), (size_t) 4);

  student.set_debt((size_t) 5);
  EXPECT_EQ(student.length_debt(), (size_t) 3);

  std::vector <std::string> data = {"C++", "Assembler"};
  student.set_debt(data);
  EXPECT_EQ(student.length_debt(), (size_t) 7);
}

TEST(Student, FromJson) {
  json j = json::parse(R"({
  "name": "Ivanov Petr",
  "group": "1",
  "avg": "4.25",
  "debt": null
})");
  Student student;

  Student::from_json(j, student);
  EXPECT_EQ(student.get_name(), std::string("Ivanov Petr"));
  EXPECT_EQ(std::any_cast<std::string>(student.get_group()), "1");
  EXPECT_EQ(std::any_cast<std::string>(student.get_avg()), "4.25");
  EXPECT_EQ(std::any_cast<std::nullptr_t>(student.get_debt()), nullptr);

  j = json::parse(R"({
  "name": "Sidorov Ivan",
  "group": 31,
  "avg": 4,
  "debt": "C++"
})");
  Student::from_json(j, student);
  EXPECT_EQ(student.get_name(), std::string("Sidorov Ivan"));
  EXPECT_EQ(std::any_cast<int>(student.get_group()), 31);
  EXPECT_EQ(std::any_cast<int>(student.get_avg()), 4);
  EXPECT_EQ(std::any_cast<std::string>(student.get_debt()), "C++");

  j = json::parse(R"({
  "name": "Petrov Nikita",
  "group": "IU8-31",
  "avg": 3.33,
  "debt": [
    "C++",
    "Linux",
    "Network"
  ]
})");
  Student::from_json(j, student);
  EXPECT_EQ(student.get_name(), std::string("Petrov Nikita"));
  EXPECT_EQ(std::any_cast<std::string>(student.get_group()), "IU8-31");
  EXPECT_EQ(std::any_cast<double>(student.get_avg()), \
            static_cast<double>(3.33));
  EXPECT_EQ(std::any_cast<std::vector<std::string>> (student.get_debt()),
            std::vector<std::string> ({"C++", "Linux", "Network"}));
}

TEST(Table, Error_item){
  std::string responseString = \
R"({
  "ites": [{
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
}
  ],
  "_meta": {
    "count": 1
  }
})";

  std::ofstream file_json;//файловый вывод

  file_json.open("file_json4.json");
  file_json << responseString;
  file_json.close();
  std::string ref_string = "Items should be in file file_json4.json";

  try{
    Table table = Table::parseFile("file_json4.json");
  }
  catch(std::runtime_error& s)
  {
    EXPECT_EQ(s.what(), ref_string);
  }
}

TEST(Table, Error_meta){
  std::string responseString = \
R"({
  "items": [{
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
  }
  ],
  "_mta": {
    "count": 1
  }
})";

  std::ofstream file_json;//файловый вывод

  file_json.open("file_json5.json");
  file_json << responseString;
  file_json.close();
  std::string ref_string = "_meta should be in file file_json5.json";

  try{
    Table table = Table::parseFile("file_json5.json");
  }
  catch(std::runtime_error& s)
  {
    EXPECT_EQ(s.what(), ref_string);
  }
}