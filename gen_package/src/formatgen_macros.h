#pragma once

#define  CqFormat_PACK( rs, rb, rt, gs, gb, gt, bs, bb, bt, as, ab, at, special)   CqFormat_CONSTEXPR_Pack( \
				 CqFormat_PACK_SWIZZLE_##rs,  CqFormat_PACK_BITS_##rb,  CqFormat_PACK_TYPE_##rt, \
				 CqFormat_PACK_SWIZZLE_##gs,  CqFormat_PACK_BITS_##gb,  CqFormat_PACK_TYPE_##gt, \
				 CqFormat_PACK_SWIZZLE_##bs,  CqFormat_PACK_BITS_##bb,  CqFormat_PACK_TYPE_##bt, \
				 CqFormat_PACK_SWIZZLE_##as,  CqFormat_PACK_BITS_##ab,  CqFormat_PACK_TYPE_##at, \
				 CqFormat_PACK_SPECIAL_##special)

#define  CqFormat_PACK_3(rs, rb, rt, gs, gb, gt, bs, bb, bt, special)\
			 CqFormat_PACK(rs, rb, rt, gs, gb, gt, bs, bb, bt, 1, _, _, special)
#define  CqFormat_PACK_2(rs, rb, rt, gs, gb, gt, special)  CqFormat_PACK(rs, rb, rt, gs, gb, gt, 0, _, _, 1, _, _, special)
#define  CqFormat_PACK_1(rs, rb, rt, special)    CqFormat_PACK(rs, rb, rt, 0, _, _, 0, _, _, 1, _, _, special)

#define  CqFormat_PACK_2_UNORM(rs, rb, gs, gb, special)    CqFormat_PACK_2(rs, rb, UNORM, gs, gb, UNORM, special)
#define  CqFormat_PACK_3_UNORM(rs, rb, gs, gb, bs, bb, special)   CqFormat_PACK_3(rs, rb, UNORM, gs, gb, UNORM, bs, bb, UNORM, special)
#define  CqFormat_PACK_4_UNORM(rs, rb, gs, gb, bs, bb, as, ab, special)   CqFormat_PACK(rs, rb, UNORM, gs, gb, UNORM, bs, bb, UNORM, as, ab, UNORM, special)
#define  CqFormat_PACK_2_SNORM(rs, rb, gs, gb, special)    CqFormat_PACK_2(rs, rb, SNORM, gs, gb, SNORM, special)
#define  CqFormat_PACK_3_SNORM(rs, rb, gs, gb, bs, bb, special)   CqFormat_PACK_3(rs, rb, SNORM, gs, gb, SNORM, bs, bb, SNORM, special)
#define  CqFormat_PACK_4_SNORM(rs, rb, gs, gb, bs, bb, as, ab, special)   CqFormat_PACK(rs, rb, SNORM, gs, gb, SNORM, bs, bb, SNORM, as, ab, SNORM, special)
#define  CqFormat_PACK_2_UINT(rs, rb, gs, gb, special)    CqFormat_PACK_2(rs, rb, UINT, gs, gb, UINT, special)
#define  CqFormat_PACK_3_UINT(rs, rb, gs, gb, bs, bb, special)   CqFormat_PACK_3(rs, rb, UINT, gs, gb, UINT, bs, bb, UINT, special)
#define  CqFormat_PACK_4_UINT(rs, rb, gs, gb, bs, bb, as, ab, special)   CqFormat_PACK(rs, rb, UINT, gs, gb, UINT, bs, bb, UINT, as, ab, UINT, special)
#define  CqFormat_PACK_2_SINT(rs, rb, gs, gb, special)    CqFormat_PACK_2(rs, rb, SINT, gs, gb, SINT, special)
#define  CqFormat_PACK_3_SINT(rs, rb, gs, gb, bs, bb, special)   CqFormat_PACK_3(rs, rb, SINT, gs, gb, SINT, bs, bb, SINT, special)
#define  CqFormat_PACK_4_SINT(rs, rb, gs, gb, bs, bb, as, ab, special)   CqFormat_PACK(rs, rb, SINT, gs, gb, SINT, bs, bb, SINT, as, ab, SINT, special)
#define  CqFormat_PACK_2_SFLOAT(rs, rb, gs, gb, special)   CqFormat_PACK_2(rs, rb, SFLOAT, gs, gb, SFLOAT, special)
#define  CqFormat_PACK_3_SFLOAT(rs, rb, gs, gb, bs, bb, special)   CqFormat_PACK_3(rs, rb, SFLOAT, gs, gb, SFLOAT, bs, bb, SFLOAT, special)
#define  CqFormat_PACK_4_SFLOAT(rs, rb, gs, gb, bs, bb, as, ab, special)   CqFormat_PACK(rs, rb, SFLOAT, gs, gb, SFLOAT, bs, bb, SFLOAT, as, ab, SFLOAT, special)

