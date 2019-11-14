#ifndef FILE_H
#define FILE_H

#include <string>

namespace StageManager::lib {
    class File {
        public:
            enum CompressionTypes: unsigned short { NONE, GZIP, BZIP2, XZ };
            File(const std::string& file_path);
            File(const File&);
            File(const File&&);
            File& operator=(const File &);
            ~File();

            inline const std::string& get_path() const { return m_path; }
            inline const CompressionTypes& get_compression_type() const { return m_compression_type; }



        private:
            std::string m_path;
            CompressionTypes m_compression_type;

            void detect_compression();
        };
}

#endif // FILE_H
