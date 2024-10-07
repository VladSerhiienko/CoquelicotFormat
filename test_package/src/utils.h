
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdint>
#include <cinttypes>
#include <cmath>
#include <cfloat>

typedef std::FILE* VFile_Handle;

#define ASSERT assert
#define VFile_Write(file, buffer, bufferSize) std::fwrite(buffer, bufferSize, 1, file)
#define VFile_Close(file) std::fclose(file)
#define VFile_FromFile(filePath, mode) std::fopen(filePath, mode)
#define Os_FM_Write "w"
#define LOGERROR(...) printf("[E]" __VA_ARGS__)
#define LOGINFO(...) printf("[I]" __VA_ARGS__)

