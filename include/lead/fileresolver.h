#include <iostream>
#include <filesystem>
#include <lead/common.h>

LEAD_NAMESPACE_BEGIN

class FileResolver {
public:
    FileResolver(std::string scene_filepath) {
        this->m_scene_filepath = scene_filepath;
        this->m_scene_filename = m_scene_filepath.filename();
        this->m_scene_directory = m_scene_filepath.parent_path();
        this->m_output_filename = m_scene_filename.stem().string() + ".exr";
        this->m_output_filepath = m_scene_directory / m_output_filename;
    }

    static std::string getSceneFilepath() {
        return m_scene_filepath.string();
    }

    static std::string getOutputFilepath() {
        return m_output_filepath.string();
    }

private:
    static std::filesystem::path m_scene_filepath;
    static std::filesystem::path m_scene_filename;
    static std::filesystem::path m_scene_directory;
    static std::filesystem::path m_output_filename;
    static std::filesystem::path m_output_filepath;
};

std::filesystem::path FileResolver::m_scene_filepath;
std::filesystem::path FileResolver::m_scene_filename;
std::filesystem::path FileResolver::m_scene_directory;
std::filesystem::path FileResolver::m_output_filename;
std::filesystem::path FileResolver::m_output_filepath;

LEAD_NAMESPACE_END
