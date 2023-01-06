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

        gameName = root.get<std::string>("game");
        width = root.get<int>("width");
        height = root.get<int>("height");
        pathForMap = root.get<std::string>("pathForMap");
        sizeOfSprites = root.get<int>("sizeOfSprites");
        pathForTilemap = root.get<std::string>("pathForTilemap");

        for (boost::property_tree::ptree::value_type& object : root.get_child("entities")) {
            entities.insert(std::pair<std::string, char>(object.first, object.second.data()[0]));
        }
    }

    std::string gameName;
    int width;
    int height;
    std::string pathForMap;
    int sizeOfSprites;
    std::string pathForTilemap;
    std::map<std::string, char> entities;

private:
    Settings() {}
    ~Settings() {}
    Settings(Settings const&) = delete;
    Settings& operator= (Settings const&) = delete;
};