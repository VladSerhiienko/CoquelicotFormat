#include "coquelicot/coquelicot_format_base.h"
#include "coquelicot/coquelicot_format_query.h"
#include "utils.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <float.h>

using Catch::Approx;

TEST_CASE("Format Cracker IsDepthOnly (C/Cpp)", "[Image]") {
    for (uint32_t i = 0; i < CqFormat_Count; ++i) {
        coquelicot::fmt::Format fmt = (coquelicot::fmt::Format)i;
        char const *name = CqFormat_Name(CqFormat(i));
        bool shouldBe = strstr(name, "D16") != nullptr;
        shouldBe |= strstr(name, "D24") != nullptr;
        shouldBe |= strstr(name, "D32") != nullptr;
        shouldBe &= (strstr(name, "S8") == nullptr);

        if (coquelicot::isDepthOnly(fmt) != shouldBe) { LOGERROR("CqFormat_IsDepthOnly failed %s", name); }
        CHECK(coquelicot::isDepthOnly(fmt) == shouldBe);
    }
}

TEST_CASE("Format Cracker IsDepthOnly (C)", "[Image]") {

	for (uint32_t i = 0; i < CqFormat_Count; ++i) {
		CqFormat fmt = (CqFormat) i;
		char const *name = CqFormat_Name(fmt);
		bool shouldBe = strstr(name, "D16") != nullptr;
		shouldBe |= strstr(name, "D24") != nullptr;
		shouldBe |= strstr(name, "D32") != nullptr;
		shouldBe &= (strstr(name, "S8") == nullptr);

		if (CqFormat_IsDepthOnly(fmt) != shouldBe) {
			LOGINFO("CqFormat_IsDepthOnly failed %s", name);
		}
		CHECK(CqFormat_IsDepthOnly(fmt) == shouldBe);
	}
}

TEST_CASE("Format Cracker IsStencilOnly (C)", "[Image]") {

	for (uint32_t i = 0; i < CqFormat_Count; ++i) {
		CqFormat fmt = (CqFormat) i;
		char const *name = CqFormat_Name(fmt);
		bool shouldBe = (strstr(name, "S8") != nullptr) &&
										(strstr(name, "D") == nullptr);

		if (CqFormat_IsStencilOnly(fmt) != shouldBe) {
			LOGINFO("CqFormat_IsStencilOnly failed %s", name);
		}
		CHECK(CqFormat_IsStencilOnly(fmt) == shouldBe);
	}
}

TEST_CASE("Format Cracker IsDepthAndStencil (C)", "[Image]") {

  for (uint32_t i = 0; i < CqFormat_Count; ++i) {
		CqFormat fmt = (CqFormat) i;
		char const *name = CqFormat_Name(fmt);
		bool shouldBe = strstr(name, "D16") != nullptr;
		shouldBe |= strstr(name, "D24") != nullptr;
		shouldBe |= strstr(name, "D32") != nullptr;
		shouldBe &= strstr(name, "S8") != nullptr;

		if (CqFormat_IsDepthAndStencil(fmt) != shouldBe) {
			LOGINFO("CqFormat_IsDepthAndStencil failed %s", name);
		}
		CHECK(CqFormat_IsDepthAndStencil(fmt) == shouldBe);
  }
}

TEST_CASE("Format Cracker IsFloat (C)", "[Image]") {

  for (uint32_t i = 0; i < CqFormat_Count; ++i) {
		CqFormat fmt = (CqFormat) i;
		char const *name = CqFormat_Name(fmt);
		bool shouldBe = strstr(name, "SFLOAT") != nullptr;
		shouldBe |= strstr(name, "UFLOAT") != nullptr;
		shouldBe |= strstr(name, "SBFLOAT") != nullptr;

		if (CqFormat_IsFloat(fmt) != shouldBe) {
			LOGINFO("CqFormat_IsFloat failed %s", name);
		}
		CHECK(CqFormat_IsFloat(fmt) == shouldBe);
  }
}

