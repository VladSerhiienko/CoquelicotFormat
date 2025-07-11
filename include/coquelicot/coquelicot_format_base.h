// Auto generated by formatgen on Oct 13 2024
#pragma once
#if !defined(CQ_FORMAT_BASE_H_) && !defined(CQ_FORMAT_IMAGEFORMAT_H)
#define CQ_FORMAT_BASE_H_ 1

/* CqFormat is a library about the encodings of pixels typically
 * encountered in real time graphics.
 *
 * Like modern graphics API it is enumeration based but it also provides an API
 * for reasoning about that enumeration programmatically.
 *
 * Additionally it provide ways of accessing pixels encoded in the specified
 * format for most pixel formats. The hope is eventually to get decode to 100%
 * but not there yet (119 out of 193 currently).
 * This allows you to effectively read/write a large amount of image data.
 *
 * To assist with working with graphics APIs converters to and from Vulkan,
 * D3D12 and Metal. These are self contained and do not require the actual APIs.
 *
 * Available as either a single header or a version made of 6 headers split into
 * functional groups. Use one style or the other but they don't mix.
 *
 * These files are large due to unrolling and large switches. Functions are
 * inlined, allowing the compiler to eliminate and collapse when possible,
 * however particularly the Encode/Decode functions aren't near as fast as they
 * could be if heavily optimised for specific formats/layouts.
 *
 * Whilst not optimal due to number of formats it supports, it intends to be
 * fast enough that in many cases it will be fine.
 *
 * Internally every format has a descriptor packed into a 64 bit code word.
 * This code word is used to generate the header and it isn't used by the API
 * itself, as its been 'burnt' out by the code generator but it can be used at
 * runtime if desired and in future its intended to be used for exotic packed
 * formats that don't get there own enumeration value but can be expressed
 * via a descriptor.
 *
 * Where possible for C++ users functions are constexpr.
 *
 * It is MIT licensed and borrows/builds on code/specs including but not
 * limited to
 * Microsoft's Chris Walbourn DXTextureTool
 * Rygerous public domain Half to float (and vice versa) code
 * Khronos DFD specifications
 * Khronos Vulkan Specification
 * Microsoft D3D11/D3D12 Specifications
 * Apple Metal documentation
 * DDS Loaders from various sources (Humus, Confetti FX, DXTextureTool)
 *
 * TODO
 * ----
 * Test CLUT formats and add encode clause
 * Add shared component i.e. G8R8G8B8 4:2:x formats
 * Add Multi plane formats
 * Add compressed format decoders
 * Add Block copy (for updating compressed formats)
 * Add functions that work on descriptor codes directly
 * Add UFLOAT 6 and 7 bit support
 * Optional SIMD decode/encode functions
 * More tests
 *
 * Definitions
 * -----------
 *
 * Pixel
 * We define a pixel as upto 4 channels representing a single 'colour'
 * Its may not be addressable directly but as blocks of related pixels.
 * When decode/encoding pixels are presented to the API as 4 floats or doubles.
 *
 * Logical Channels (CqFormat_LogicalChannel)
 * Logical channel are the usual way you would ask for a particular channel,
 * so asking about LC_Red while get you data for the red channel, however its
 * actually physically encoded in the data.
 *
 * Physical Channels (CqFormat_PhysicalChannel)
 * Physical channels are the inverse of logical channels, that have no meaning
 * beyond the position in the data itself.
 *
 * Both Logical and Physical channels support returning constant 0 or 1
 *
 * Blocks
 * A block is the smallest addressable element this format refers to. Blocks
 * have up to 3 dimensions (though no format currently uses the 3rd).
 * Blocks are always at least byte aligned.
 * For single pixel formats this will be 1x1x1. For something like R1 it would
 * be 8x1x1 (8 single bits for 8 pixels).
 * For block compressed format a common value is 4x4x1.
 * A block for shared channels or very tightly packed this is how many pixels
 * are combined into one addressable unit.
 *
 * API
 * ---
 * The primary enumeration is simply CqFormat, everything else supports
 * this enum.
 * All functions, enums etc. are prefixed with CqFormat_, All functions
 * also take the format as first parameter. These are often removed in the api
 * docs to save space.
 *
 * Defines
 * -------
 * CqFormat_Count - how many formats in total
 * CqFormat_MaxPixelCountOfBlock - maximum number of pixels in a block
 * 									- for any format (for static decode buffer allocation)
 *
 * Enums
 * -----
 * CqFormat - Count entries, one for each format supported
 * LogicalChannel - values for logical channel or constants
 * 						- LC_Red - Red channel is specified
 * 						- LC_Green - Green channel is specified
 * 						- LC_Blue - Blue channel is specified
 * 						- LC_Alpha - Alpha channel is specified
 * 						- LC_Depth - Depth channel is specified
 * 						- LC_Stencil - Stencil channel is specified
 * 						- LC_1 - constant 1 will be returned
 * 						- LC_0 - constant 0 will be return
 * PhysicalChannel - values for physical channel or constants
 * 						- PC_0 - Leftmost channel
 * 						- PC_1 - 2nd channel
 * 						- PC_2 - 3rd channel
 * 						- PC_3 - 4th channel
 * 						- PC_CONST_1 - constant 1 will be returned
 * 						- PC_CONST_0 - constant 0 will be return
 *
 * Structs
 * -------
 * CqFormat_DecodeInput
 *   - pixel or pixelPlane0 - pixel data ptr or pixel data ptr for plane 0
 *   - lut or pixelPlane1 - Look Up Table ptr for CLUT formats or pixel plane 1
 *	 - pixelPlane2 to pixelPlane 9 - 7 more planes ptrs
 * CqFormat_EncodeOutput
 *   - pixel or pixelPlane0 - pixel data ptr or pixel data ptr for plane 0
 *	 - pixelPlane2 to pixelPlane 9 - 8 more planes ptrs

 * Query Functions
 * -----------
 * Code - uint64_t with the internal descriptor code
 * Name  - Human C string with the name of this fmt
 * FromName - lookup the format given the name as a C String (fast)
 * IsDepthOnly - true if just a depth channel
 * IsStencilOnly - true if just a stencil channel
 * IsDepthAndStencil - if has both depth and stencil channel
 * IsCompressed - true if its a compressed format (aka block)
 * IsCLUT - true if data is index into a CLUT (Colour Look Up Table)
 * IsFloat - is the data in floating point
 * IsNormalised - return true if data will be within 0 to 1 or -1 to 1
 * IsSigned - does the data include negatives
 * IsSRGB - is the data encoded using sRGB non linear encoding
 * IsHomogenous - is the encoding the same for every channel
 * WidthOfBlock - How many pixels in the x dimension for a block
 * HeightOfBlock - How many pixels in the y dimension for a block
 * DepthOfBlock 	- How many pixels in the z dimension for a block
 * PixelCountOfBlock - How many pixels in total for a block
 * BitSizeOfBlock - How big in bits is a single block.
 * ChannelCount - How many channels are actually encoded
 *
 * Logical Channel Functions
 * -------------------------
 * ChannelBitWidth( logical channel ) - how wide in bits is the channel
 * Min( logical channel ) - minimum possible value for the channel
 * Max(  logical channel ) - maximum possible value for the channel
 * LogicalChannelToPhysical( logical channel )
 * 											- what physical channel is the logical channel stored in
 * 											- or constant 0 or 1 if its not physically stored
 *
 * Pixel Decoder Functions (X = F or D version, use F if possible as its faster)
 * -----------------------
 * CanDecodeLogicalPixelsX - Can DecodeLogicalPixelsX work with this format?
 * DecodeLogicalPixelsX( width in blocks, FetchInput, out pixels)
 * 		 - pixels should be a pointer to 4 * PixelCounfOfBlack float/doubles
 * 		 - does full decode and remapping into logical channels include constants.
 *     - Returned result can be used directly as RGBA floating point data
 *     - Input pointers are updated are used, so can be passed back in for
 *     - next set of pixel decoding if desired.
 *     - For CLUT formats in.pixel should be the packed pixel data and in.lut is
 *		 - the lookuptable in R8G8B8A8 format of 2^Pbits entries
 *     - For all others in.pixel should be the packed pixel data
 * Pixel Decoder Helper Functions
 * -----------------------
 * UFloat6AsUintToFloat - returns the value stored as a 6 bit UFloat
 * UFloat7AsUintToFloat - returns the value stored as a 7 bit UFloat
 * UFloat10AsUintToFloat - returns the value stored as a 10 bit UFloat
 * UFloat11AsUintToFloat - returns the value stored as a 11 bit UFloat
 * SharedE5B9G9R9UFloatToFloats - return the pixel stored in shared
 * 															- shared 5 bit exponent,  9 bit mantissa for RGB
 * HalfAsUintToFloat - returns the value stored as a 16 bit SFloat
 * BFloatAsUintToFloat - returns the value stored as a 16 bit BFloat
 * LookupSRGB - returns the value for an 8 bit sRGB encoded value
 *
 * Pixel Encoder Functions (X = F or D version, use F if possible as its faster)
 * -----------------------
 * CanEncodeLogicalPixelsX - Can EncodeLogicalPixelsX work with this format?
 * EncodeLogicalPixelsX( width in blocks, in pixels, PutOutput)
 * 		 - pixels should be a pointer to 4 * PixelCounfOfBlack float/doubles
 * 		 - does full encode and remapping into logical channels
 *     - Output pointers are updated are used, so can be passed back in for
 *     - next set of pixel encoding if desired.
 *     - out.pixel is where colour information should be stored
 *
 * Pixel Encoder Helper Functions
 * -----------------------
 * FloatToUFloat6AsUint - Encodes float into  a 6 bit UFloat
 * FloatToUFloat7AsUint - Encodes float into  a 7 bit UFloat
 * FloatToUFloat10AsUint - Encodes float into a 10 bit UFloat
 * FloatToUFloat11AsUint - Encodes float into  11 bit UFloat
 * FloatRGBToRGB9E5AsUint32 - Encodes a float RGB into RGB9E5
 * FloatToHalfAsUint - Encodes a float into a 16 bit SFloat
 * FloatToBFloatAsUint -  Encodes a float into a 16 bit BFloat
 * FloatToSRGB - encodes a float to sRGB assuming input is 0-1
 *
 * Physical Channel Functions (in general use the Logical Channels)
 * ------------------
 * ChannelBitWidthAtPhysical( phys channel ) - how wide in bits for this channel
 * MinAtPhysical( phys channel ) - min possible value for this channel
 * MaxAtPhysical( phys channel ) - max possible value for this channel
 * PhysicalChannelToLogical(phys channel)
 * 											- what logical channel does a physical channel map to.
 * 											- Or a constant 0 or 1
 *
 * Graphics API Functions
 * ------------------
 * FromVkFormat( VkFormat ) - converts from or UNDEFINED if not possible
 * ToVkFormat - converts to or VK_FORMAT_UNDEFINED if not possible
 * FromDXGI_FORMAT( DXGI_FORMAT) converts from or UNDEFINED if not possible
 * ToDXGI_FORMAT - converts to or DXGI_FORMAT_UNKNOWN if not possible
 * DXGI_FORMATToTypeless - returns the DXGI typeless format if possible
 * FromMetal( MTLPixelFormat ) - converts from or UNDEFINED if not possible
 * ToMetal - converts to or MTLPixelFormatInvalid if not possible
 *
 *
 */
