RAW_INCLUDE_START( R"=====( )

// Helpers
CQ_FORMAT_CALL uint32_t CqFormat_PixelCountOfBlock(CqFormat const fmt) {
	return CqFormat_WidthOfBlock(fmt) * CqFormat_HeightOfBlock(fmt) * CqFormat_DepthOfBlock(fmt);
}

CQ_FORMAT_CALL double CqFormat_Min(CqFormat const fmt, CqFormat_LogicalChannel const channel) {
	return CqFormat_MinAtPhysical(fmt, CqFormat_LogicalChannelToPhysical(fmt, channel));
}

CQ_FORMAT_CALL double CqFormat_Max(CqFormat const fmt, CqFormat_LogicalChannel const channel) {
	return CqFormat_MaxAtPhysical(fmt, CqFormat_LogicalChannelToPhysical(fmt, channel));
}

CQ_FORMAT_CALL uint32_t CqFormat_ChannelBitWidth(CqFormat const fmt, CqFormat_LogicalChannel const channel) {
	return CqFormat_ChannelBitWidthAtPhysical(fmt, CqFormat_LogicalChannelToPhysical(fmt, channel));
}

RAW_INCLUDE_END( )=====" )