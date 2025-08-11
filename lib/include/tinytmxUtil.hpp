#ifndef TINYTMX_TINYTMXUTIL_HPP
#define TINYTMX_TINYTMXUTIL_HPP

#include <string>

namespace tinytmx
{
        using XmlParseFunc = std::string(*)(const std::string&);

        XmlParseFunc TinyTMX_GetParseFunc();

        void TinyTMX_SetParseFunc(XmlParseFunc xpf);

        /// Trim both leading and trailing whitespace from a string.
        void Trim(std::string &str);

        /// Decode a base-64 encoded string.
        std::string DecodeBase64(std::string const &str);

        /// Decompress a gzip encoded byte array.
        char* DecompressGZIP(char const *data, uint32_t dataSize, uint32_t expectedSize);

        std::string ParseXMLFileContents(const std::string& path);
}

#endif //TINYTMX_TINYTMXUTIL_HPP

