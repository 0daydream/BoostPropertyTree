#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>


class Settings {
private:
    std::string configFileName;
    boost::property_tree::ptree pt;

public:
    Settings() : configFileName("config.ini") {};
    ~Settings() = default;

    void createConfig() {
        pt.put("audio.volume", 0.75);
        pt.put("audio.mute", false);

        pt.put("video.resolution", "1280x720");
        pt.put("video.fullscreen", false);

        try {
            boost::property_tree::write_ini(configFileName, pt);
            std::cout << "INI file created: " << configFileName << "\n";
        }
        catch (const boost::property_tree::ini_parser_error& e) {
            std::cout << "Failed to create INI file: " << e.what() << "\n";
            return;
        }
    }

    void loadConfig() {
        try {
            boost::property_tree::ini_parser::read_ini(configFileName, pt);
        }
        catch (const boost::property_tree::ptree_error& e) {
            std::cerr << "Error reading INI file: " << e.what() << "\n";
            return;
        }

        float volume = pt.get<float>("audio.volume", 1.0);
        bool mute = pt.get<bool>("audio.mute", false);

        std::string resolution = pt.get<std::string>("video.resolution", "1280x720");
        bool fullScreen = pt.get<bool>("video.fullscreen", false);

        std::cout << "Audio Volume: " << volume << "\n";
        std::cout << "Audio Mute: " << std::boolalpha << mute << "\n";

        std::cout << "Video Resolution: " << resolution << "\n";
        std::cout << "Video Fullscreen: " << std::boolalpha << fullScreen << "\n";
    }

};

int main()
{
    Settings settings;
    settings.createConfig();
    settings.loadConfig();
}