# pragma once

namespace MidiStruct
{
	struct TrackEvent;
}

class MidiTimeCalculator : private boost::noncopyable
{
	uint16_t tempoDivision_, UNUSED_6_[3];	// 6 padding bytes
	double microSeconds_;
	std::map<double, uint32_t> tempoSettings_, globalTempoSettings_;

	std::vector<std::vector<MidiStruct::TrackEvent>> tracks_;
	typedef std::vector<std::vector<unsigned>> Times_;
	typedef std::vector<std::vector<int16_t>> Notes_;
	Times_ milliSeconds_;
	Notes_ notes_;

	size_t currentTrack_, currentEvent_;

	std::string log_;
	std::vector<std::string> trackNames_;
#ifdef _DEBUG
	int UNUSED_4_;							// 4 padding bytes
#endif
public:
	MidiTimeCalculator();
	~MidiTimeCalculator();

	void LoadMidiData(const char* fileName);
	void LoadMidiData(const wchar_t* fileName);
	void CalcDeltaTimes();

	Times_ GetTimes() const
	{
		return milliSeconds_;
	}
	Notes_ GetNotes() const
	{
		return notes_;
	}
	const std::string& GetLog() const
	{
		return log_;
	}
	const std::vector<std::string>& GetTrackNames() const
	{
		return trackNames_;
	}
private:
	void ProgressMicroseconds();
	void ReadEvent();
	bool EndOfTracks();
	MidiStruct::TrackEvent GetEvent() const;

	double DeltaToMicrosec(double, uint32_t) const;
	double MicrosecToDelta(double, uint32_t) const;
};