typedef enum CqFormat {
	CqFormat_UNDEFINED = 0,
	CqFormat_R1_UNORM = 1,
	CqFormat_R2_UNORM = 2,
	CqFormat_R4_UNORM = 3,
	CqFormat_R4G4_UNORM = 4,
	CqFormat_G4R4_UNORM = 5,
	CqFormat_A8_UNORM = 6,
	CqFormat_R8_UNORM = 7,
	CqFormat_R8_SNORM = 8,
	CqFormat_R8_UINT = 9,
	CqFormat_R8_SINT = 10,
	CqFormat_R8_SRGB = 11,
	CqFormat_B2G3R3_UNORM = 12,
	CqFormat_R4G4B4A4_UNORM = 13,
	CqFormat_R4G4B4X4_UNORM = 14,
	CqFormat_B4G4R4A4_UNORM = 15,
	CqFormat_B4G4R4X4_UNORM = 16,
	CqFormat_A4R4G4B4_UNORM = 17,
	CqFormat_X4R4G4B4_UNORM = 18,
	CqFormat_A4B4G4R4_UNORM = 19,
	CqFormat_X4B4G4R4_UNORM = 20,
	CqFormat_R5G6B5_UNORM = 21,
	CqFormat_B5G6R5_UNORM = 22,
	CqFormat_R5G5B5A1_UNORM = 23,
	CqFormat_B5G5R5A1_UNORM = 24,
	CqFormat_A1B5G5R5_UNORM = 25,
	CqFormat_A1R5G5B5_UNORM = 26,
	CqFormat_R5G5B5X1_UNORM = 27,
	CqFormat_B5G5R5X1_UNORM = 28,
	CqFormat_X1R5G5B5_UNORM = 29,
	CqFormat_X1B5G5R5_UNORM = 30,
	CqFormat_B2G3R3A8_UNORM = 31,
	CqFormat_R8G8_UNORM = 32,
	CqFormat_R8G8_SNORM = 33,
	CqFormat_G8R8_UNORM = 34,
	CqFormat_G8R8_SNORM = 35,
	CqFormat_R8G8_UINT = 36,
	CqFormat_R8G8_SINT = 37,
	CqFormat_R8G8_SRGB = 38,
	CqFormat_R16_UNORM = 39,
	CqFormat_R16_SNORM = 40,
	CqFormat_R16_UINT = 41,
	CqFormat_R16_SINT = 42,
	CqFormat_R16_SFLOAT = 43,
	CqFormat_R16_SBFLOAT = 44,
	CqFormat_R8G8B8_UNORM = 45,
	CqFormat_R8G8B8_SNORM = 46,
	CqFormat_R8G8B8_UINT = 47,
	CqFormat_R8G8B8_SINT = 48,
	CqFormat_R8G8B8_SRGB = 49,
	CqFormat_B8G8R8_UNORM = 50,
	CqFormat_B8G8R8_SNORM = 51,
	CqFormat_B8G8R8_UINT = 52,
	CqFormat_B8G8R8_SINT = 53,
	CqFormat_B8G8R8_SRGB = 54,
	CqFormat_R8G8B8A8_UNORM = 55,
	CqFormat_R8G8B8A8_SNORM = 56,
	CqFormat_R8G8B8A8_UINT = 57,
	CqFormat_R8G8B8A8_SINT = 58,
	CqFormat_R8G8B8A8_SRGB = 59,
	CqFormat_B8G8R8A8_UNORM = 60,
	CqFormat_B8G8R8A8_SNORM = 61,
	CqFormat_B8G8R8A8_UINT = 62,
	CqFormat_B8G8R8A8_SINT = 63,
	CqFormat_B8G8R8A8_SRGB = 64,
	CqFormat_R8G8B8X8_UNORM = 65,
	CqFormat_B8G8R8X8_UNORM = 66,
	CqFormat_R16G16_UNORM = 67,
	CqFormat_G16R16_UNORM = 68,
	CqFormat_R16G16_SNORM = 69,
	CqFormat_G16R16_SNORM = 70,
	CqFormat_R16G16_UINT = 71,
	CqFormat_R16G16_SINT = 72,
	CqFormat_R16G16_SFLOAT = 73,
	CqFormat_R16G16_SBFLOAT = 74,
	CqFormat_R32_UINT = 75,
	CqFormat_R32_SINT = 76,
	CqFormat_R32_SFLOAT = 77,
	CqFormat_A2R10G10B10_UNORM = 78,
	CqFormat_A2R10G10B10_UINT = 79,
	CqFormat_A2R10G10B10_SNORM = 80,
	CqFormat_A2R10G10B10_SINT = 81,
	CqFormat_A2B10G10R10_UNORM = 82,
	CqFormat_A2B10G10R10_UINT = 83,
	CqFormat_A2B10G10R10_SNORM = 84,
	CqFormat_A2B10G10R10_SINT = 85,
	CqFormat_R10G10B10A2_UNORM = 86,
	CqFormat_R10G10B10A2_UINT = 87,
	CqFormat_R10G10B10A2_SNORM = 88,
	CqFormat_R10G10B10A2_SINT = 89,
	CqFormat_B10G10R10A2_UNORM = 90,
	CqFormat_B10G10R10A2_UINT = 91,
	CqFormat_B10G10R10A2_SNORM = 92,
	CqFormat_B10G10R10A2_SINT = 93,
	CqFormat_B10G11R11_UFLOAT = 94,
	CqFormat_E5B9G9R9_UFLOAT = 95,
	CqFormat_R16G16B16_UNORM = 96,
	CqFormat_R16G16B16_SNORM = 97,
	CqFormat_R16G16B16_UINT = 98,
	CqFormat_R16G16B16_SINT = 99,
	CqFormat_R16G16B16_SFLOAT = 100,
	CqFormat_R16G16B16_SBFLOAT = 101,
	CqFormat_R16G16B16A16_UNORM = 102,
	CqFormat_R16G16B16A16_SNORM = 103,
	CqFormat_R16G16B16A16_UINT = 104,
	CqFormat_R16G16B16A16_SINT = 105,
	CqFormat_R16G16B16A16_SFLOAT = 106,
	CqFormat_R16G16B16A16_SBFLOAT = 107,
	CqFormat_R32G32_UINT = 108,
	CqFormat_R32G32_SINT = 109,
	CqFormat_R32G32_SFLOAT = 110,
	CqFormat_R32G32B32_UINT = 111,
	CqFormat_R32G32B32_SINT = 112,
	CqFormat_R32G32B32_SFLOAT = 113,
	CqFormat_R32G32B32A32_UINT = 114,
	CqFormat_R32G32B32A32_SINT = 115,
	CqFormat_R32G32B32A32_SFLOAT = 116,
	CqFormat_R64_UINT = 117,
	CqFormat_R64_SINT = 118,
	CqFormat_R64_SFLOAT = 119,
	CqFormat_R64G64_UINT = 120,
	CqFormat_R64G64_SINT = 121,
	CqFormat_R64G64_SFLOAT = 122,
	CqFormat_R64G64B64_UINT = 123,
	CqFormat_R64G64B64_SINT = 124,
	CqFormat_R64G64B64_SFLOAT = 125,
	CqFormat_R64G64B64A64_UINT = 126,
	CqFormat_R64G64B64A64_SINT = 127,
	CqFormat_R64G64B64A64_SFLOAT = 128,
	CqFormat_D16_UNORM = 129,
	CqFormat_X8_D24_UNORM = 130,
	CqFormat_D32_SFLOAT = 131,
	CqFormat_S8_UINT = 132,
	CqFormat_D16_UNORM_S8_UINT = 133,
	CqFormat_D24_UNORM_S8_UINT = 134,
	CqFormat_D32_SFLOAT_S8_UINT = 135,
	CqFormat_DXBC1_RGB_UNORM = 136,
	CqFormat_DXBC1_RGB_SRGB = 137,
	CqFormat_DXBC1_RGBA_UNORM = 138,
	CqFormat_DXBC1_RGBA_SRGB = 139,
	CqFormat_DXBC2_UNORM = 140,
	CqFormat_DXBC2_SRGB = 141,
	CqFormat_DXBC3_UNORM = 142,
	CqFormat_DXBC3_SRGB = 143,
	CqFormat_DXBC4_UNORM = 144,
	CqFormat_DXBC4_SNORM = 145,
	CqFormat_DXBC5_UNORM = 146,
	CqFormat_DXBC5_SNORM = 147,
	CqFormat_DXBC6H_UFLOAT = 148,
	CqFormat_DXBC6H_SFLOAT = 149,
	CqFormat_DXBC7_UNORM = 150,
	CqFormat_DXBC7_SRGB = 151,
	CqFormat_PVRTC1_2BPP_UNORM = 152,
	CqFormat_PVRTC1_4BPP_UNORM = 153,
	CqFormat_PVRTC2_2BPP_UNORM = 154,
	CqFormat_PVRTC2_4BPP_UNORM = 155,
	CqFormat_PVRTC1_2BPP_SRGB = 156,
	CqFormat_PVRTC1_4BPP_SRGB = 157,
	CqFormat_PVRTC2_2BPP_SRGB = 158,
	CqFormat_PVRTC2_4BPP_SRGB = 159,
	CqFormat_ETC2_R8G8B8_UNORM = 160,
	CqFormat_ETC2_R8G8B8_SRGB = 161,
	CqFormat_ETC2_R8G8B8A1_UNORM = 162,
	CqFormat_ETC2_R8G8B8A1_SRGB = 163,
	CqFormat_ETC2_R8G8B8A8_UNORM = 164,
	CqFormat_ETC2_R8G8B8A8_SRGB = 165,
	CqFormat_ETC2_EAC_R11_UNORM = 166,
	CqFormat_ETC2_EAC_R11_SNORM = 167,
	CqFormat_ETC2_EAC_R11G11_UNORM = 168,
	CqFormat_ETC2_EAC_R11G11_SNORM = 169,
	CqFormat_ASTC_4x4_UNORM = 170,
	CqFormat_ASTC_4x4_SRGB = 171,
	CqFormat_ASTC_5x4_UNORM = 172,
	CqFormat_ASTC_5x4_SRGB = 173,
	CqFormat_ASTC_5x5_UNORM = 174,
	CqFormat_ASTC_5x5_SRGB = 175,
	CqFormat_ASTC_6x5_UNORM = 176,
	CqFormat_ASTC_6x5_SRGB = 177,
	CqFormat_ASTC_6x6_UNORM = 178,
	CqFormat_ASTC_6x6_SRGB = 179,
	CqFormat_ASTC_8x5_UNORM = 180,
	CqFormat_ASTC_8x5_SRGB = 181,
	CqFormat_ASTC_8x6_UNORM = 182,
	CqFormat_ASTC_8x6_SRGB = 183,
	CqFormat_ASTC_8x8_UNORM = 184,
	CqFormat_ASTC_8x8_SRGB = 185,
	CqFormat_ASTC_10x5_UNORM = 186,
	CqFormat_ASTC_10x5_SRGB = 187,
	CqFormat_ASTC_10x6_UNORM = 188,
	CqFormat_ASTC_10x6_SRGB = 189,
	CqFormat_ASTC_10x8_UNORM = 190,
	CqFormat_ASTC_10x8_SRGB = 191,
	CqFormat_ASTC_10x10_UNORM = 192,
	CqFormat_ASTC_10x10_SRGB = 193,
	CqFormat_ASTC_12x10_UNORM = 194,
	CqFormat_ASTC_12x10_SRGB = 195,
	CqFormat_ASTC_12x12_UNORM = 196,
	CqFormat_ASTC_12x12_SRGB = 197,
	CqFormat_CLUT_P4 = 198,
	CqFormat_CLUT_P4A4 = 199,
	CqFormat_CLUT_P8 = 200,
	CqFormat_CLUT_P8A8 = 201,
} CqFormat;

