#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <cfloat>
#include <cmath>
#include "utils.h"
#include "coquelicot_format_bits.h"
#include "formatgen.h"

void GenEnumClasses(VFile_Handle file) {
    char const cppstart[] = "#ifdef __cplusplus\n";
    char const nsstart[] = "namespace coquelicot {\n";
    char const ifstartmacro[] = "enum class Format {\n";
    char const ifmodmacro[] = "\t%s = %d,\n";
    char const ifendmacro[] = "};\n\n";
    char const nsend[] = "}\n\n";
    char const cppend[] = "#endif\n\n";
    char buffer[2048];

#define CqFormat_START_MACRO                            \
    {                                                          \
        VFile_Write(file, ifstartmacro, strlen(ifstartmacro)); \
        uint32_t count = 0;

#define CqFormat_MOD_MACRO(x, y)       \
    sprintf(buffer, ifmodmacro, #x, count++); \
    VFile_Write(file, buffer, strlen(buffer));

#define CqFormat_END_MACRO                      \
    VFile_Write(file, ifendmacro, strlen(ifendmacro)); \
    }

	VFile_Write(file, cppstart, strlen(cppstart));
	VFile_Write(file, nsstart, strlen(nsstart));

#include "formatgen.h"

    char const logiEnum[] =
        "enum class LogicalChannel {\n"
        "\tRed = 0,\n"
        "\tGreen = 1,\n"
        "\tBlue = 2,\n"
        "\tAlpha = 3,\n"
        "\tDepth = 0,\n"
        "\tStencil = 1,\n"
        "\t_0 = -1,\n"
        "\t_1 = -2,\n"
        "};\n\n";
    VFile_Write(file, logiEnum, strlen(logiEnum));

    char const physEnum[] =
        "enum PhysicalChannel {\n"
        "\t_0 = 0,\n"
        "\t_1 = 1,\n"
        "\t_2 = 2,\n"
        "\t_3 = 3,\n"
        "\tCONST_0 = -1,\n"
        "\tCONST_1 = -2,\n"
        "};\n\n";
    VFile_Write(file, physEnum, strlen(physEnum));

    VFile_Write(file, nsend, strlen(nsend));
	VFile_Write(file, cppend, strlen(cppend));
}

void GenEnums(VFile_Handle file) {
	char const ifstartmacro[] = "typedef enum CqFormat {\n";
	char const ifmodmacro[] = "\tCqFormat_%s = %d,\n";
	char const ifendmacro[] = "} CqFormat;\n\n";

	char buffer[2048];
#define  CqFormat_START_MACRO { VFile_Write(file, ifstartmacro, strlen(ifstartmacro)); uint32_t count = 0;
#define  CqFormat_MOD_MACRO(x, y) sprintf(buffer, ifmodmacro, #x, count++); VFile_Write(file, buffer, strlen(buffer));
#define  CqFormat_END_MACRO VFile_Write(file, ifendmacro, strlen(ifendmacro)); }
#include "formatgen.h"

	char const logiEnum[] =
			"typedef enum CqFormat_LogicalChannel {\n"
			"\tCqFormat_LC_Red = 0,\n"
			"\tCqFormat_LC_Green = 1,\n"
			"\tCqFormat_LC_Blue = 2,\n"
			"\tCqFormat_LC_Alpha = 3,\n"
			"\tCqFormat_LC_Depth = 0,\n"
			"\tCqFormat_LC_Stencil = 1,\n"
			"\tCqFormat_LC_0 = -1,\n"
			"\tCqFormat_LC_1 = -2,\n"
			"} CqFormat_LogicalChannel;\n\n";

	VFile_Write(file, logiEnum, strlen(logiEnum));

	char const physEnum[] =
			"typedef enum CqFormat_PhysicalChannel {\n"
			"\tCqFormat_PC_0 = 0,\n"
			"\tCqFormat_PC_1 = 1,\n"
			"\tCqFormat_PC_2 = 2,\n"
			"\tCqFormat_PC_3 = 3,\n"
			"\tCqFormat_PC_CONST_0 = -1,\n"
			"\tCqFormat_PC_CONST_1 = -2,\n"
			"} CqFormat_PhysicalChannel;\n\n";
	VFile_Write(file, physEnum, strlen(physEnum));

}

void GenStructs(VFile_Handle file) {
	char const fetchInput[] =
			"typedef struct CqFormat_DecodeInput {\n"
			"\tunion { void const* pixel; void const* pixelPlane0; };\n"
			"\tunion { void const* lut; void const* pixelPlane1; };\n"
			"\tvoid const* pixelPlane2;\n"
			"\tvoid const* pixelPlane3;\n"
			"\tvoid const* pixelPlane4;\n"
			"\tvoid const* pixelPlane5;\n"
			"\tvoid const* pixelPlane6;\n"
			"\tvoid const* pixelPlane7;\n"
			"\tvoid const* pixelPlane8;\n"
			"\tvoid const* pixelPlane9;\n"
			"} CqFormat_DecodeInput;\n\n";
	VFile_Write(file, fetchInput, strlen(fetchInput));

	char const putOutput[] =
			"typedef struct CqFormat_EncodeOutput {\n"
			"\tunion { void * pixel; void * pixelPlane0; };\n"
			"\tvoid * pixelPlane1;\n"
			"\tvoid * pixelPlane2;\n"
			"\tvoid * pixelPlane3;\n"
			"\tvoid * pixelPlane4;\n"
			"\tvoid * pixelPlane5;\n"
			"\tvoid * pixelPlane6;\n"
			"\tvoid * pixelPlane7;\n"
			"\tvoid * pixelPlane8;\n"
			"\tvoid * pixelPlane9;\n"
			"} CqFormat_EncodeOutput;\n\n";
	VFile_Write(file, putOutput, strlen(putOutput));

}

void GenCount(VFile_Handle file) {
	char buffer[2048];
	// format count
#define  CqFormat_START_MACRO uint32_t count = 0;
#define  CqFormat_MOD_MACRO(x, y) count++;
#define  CqFormat_END_MACRO
#include "formatgen.h"
	char const formatCountF[] = "#define CqFormat_Count %uU \n\n";

	sprintf(buffer, formatCountF, count);
	VFile_Write(file, buffer, strlen(buffer));
}