#define  CqFormat_PACK_2_SRGB(rs, rb, gs, gb, special)    CqFormat_PACK_2(rs, rb, SRGB, gs, gb, SRGB, special)
#define  CqFormat_PACK_3_SRGB(rs, rb, gs, gb, bs, bb, special)   CqFormat_PACK_3(rs, rb, SRGB, gs, gb, SRGB, bs, bb, SRGB, special)
// SRGB never goes in alpha
#define  CqFormat_PACK_4_SRGB(rs, rb, gs, gb, bs, bb, as, ab, special)   CqFormat_PACK(rs, rb, SRGB, gs, gb, SRGB, bs, bb, SRGB, as, ab, UNORM, special)


#define  CqFormat_DEPTH_STENCIL( rs, rb, rt, gs, gb, gt, size)   CqFormat_CONSTEXPR_DepthStencil( \
				 CqFormat_DEPTH_STENCIL_SWIZZLE_##rs,  CqFormat_DEPTH_STENCIL_BITS_##rb,  CqFormat_DEPTH_STENCIL_TYPE_##rt, \
				 CqFormat_DEPTH_STENCIL_SWIZZLE_##gs,  CqFormat_DEPTH_STENCIL_BITS_##gb,  CqFormat_DEPTH_STENCIL_TYPE_##gt, \
				 CqFormat_DEPTH_STENCIL_TOTAL_SIZE_##size)

#define  CqFormat_DXTC(a, t, b, cc, mc)  CqFormat_CONSTEXPR_DXTC( CqFormat_DXTC_ALPHA_##a,  CqFormat_DXTC_TYPE_##t,  CqFormat_DXTC_BLOCKBYTES_##b,  CqFormat_DXTC_CHANNELCOUNT_##cc,  CqFormat_DXTC_MODECOUNT_##mc)
#define  CqFormat_PVRTC(v, b, t)  CqFormat_CONSTEXPR_PVRTC( CqFormat_PVRTC_VERSION_##v,  CqFormat_PVRTC_BITS_##b,  CqFormat_PVRTC_TYPE_##t)
#define  CqFormat_ETC(b, a, t, cc)  CqFormat_CONSTEXPR_ETC( CqFormat_ETC_BITS_##b,  CqFormat_ETC_ALPHA_##a,  CqFormat_ETC_TYPE_##t,  CqFormat_ETC_CHANNELCOUNT_##cc)
#define  CqFormat_ASTC(w, h, d, t)  CqFormat_CONSTEXPR_ASTC( CqFormat_ASTC_SIZE_##w,  CqFormat_ASTC_SIZE_##h,  CqFormat_ASTC_SIZE_##d,  CqFormat_ASTC_TYPE_##t)
#define  CqFormat_CLUT(bs, c0s, c0t, c1s, c1t)  CqFormat_CONSTEXPR_CLUT( CqFormat_CLUT_BLOCKSIZE_##bs, CqFormat_CLUT_BITS_##c0s,  CqFormat_CLUT_TYPE_##c0t,   CqFormat_CLUT_BITS_##c1s,  CqFormat_CLUT_TYPE_##c1t)


#define CqFormat_PACK_BITS__  CqFormat_PACK_BITS_0
#define CqFormat_PACK_SWIZZLE__  CqFormat_PACK_SWIZZLE_0
#define CqFormat_PACK_TYPE__  CqFormat_PACK_TYPE_NONE
#define CqFormat_DEPTH_STENCIL_BITS__  CqFormat_DEPTH_STENCIL_BITS_0
#define CqFormat_DEPTH_STENCIL_SWIZZLE__  CqFormat_DEPTH_STENCIL_SWIZZLE_0
#define CqFormat_DEPTH_STENCIL_TYPE__  CqFormat_DEPTH_STENCIL_TYPE_NONE

#define CqFormat_CLUT_BLOCKSIZE__  CqFormat_CLUT_BLOCKSIZE_1
#define CqFormat_CLUT_BITS__  CqFormat_CLUT_BITS_0
#define CqFormat_CLUT_TYPE__  CqFormat_CLUT_TYPE_NONE
