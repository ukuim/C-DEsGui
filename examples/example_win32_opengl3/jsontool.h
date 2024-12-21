#pragma once
#include <nlohmann/json.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
using json = nlohmann::json;
class User {
public:
    std::string name;
    int age;
    User() : name(""), age(0) {}
    User(const json& j) : name(j["name"]), age(j["age"]) {}
};
class UserData {
public:
    std::map<std::string, User> userdata;
    UserData(const json& j) {
        if (j.contains("userdata")) {
            for (auto& user : j["userdata"].items()) {
                userdata[user.key()] = User(user.value());
            }
        }
    }
};
void read_json(const std::string& filename, json& j);

void write_json(const std::string& filename, const json& j);
void add_user(json& j, const std::string& username, const std::string& name, int age);
void update_user(json& j, const std::string& username, const std::string& new_name, int new_age);

void delete_user(json& j, const std::string& username);

void query_user(const json& j, const std::string& username);
