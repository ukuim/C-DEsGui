#include "jsontool.h"

void read_json(const std::string& filename, json& j) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }
    file >> j;
    file.close();
}

void write_json(const std::string& filename, const json& j) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }
    file << std::setw(4) << j << std::endl; // 使用setw来格式化输出，使其更易于阅读  
    file.close();
}

void add_user(json& j, const std::string& username, const std::string& name, int age) {
    j["userdata"][username]["name"] = name;
    j["userdata"][username]["age"] = age;
}

void update_user(json& j, const std::string& username, const std::string& new_name, int new_age) {
    if (j["userdata"].find(username) != j["userdata"].end()) {
        j["userdata"][username]["name"] = new_name;
        j["userdata"][username]["age"] = new_age;
    }
    else {
        std::cerr << "User " << username << " not found." << std::endl;
    }
}

void delete_user(json& j, const std::string& username) {
    if (j["userdata"].erase(username)) {
        std::cout << "User " << username << " deleted successfully." << std::endl;
    }
    else {
        std::cerr << "User " << username << " not found." << std::endl;
    }
}

void query_user(const json& j, const std::string& username) {
    if (j["userdata"].find(username) != j["userdata"].end()) {
        std::cout << "User " << username << ":" << std::endl;
        std::cout << "  Name: " << j["userdata"][username]["name"] << std::endl;
        std::cout << "  Age: " << j["userdata"][username]["age"] << std::endl;
    }
    else {
        std::cerr << "User " << username << " not found." << std::endl;
    }
}
