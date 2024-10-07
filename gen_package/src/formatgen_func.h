#pragma once

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

constexpr uint64_t  CqFormat_CONSTEXPR_Pack(
		uint64_t rs, uint64_t rb, uint64_t rt,
		uint64_t gs, uint64_t gb, uint64_t gt,
		uint64_t bs, uint64_t bb, uint64_t bt,
		uint64_t as, uint64_t ab, uint64_t at,
		uint64_t special ) {

	static_assert((( CqFormat_PACK_NUM_CHANNELS *  CqFormat_PACK_BITS_REQUIRED_BITS) +  CqFormat_PACK_BITS_SHIFT) == 35);
	static_assert((( CqFormat_PACK_NUM_CHANNELS *  CqFormat_PACK_SWIZZLE_REQUIRED_BITS) +  CqFormat_PACK_SWIZZLE_SHIFT) == 47);
	static_assert((( CqFormat_PACK_NUM_CHANNELS *  CqFormat_PACK_TYPE_REQUIRED_BITS) +  CqFormat_PACK_TYPE_SHIFT) == 63);

	static_assert((( CqFormat_PACK_NUM_CHANNELS *  CqFormat_PACK_TYPE_REQUIRED_BITS) +  CqFormat_PACK_TYPE_SHIFT) < 64);

	uint64_t packed = CqFormat_NAMESPACE_PACK |
			(special <<  CqFormat_PACK_SPECIAL_SHIFT) |
			(rb << (( CqFormat_PC_0 *  CqFormat_PACK_BITS_REQUIRED_BITS) +  CqFormat_PACK_BITS_SHIFT)) |
			(rs << (( CqFormat_PC_0 *  CqFormat_PACK_SWIZZLE_REQUIRED_BITS) +  CqFormat_PACK_SWIZZLE_SHIFT)) |
			(rt << (( CqFormat_PC_0 *  CqFormat_PACK_TYPE_REQUIRED_BITS) +  CqFormat_PACK_TYPE_SHIFT)) |

			(gb << (( CqFormat_PC_1 *  CqFormat_PACK_BITS_REQUIRED_BITS) +  CqFormat_PACK_BITS_SHIFT)) |
			(gs << (( CqFormat_PC_1 *  CqFormat_PACK_SWIZZLE_REQUIRED_BITS) +  CqFormat_PACK_SWIZZLE_SHIFT)) |
			(gt << (( CqFormat_PC_1 *  CqFormat_PACK_TYPE_REQUIRED_BITS) +  CqFormat_PACK_TYPE_SHIFT)) |

			(bb << (( CqFormat_PC_2 *  CqFormat_PACK_BITS_REQUIRED_BITS) +  CqFormat_PACK_BITS_SHIFT)) |
			(bs << (( CqFormat_PC_2 *  CqFormat_PACK_SWIZZLE_REQUIRED_BITS) +  CqFormat_PACK_SWIZZLE_SHIFT)) |
			(bt << (( CqFormat_PC_2 *  CqFormat_PACK_TYPE_REQUIRED_BITS) +  CqFormat_PACK_TYPE_SHIFT)) |

			(ab << (( CqFormat_PC_3 *  CqFormat_PACK_BITS_REQUIRED_BITS) +  CqFormat_PACK_BITS_SHIFT)) |
			(as << (( CqFormat_PC_3 *  CqFormat_PACK_SWIZZLE_REQUIRED_BITS) +  CqFormat_PACK_SWIZZLE_SHIFT)) |
			(at << (( CqFormat_PC_3 *  CqFormat_PACK_TYPE_REQUIRED_BITS) +  CqFormat_PACK_TYPE_SHIFT)) |
			0;
	return packed;
}