typedef enum CqFormat_LogicalChannel {
	CqFormat_LC_Red = 0,
	CqFormat_LC_Green = 1,
	CqFormat_LC_Blue = 2,
	CqFormat_LC_Alpha = 3,
	CqFormat_LC_Depth = 0,
	CqFormat_LC_Stencil = 1,
	CqFormat_LC_0 = -1,
	CqFormat_LC_1 = -2,
} CqFormat_LogicalChannel;

typedef enum CqFormat_PhysicalChannel {
	CqFormat_PC_0 = 0,
	CqFormat_PC_1 = 1,
	CqFormat_PC_2 = 2,
	CqFormat_PC_3 = 3,
	CqFormat_PC_CONST_0 = -1,
	CqFormat_PC_CONST_1 = -2,
} CqFormat_PhysicalChannel;

#ifdef __cplusplus
namespace coquelicot::fmt {
enum class Format {
	UNDEFINED = 0,
	R1_UNORM = 1,
	R2_UNORM = 2,
	R4_UNORM = 3,
	R4G4_UNORM = 4,
	G4R4_UNORM = 5,
	A8_UNORM = 6,
	R8_UNORM = 7,
	R8_SNORM = 8,
	R8_UINT = 9,
	R8_SINT = 10,
	R8_SRGB = 11,
	B2G3R3_UNORM = 12,
	R4G4B4A4_UNORM = 13,
	R4G4B4X4_UNORM = 14,
	B4G4R4A4_UNORM = 15,
	B4G4R4X4_UNORM = 16,
	A4R4G4B4_UNORM = 17,
	X4R4G4B4_UNORM = 18,
	A4B4G4R4_UNORM = 19,
	X4B4G4R4_UNORM = 20,
	R5G6B5_UNORM = 21,
	B5G6R5_UNORM = 22,
	R5G5B5A1_UNORM = 23,
	B5G5R5A1_UNORM = 24,
	A1B5G5R5_UNORM = 25,
	A1R5G5B5_UNORM = 26,
	R5G5B5X1_UNORM = 27,
	B5G5R5X1_UNORM = 28,
	X1R5G5B5_UNORM = 29,
	X1B5G5R5_UNORM = 30,
	B2G3R3A8_UNORM = 31,
	R8G8_UNORM = 32,
	R8G8_SNORM = 33,
	G8R8_UNORM = 34,
	G8R8_SNORM = 35,
	R8G8_UINT = 36,
	R8G8_SINT = 37,
	R8G8_SRGB = 38,
	R16_UNORM = 39,
	R16_SNORM = 40,
	R16_UINT = 41,
	R16_SINT = 42,
	R16_SFLOAT = 43,
	R16_SBFLOAT = 44,
	R8G8B8_UNORM = 45,
	R8G8B8_SNORM = 46,
	R8G8B8_UINT = 47,
	R8G8B8_SINT = 48,
	R8G8B8_SRGB = 49,
	B8G8R8_UNORM = 50,
	B8G8R8_SNORM = 51,
	B8G8R8_UINT = 52,
	B8G8R8_SINT = 53,
	B8G8R8_SRGB = 54,
	R8G8B8A8_UNORM = 55,
	R8G8B8A8_SNORM = 56,
	R8G8B8A8_UINT = 57,
	R8G8B8A8_SINT = 58,
	R8G8B8A8_SRGB = 59,
	B8G8R8A8_UNORM = 60,
	B8G8R8A8_SNORM = 61,
	B8G8R8A8_UINT = 62,
	B8G8R8A8_SINT = 63,
	B8G8R8A8_SRGB = 64,
	R8G8B8X8_UNORM = 65,
	B8G8R8X8_UNORM = 66,
	R16G16_UNORM = 67,
	G16R16_UNORM = 68,
	R16G16_SNORM = 69,
	G16R16_SNORM = 70,
	R16G16_UINT = 71,
	R16G16_SINT = 72,
	R16G16_SFLOAT = 73,
	R16G16_SBFLOAT = 74,
	R32_UINT = 75,
	R32_SINT = 76,
	R32_SFLOAT = 77,
	A2R10G10B10_UNORM = 78,
	A2R10G10B10_UINT = 79,
	A2R10G10B10_SNORM = 80,
	A2R10G10B10_SINT = 81,
	A2B10G10R10_UNORM = 82,
	A2B10G10R10_UINT = 83,
	A2B10G10R10_SNORM = 84,
	A2B10G10R10_SINT = 85,
	R10G10B10A2_UNORM = 86,
	R10G10B10A2_UINT = 87,
	R10G10B10A2_SNORM = 88,
	R10G10B10A2_SINT = 89,
	B10G10R10A2_UNORM = 90,
	B10G10R10A2_UINT = 91,
	B10G10R10A2_SNORM = 92,
	B10G10R10A2_SINT = 93,
	B10G11R11_UFLOAT = 94,
	E5B9G9R9_UFLOAT = 95,
	R16G16B16_UNORM = 96,
	R16G16B16_SNORM = 97,
	R16G16B16_UINT = 98,
	R16G16B16_SINT = 99,
	R16G16B16_SFLOAT = 100,
	R16G16B16_SBFLOAT = 101,
	R16G16B16A16_UNORM = 102,
	R16G16B16A16_SNORM = 103,
	R16G16B16A16_UINT = 104,
	R16G16B16A16_SINT = 105,
	R16G16B16A16_SFLOAT = 106,
	R16G16B16A16_SBFLOAT = 107,
	R32G32_UINT = 108,
	R32G32_SINT = 109,
	R32G32_SFLOAT = 110,
	R32G32B32_UINT = 111,
	R32G32B32_SINT = 112,
	R32G32B32_SFLOAT = 113,
	R32G32B32A32_UINT = 114,
	R32G32B32A32_SINT = 115,
	R32G32B32A32_SFLOAT = 116,
	R64_UINT = 117,
	R64_SINT = 118,
	R64_SFLOAT = 119,
	R64G64_UINT = 120,
	R64G64_SINT = 121,
	R64G64_SFLOAT = 122,
	R64G64B64_UINT = 123,
	R64G64B64_SINT = 124,
	R64G64B64_SFLOAT = 125,
	R64G64B64A64_UINT = 126,
	R64G64B64A64_SINT = 127,
	R64G64B64A64_SFLOAT = 128,
	D16_UNORM = 129,
	X8_D24_UNORM = 130,
	D32_SFLOAT = 131,
	S8_UINT = 132,
	D16_UNORM_S8_UINT = 133,
	D24_UNORM_S8_UINT = 134,
	D32_SFLOAT_S8_UINT = 135,
	DXBC1_RGB_UNORM = 136,
	DXBC1_RGB_SRGB = 137,
	DXBC1_RGBA_UNORM = 138,
	DXBC1_RGBA_SRGB = 139,
	DXBC2_UNORM = 140,
	DXBC2_SRGB = 141,
	DXBC3_UNORM = 142,
	DXBC3_SRGB = 143,
	DXBC4_UNORM = 144,
	DXBC4_SNORM = 145,
	DXBC5_UNORM = 146,
	DXBC5_SNORM = 147,
	DXBC6H_UFLOAT = 148,
	DXBC6H_SFLOAT = 149,
	DXBC7_UNORM = 150,
	DXBC7_SRGB = 151,
	PVRTC1_2BPP_UNORM = 152,
	PVRTC1_4BPP_UNORM = 153,
	PVRTC2_2BPP_UNORM = 154,
	PVRTC2_4BPP_UNORM = 155,
	PVRTC1_2BPP_SRGB = 156,
	PVRTC1_4BPP_SRGB = 157,
	PVRTC2_2BPP_SRGB = 158,
	PVRTC2_4BPP_SRGB = 159,
	ETC2_R8G8B8_UNORM = 160,
	ETC2_R8G8B8_SRGB = 161,
	ETC2_R8G8B8A1_UNORM = 162,
	ETC2_R8G8B8A1_SRGB = 163,
	ETC2_R8G8B8A8_UNORM = 164,
	ETC2_R8G8B8A8_SRGB = 165,
	ETC2_EAC_R11_UNORM = 166,
	ETC2_EAC_R11_SNORM = 167,
	ETC2_EAC_R11G11_UNORM = 168,
	ETC2_EAC_R11G11_SNORM = 169,
	ASTC_4x4_UNORM = 170,
	ASTC_4x4_SRGB = 171,
	ASTC_5x4_UNORM = 172,
	ASTC_5x4_SRGB = 173,
	ASTC_5x5_UNORM = 174,
	ASTC_5x5_SRGB = 175,
	ASTC_6x5_UNORM = 176,
	ASTC_6x5_SRGB = 177,
	ASTC_6x6_UNORM = 178,
	ASTC_6x6_SRGB = 179,
	ASTC_8x5_UNORM = 180,
	ASTC_8x5_SRGB = 181,
	ASTC_8x6_UNORM = 182,
	ASTC_8x6_SRGB = 183,
	ASTC_8x8_UNORM = 184,
	ASTC_8x8_SRGB = 185,
	ASTC_10x5_UNORM = 186,
	ASTC_10x5_SRGB = 187,
	ASTC_10x6_UNORM = 188,
	ASTC_10x6_SRGB = 189,
	ASTC_10x8_UNORM = 190,
	ASTC_10x8_SRGB = 191,
	ASTC_10x10_UNORM = 192,
	ASTC_10x10_SRGB = 193,
	ASTC_12x10_UNORM = 194,
	ASTC_12x10_SRGB = 195,
	ASTC_12x12_UNORM = 196,
	ASTC_12x12_SRGB = 197,
	CLUT_P4 = 198,
	CLUT_P4A4 = 199,
	CLUT_P8 = 200,
	CLUT_P8A8 = 201,
};

enum class LogicalChannel {
	Red = 0,
	Green = 1,
	Blue = 2,
	Alpha = 3,
	Depth = 0,
	Stencil = 1,
	_0 = -1,
	_1 = -2,
};

enum PhysicalChannel {
	_0 = 0,
	_1 = 1,
	_2 = 2,
	_3 = 3,
	CONST_0 = -1,
	CONST_1 = -2,
};

}

#endif

#define CqFormat_Count 202U 

typedef struct CqFormat_DecodeInput {
	union { void const* pixel; void const* pixelPlane0; };
	union { void const* lut; void const* pixelPlane1; };
	void const* pixelPlane2;
	void const* pixelPlane3;
	void const* pixelPlane4;
	void const* pixelPlane5;
	void const* pixelPlane6;
	void const* pixelPlane7;
	void const* pixelPlane8;
	void const* pixelPlane9;
} CqFormat_DecodeInput;

typedef struct CqFormat_EncodeOutput {
	union { void * pixel; void * pixelPlane0; };
	void * pixelPlane1;
	void * pixelPlane2;
	void * pixelPlane3;
	void * pixelPlane4;
	void * pixelPlane5;
	void * pixelPlane6;
	void * pixelPlane7;
	void * pixelPlane8;
	void * pixelPlane9;
} CqFormat_EncodeOutput;

#endif // CQ_FORMAT_BASE_H_

