#pragma once
#include <map>
#include <string>
#include <property_tree/ptree.hpp>
#include <property_tree/json_parser.hpp>
#include <property_tree/ptree_fwd.hpp>
class Settings {
public:
    static Settings& Instance() {
        static Settings conf;
        return conf;
    }

    void loadConfig(std::string filePath) {
        boost::property_tree::ptree root;
        boost::property_tree::read_json(filePath, root);

        windowName = root.get<std::string>("windowName");
        windowWidth = root.get<int>("windowWidth");
        windowHeight = root.get<int>("windowHeight");

        tileSetPath = root.get<std::string>("tileSetPath");
        mapPath = root.get<std::string>("mapPath");
        fontPath = root.get<std::string>("fontPath");
        spriteSize = root.get<int>("spriteSize");

        for (boost::property_tree::ptree::value_type& object : root.get_child("objects")) {
            objects.insert(std::pair<std::string, char>(object.first, object.second.data()[0]));
        }
    }

    std::string windowName;
    int windowWidth;
    int windowHeight;

    std::string tileSetPath;
    std::string mapPath;
    std::string fontPath;

    int spriteSize;
    std::map<std::string, char> objects;

private:
    Settings() {}
    ~Settings() {}
    Settings(Settings const&) = delete;
    Settings& operator= (Settings const&) = delete;
};