# include "stdafx.h"
# include "MetaEvent.h"
# include "MidiStruct.h"
# include "IFileParser.h"
# include "MidiError.h"

MetaEvent::MetaEvent(const char statusByte, const char metaType) :
	Event(statusByte)
{
	GetChunk()->metaType = metaType;
}

std::unique_ptr<MetaEvent> MetaEvent::GetInstance(const char statusByte)
{
	if (!GetInputFile()) throw MidiError("INPUT FILE HAS NOT BEEN SET YET");
	const auto metaType(GetInputFile()->ReadByte());

	switch (metaType)
	{
	case 0x00: case 0x01: case 0x02: case 0x03: case 0x04: case 0x05: case 0x06: case 0x07:
				return MetaEvent_Text		::GetInstance(statusByte, metaType); break;
	case 0x20: case 0x21: case 0x54: case 0x58: case 0x7F:
				return MetaEvent_Skip		::GetInstance(statusByte, metaType); break;
	case 0x2F:	return MetaEvent_EndTrack	::GetInstance(statusByte, metaType); break;
	case 0x51:	return MetaEvent_Tempo		::GetInstance(statusByte, metaType); break;
	case 0x59:	return MetaEvent_KeySign	::GetInstance(statusByte, metaType); break;
	default: throw MidiError("WRONG META TYPE");
	}
}