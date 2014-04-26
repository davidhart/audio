#pragma once

#include <vector>

#include "track.h"

// TODO: implement looping

class Sequence
{

private:

	typedef  std::vector<Track*> TrackCollection;
	TrackCollection _tracks;

public:

	Sequence();
	~Sequence();

	Sequence(const Sequence& rhs);
	Sequence& operator=(const Sequence& rhs);

	Track* AddTrack();
	void RemoveTrack(Track* track);
	void ClearTracks();

	void BlitSequence(float* buffer, unsigned bufferSize, unsigned offset);

private:

	void CopyInternal(const Sequence& rhs);

};