TEST_CASE("Format Cracker IsNormalised (C)", "[Image]") {

  for (uint32_t i = 0; i < CqFormat_Count; ++i) {
		CqFormat fmt = (CqFormat) i;
		char const *name = CqFormat_Name(fmt);
		bool shouldBeNormalised = strstr(name, "UNORM") != nullptr;
		shouldBeNormalised |= strstr(name, "SNORM") != nullptr;
		shouldBeNormalised |= strstr(name, "SRGB") != nullptr;

		if (CqFormat_IsNormalised(fmt) != shouldBeNormalised) {
			LOGINFO("CqFormat_IsNormalised failed %s", name);
		}
		CHECK(CqFormat_IsNormalised(fmt) == shouldBeNormalised);
	}
}

TEST_CASE("Format Cracker IsSigned (C)", "[Image]") {
  for (uint32_t i = 0; i < CqFormat_Count; ++i) {
		CqFormat fmt = (CqFormat) i;
		char const *name = CqFormat_Name(fmt);
		bool shouldBe = strstr(name, "SNORM") != nullptr;
		shouldBe |= strstr(name, "SSCALED") != nullptr;
		shouldBe |= strstr(name, "SINT") != nullptr;
		shouldBe |= strstr(name, "SFLOAT") != nullptr;
		shouldBe |= strstr(name, "SBFLOAT") != nullptr;

		if (CqFormat_IsSigned(fmt) != shouldBe) {
			LOGINFO("CqFormat_IsSigned failed %s", name);
		}
		CHECK(CqFormat_IsSigned(fmt) == shouldBe);
  }
}

TEST_CASE("Format Cracker IsSRGB (C)", "[Image]") {

  for (uint32_t i = 0; i < CqFormat_Count; ++i) {
		CqFormat fmt = (CqFormat) i;
		char const *name = CqFormat_Name(fmt);
		bool shouldBe = strstr(name, "SRGB") != nullptr;

		if (CqFormat_IsSRGB(fmt) != shouldBe) {
			LOGINFO("CqFormat_IsSRGB failed %s", name);
		}
		CHECK(CqFormat_IsSRGB(fmt) == shouldBe);
  }
}

TEST_CASE("Format Cracker IsCompressed (C)", "[Image]") {

	for (uint32_t i = 0; i < CqFormat_Count; ++i) {
		CqFormat fmt = (CqFormat) i;
		char const *name = CqFormat_Name(fmt);
		bool shouldBe = false;
		shouldBe |=	(strstr(name, "DXBC") != nullptr);
		shouldBe |=	(strstr(name, "ETC") != nullptr);
		shouldBe |=	(strstr(name, "PVRTC") != nullptr);
		shouldBe |=	(strstr(name, "ASTC") != nullptr);

		if (CqFormat_IsCompressed(fmt) != shouldBe) {
			LOGINFO("CqFormat_IsCompressed failed %s", name);
		}
		CHECK(CqFormat_IsCompressed(fmt) == shouldBe);
	}
}