constexpr uint64_t  CqFormat_CONSTEXPR_DepthStencil( uint64_t rs, uint64_t rb, uint64_t rt, uint64_t gs, uint64_t gb, uint64_t gt, uint64_t size) {
	static_assert((( CqFormat_DEPTH_STENCIL_NUM_CHANNELS *  CqFormat_DEPTH_STENCIL_BITS_REQUIRED_BITS) +  CqFormat_DEPTH_STENCIL_BITS_SHIFT) == 20);
	static_assert((( CqFormat_DEPTH_STENCIL_NUM_CHANNELS *  CqFormat_DEPTH_STENCIL_SWIZZLE_REQUIRED_BITS) +  CqFormat_DEPTH_STENCIL_SWIZZLE_SHIFT) == 24);
	static_assert((( CqFormat_DEPTH_STENCIL_NUM_CHANNELS *  CqFormat_DEPTH_STENCIL_TYPE_REQUIRED_BITS) +  CqFormat_DEPTH_STENCIL_TYPE_SHIFT) == 28);

	static_assert((( CqFormat_DEPTH_STENCIL_NUM_CHANNELS *  CqFormat_DEPTH_STENCIL_TYPE_REQUIRED_BITS) +  CqFormat_DEPTH_STENCIL_TYPE_SHIFT) < 64);

	uint64_t value = CqFormat_NAMESPACE_DEPTH_STENCIL |
			(size <<  CqFormat_DEPTH_STENCIL_TOTAL_SIZE_SHIFT) |
			(rb << (( CqFormat_PC_0 *  CqFormat_DEPTH_STENCIL_BITS_REQUIRED_BITS) +  CqFormat_DEPTH_STENCIL_BITS_SHIFT)) |
			(rs << (( CqFormat_PC_0 *  CqFormat_DEPTH_STENCIL_SWIZZLE_REQUIRED_BITS) +  CqFormat_DEPTH_STENCIL_SWIZZLE_SHIFT)) |
			(rt << (( CqFormat_PC_0 *  CqFormat_DEPTH_STENCIL_TYPE_REQUIRED_BITS) +  CqFormat_DEPTH_STENCIL_TYPE_SHIFT)) |

			(gb << (( CqFormat_PC_1 *  CqFormat_DEPTH_STENCIL_BITS_REQUIRED_BITS) +  CqFormat_DEPTH_STENCIL_BITS_SHIFT)) |
			(gs << (( CqFormat_PC_1 *  CqFormat_DEPTH_STENCIL_SWIZZLE_REQUIRED_BITS) +  CqFormat_DEPTH_STENCIL_SWIZZLE_SHIFT)) |
			(gt << (( CqFormat_PC_1 *  CqFormat_DEPTH_STENCIL_TYPE_REQUIRED_BITS) +  CqFormat_DEPTH_STENCIL_TYPE_SHIFT)) |
			0;
	return value;
}

constexpr uint64_t  CqFormat_CONSTEXPR_DXTC(uint64_t alpha, uint64_t type, uint64_t blockBytes, uint64_t channelCount, uint64_t modeCount) {
	static_assert( CqFormat_DXTC_ALPHA_SHIFT == 12);
	static_assert( CqFormat_DXTC_TYPE_SHIFT == 14);
	static_assert( CqFormat_DXTC_BLOCKBYTES_SHIFT == 17);
	static_assert( CqFormat_DXTC_CHANNELCOUNT_SHIFT == 19);
	static_assert( CqFormat_DXTC_MODECOUNT_SHIFT == 21);

	static_assert( CqFormat_DXTC_MODECOUNT_REQUIRED_BITS +  CqFormat_DXTC_MODECOUNT_SHIFT < 64);

	uint64_t value = CqFormat_NAMESPACE_DXTC |
			(alpha <<  CqFormat_DXTC_ALPHA_SHIFT) |
			(type <<  CqFormat_DXTC_TYPE_SHIFT) |
			(blockBytes <<  CqFormat_DXTC_BLOCKBYTES_SHIFT) |
			(channelCount <<  CqFormat_DXTC_CHANNELCOUNT_SHIFT) |
			(modeCount <<  CqFormat_DXTC_MODECOUNT_SHIFT) |
			0;
	return value;
}

constexpr uint64_t  CqFormat_CONSTEXPR_PVRTC(uint64_t version, uint64_t bits, uint64_t type) {
	static_assert( CqFormat_PVRTC_VERSION_SHIFT == 12);
	static_assert( CqFormat_PVRTC_BITS_SHIFT == 14);
	static_assert( CqFormat_PVRTC_TYPE_SHIFT == 16);

	static_assert( CqFormat_PVRTC_TYPE_REQUIRED_BITS +  CqFormat_PVRTC_TYPE_SHIFT < 64);

	uint64_t value = CqFormat_NAMESPACE_PVRTC |
			(version <<  CqFormat_PVRTC_VERSION_SHIFT) |
			(bits <<  CqFormat_PVRTC_BITS_SHIFT) |
			(type <<  CqFormat_PVRTC_TYPE_SHIFT) |
			0;
	return value;
}

