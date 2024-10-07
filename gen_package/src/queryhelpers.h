RAW_INCLUDE_START( R"=====( )

// Helpers
CQ_FMT_CONSTEXPR inline uint32_t TinyImageFormat_PixelCountOfBlock(TinyImageFormat const fmt) {
	return TinyImageFormat_WidthOfBlock(fmt) * TinyImageFormat_HeightOfBlock(fmt) * TinyImageFormat_DepthOfBlock(fmt);
}

CQ_FMT_CONSTEXPR inline double TinyImageFormat_Min(TinyImageFormat const fmt, TinyImageFormat_LogicalChannel const channel) {
	return TinyImageFormat_MinAtPhysical(fmt, TinyImageFormat_LogicalChannelToPhysical(fmt, channel));
}

CQ_FMT_CONSTEXPR inline double TinyImageFormat_Max(TinyImageFormat const fmt, TinyImageFormat_LogicalChannel const channel) {
	return TinyImageFormat_MaxAtPhysical(fmt, TinyImageFormat_LogicalChannelToPhysical(fmt, channel));
}

CQ_FMT_CONSTEXPR inline uint32_t TinyImageFormat_ChannelBitWidth(TinyImageFormat const fmt, TinyImageFormat_LogicalChannel const channel) {
	return TinyImageFormat_ChannelBitWidthAtPhysical(fmt, TinyImageFormat_LogicalChannelToPhysical(fmt, channel));
}

RAW_INCLUDE_END( )=====" )