TEST_CASE("Format Cracker Min (C)", "[Image]") {

  // random sample a few to check
  REQUIRE(CqFormat_Min(CqFormat_R8G8B8A8_UINT, CqFormat_LC_Red) == Approx(0));
  REQUIRE(CqFormat_Min(CqFormat_R8G8B8A8_UINT, CqFormat_LC_Green) == Approx(0));
  REQUIRE(CqFormat_Min(CqFormat_R8G8B8A8_UINT, CqFormat_LC_Blue) == Approx(0));
  REQUIRE(CqFormat_Min(CqFormat_R8G8B8A8_UINT, CqFormat_LC_Alpha) == Approx(0));

  REQUIRE(CqFormat_Min(CqFormat_R8G8B8A8_SINT, CqFormat_LC_Red) == Approx(-128));
  REQUIRE(CqFormat_Min(CqFormat_R8G8B8A8_SINT, CqFormat_LC_Green) == Approx(-128));
  REQUIRE(CqFormat_Min(CqFormat_R8G8B8A8_SINT, CqFormat_LC_Blue) == Approx(-128));
  REQUIRE(CqFormat_Min(CqFormat_R8G8B8A8_SINT, CqFormat_LC_Alpha) == Approx(-128));

  REQUIRE(CqFormat_Min(CqFormat_R32G32B32A32_SFLOAT, CqFormat_LC_Red) == Approx(-FLT_MAX));
  REQUIRE(CqFormat_Min(CqFormat_R32G32B32A32_SFLOAT, CqFormat_LC_Green) == Approx(-FLT_MAX));
  REQUIRE(CqFormat_Min(CqFormat_R32G32B32A32_SFLOAT, CqFormat_LC_Blue) == Approx(-FLT_MAX));
  REQUIRE(CqFormat_Min(CqFormat_R32G32B32A32_SFLOAT, CqFormat_LC_Alpha) == Approx(-FLT_MAX));

	REQUIRE(CqFormat_Min(CqFormat_R8G8B8X8_UNORM, CqFormat_LC_Red) == Approx(0.0));
	REQUIRE(CqFormat_Min(CqFormat_R8G8B8A8_SNORM, CqFormat_LC_Red) == Approx(-1.0));


}

TEST_CASE("Format Cracker Max (C)", "[Image]") {

  // random sample a few to check
  REQUIRE(CqFormat_Max(CqFormat_R8G8B8A8_UINT, CqFormat_LC_Red) == Approx(255));
  REQUIRE(CqFormat_Max(CqFormat_R8G8B8A8_UINT, CqFormat_LC_Green) == Approx(255));
  REQUIRE(CqFormat_Max(CqFormat_R8G8B8A8_UINT, CqFormat_LC_Blue) == Approx(255));
  REQUIRE(CqFormat_Max(CqFormat_R8G8B8A8_UINT, CqFormat_LC_Alpha) == Approx(255));

  REQUIRE(CqFormat_Max(CqFormat_R8G8B8A8_SINT, CqFormat_LC_Red) == Approx(127));
  REQUIRE(CqFormat_Max(CqFormat_R8G8B8A8_SINT, CqFormat_LC_Green) == Approx(127));
  REQUIRE(CqFormat_Max(CqFormat_R8G8B8A8_SINT, CqFormat_LC_Blue) == Approx(127));
  REQUIRE(CqFormat_Max(CqFormat_R8G8B8A8_SINT, CqFormat_LC_Alpha) == Approx(127));

  REQUIRE(CqFormat_Max(CqFormat_R32G32B32A32_SFLOAT, CqFormat_LC_Red) == Approx(FLT_MAX));
  REQUIRE(CqFormat_Max(CqFormat_R32G32B32A32_SFLOAT, CqFormat_LC_Green) == Approx(FLT_MAX));
  REQUIRE(CqFormat_Max(CqFormat_R32G32B32A32_SFLOAT, CqFormat_LC_Blue) == Approx(FLT_MAX));
  REQUIRE(CqFormat_Max(CqFormat_R32G32B32A32_SFLOAT, CqFormat_LC_Alpha) == Approx(FLT_MAX));

  REQUIRE(CqFormat_Max(CqFormat_D32_SFLOAT_S8_UINT, CqFormat_LC_Depth) == Approx(FLT_MAX));
  REQUIRE(CqFormat_Max(CqFormat_D32_SFLOAT_S8_UINT, CqFormat_LC_Stencil) == Approx(255));

	REQUIRE(CqFormat_Max(CqFormat_D32_SFLOAT, CqFormat_LC_Depth) == Approx(FLT_MAX));
	REQUIRE(CqFormat_Max(CqFormat_S8_UINT, CqFormat_LC_Stencil) == Approx(255));

	REQUIRE(CqFormat_Max(CqFormat_B8G8R8X8_UNORM, CqFormat_LC_Red) == Approx(1.0));
	REQUIRE(CqFormat_Max(CqFormat_B8G8R8A8_SNORM, CqFormat_LC_Red) == Approx(1.0));

}