constexpr uint64_t  CqFormat_CONSTEXPR_ETC(uint64_t bits, uint64_t alpha, uint64_t type, uint64_t channelCount) {
	static_assert( CqFormat_ETC_BITS_SHIFT == 12);
	static_assert( CqFormat_ETC_ALPHA_SHIFT == 14);
	static_assert( CqFormat_ETC_TYPE_SHIFT == 16);
	static_assert( CqFormat_ETC_CHANNELCOUNT_SHIFT == 18);

	static_assert( CqFormat_ETC_CHANNELCOUNT_REQUIRED_BITS +  CqFormat_ETC_CHANNELCOUNT_SHIFT < 64);

	uint64_t value = CqFormat_NAMESPACE_ETC |
			(bits <<  CqFormat_ETC_BITS_SHIFT) |
			(alpha <<  CqFormat_ETC_ALPHA_SHIFT) |
			(type <<  CqFormat_ETC_TYPE_SHIFT) |
			(channelCount <<  CqFormat_ETC_CHANNELCOUNT_SHIFT) |
			0;
	return value;
}

constexpr uint64_t  CqFormat_CONSTEXPR_ASTC(uint64_t w, uint64_t h, uint64_t d, uint64_t type) {
	static_assert( CqFormat_ASTC_SIZE_SHIFT == 12);
	static_assert( CqFormat_ASTC_TYPE_SHIFT == 21);

	static_assert( (CqFormat_ASTC_NUM_DIMS * CqFormat_ASTC_TYPE_REQUIRED_BITS) +  CqFormat_ASTC_TYPE_SHIFT < 64);

	uint64_t value = CqFormat_NAMESPACE_ASTC |
			(w << ((0 *  CqFormat_ASTC_SIZE_REQUIRED_BITS) +  CqFormat_ASTC_SIZE_SHIFT)) |
			(h << ((1 *  CqFormat_ASTC_SIZE_REQUIRED_BITS) +  CqFormat_ASTC_SIZE_SHIFT)) |
			(d << ((2 *  CqFormat_ASTC_SIZE_REQUIRED_BITS) +  CqFormat_ASTC_SIZE_SHIFT)) |
			(type <<  CqFormat_ASTC_TYPE_SHIFT) |
			0;
	return value;
}

constexpr uint64_t  CqFormat_CONSTEXPR_CLUT(uint64_t bs, uint64_t c0s, uint64_t c0t, uint64_t c1s, uint64_t c1t) {
	static_assert( CqFormat_CLUT_BLOCKSIZE_SHIFT == 12);
	static_assert( CqFormat_CLUT_BITS_SHIFT == 14);
	static_assert( CqFormat_CLUT_TYPE_SHIFT == 20);

	static_assert( (CqFormat_CLUT_NUM_CHANNELS * CqFormat_CLUT_TYPE_REQUIRED_BITS) +  CqFormat_CLUT_TYPE_SHIFT < 64);

	uint64_t value = 	CqFormat_NAMESPACE_CLUT |
			(bs << CqFormat_CLUT_BLOCKSIZE_SHIFT) |
			(c0s << ((0 *  CqFormat_CLUT_BITS_REQUIRED_BITS) +  CqFormat_CLUT_BITS_SHIFT)) |
			(c1s << ((1 *  CqFormat_CLUT_BITS_REQUIRED_BITS) +  CqFormat_CLUT_BITS_SHIFT)) |
			(c0t << ((0 *  CqFormat_CLUT_TYPE_REQUIRED_BITS) +  CqFormat_CLUT_TYPE_SHIFT)) |
			(c1t << ((1 *  CqFormat_CLUT_TYPE_REQUIRED_BITS) +  CqFormat_CLUT_TYPE_SHIFT)) |
			0;
	return value;
}

constexpr bool IsInPacked(char const *name, uint64_t v) {
	return (v & CqFormat_NAMESPACE_MASK) == CqFormat_NAMESPACE_PACK;
}

constexpr bool IsInDepthStencil(char const *name, uint64_t v) {
	return (v & CqFormat_NAMESPACE_MASK) == CqFormat_NAMESPACE_DEPTH_STENCIL;
}

constexpr bool IsInDXTC(char const *name, uint64_t v) {
	return (v & CqFormat_NAMESPACE_MASK) == CqFormat_NAMESPACE_DXTC;
}

constexpr bool IsInPVRTC(char const *name, uint64_t v) {
	return (v & CqFormat_NAMESPACE_MASK) == CqFormat_NAMESPACE_PVRTC;
}

constexpr bool IsInETC(char const *name, uint64_t v) {
	return (v & CqFormat_NAMESPACE_MASK) == CqFormat_NAMESPACE_ETC;
}

constexpr bool IsInASTC(char const *name, uint64_t v) {
	return (v & CqFormat_NAMESPACE_MASK) == CqFormat_NAMESPACE_ASTC;
}

constexpr bool IsInCLUT(char const *name, uint64_t v) {
	return (v & CqFormat_NAMESPACE_MASK) == CqFormat_NAMESPACE_CLUT;
}

constexpr uint64_t Mask(uint64_t v) {
	return (1ULL << v) - 1ULL;
}
