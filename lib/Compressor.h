#ifndef COMPRESSOR_H
#define COMPRESSOR_H

namespace StageManager::lib {
    class Compressor {
        public:
            Compressor();
            enum CompressionType : unsigned short { GZIP, BZIP2, XZ };
    };
}

#endif // COMPRESSOR_H
