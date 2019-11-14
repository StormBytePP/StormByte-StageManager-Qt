#include "File.h"
#include <filesystem>

StageManager::lib::File::File(const std::string& file_path): m_path(file_path) {
    detect_compression();
}

StageManager::lib::File::~File() {

}

#include <iostream>
void StageManager::lib::File::detect_compression() {
    std::filesystem::path p(m_path);
    std::string extension = p.extension();

    if (extension == ".tar" || extension == "") {           m_compression_type = NONE; }
    else if (extension == ".bz2" || extension == ".tbz") {  m_compression_type = BZIP2; }
    else if (extension == ".gz" || extension == ".tgz") {   m_compression_type = GZIP; }
    else if (extension == ".xz" || extension == ".txz") {   m_compression_type = XZ; }
}
