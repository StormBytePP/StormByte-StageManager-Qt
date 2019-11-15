#include "CompressionAction.h"
#include <QProcess>

StageManager::system::CompressionAction::CompressionAction(const std::filesystem::path& file, const std::filesystem::path& folder) {
    m_file = file;
    m_folder = folder;
    m_process = new QProcess();
    connect(m_process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(handleOK()));
}

StageManager::system::CompressionAction::~CompressionAction() {
    delete m_process;
}

StageManager::system::CompressionType StageManager::system::CompressionAction::get_compression_type() const {
    std::string extension = m_file.extension();

    if (extension == ".bz2" || extension == ".tbz") {       return BZIP2; }
    else if (extension == ".gz" || extension == ".tgz") {   return GZIP; }
    else if (extension == ".xz" || extension == ".txz") {   return XZ; }
    else if (extension == ".zstd" || extension == ".tzd") { return ZSTD; }
    else {                                                  return NONE; }
}

const QStringList StageManager::system::CompressionAction::get_tar_command_arguments() const {
    return get_tar_compression_arguments() << "-cpf" << m_file.c_str() << "-C" << m_folder.c_str() << ".";
}

const QStringList StageManager::system::CompressionAction::get_untar_command_arguments() const {
    return get_tar_compression_arguments() << "-xpf" << m_file.c_str() << "-C" << m_folder.c_str();
}

QStringList StageManager::system::CompressionAction::get_tar_compression_arguments() const {
    QStringList commands;
    switch(get_compression_type()) {
        case BZIP2:
            commands << "-I" << "pbzip2 -9";
            break;

        case GZIP:
            commands << "-I" << "pigz -9";
            break;

        case XZ:
            commands << "-I" << "pxz -9eT0";
            break;

        case ZSTD:
            commands << "-I" << "pzstd -9 -q";
            break;

        case NONE:
            break;
    }
    return commands;
}
