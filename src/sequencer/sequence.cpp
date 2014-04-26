#include "sequence.h"
#include "buffer_utils.h"

#include <cassert>

Sequence::Sequence()
{

}

Sequence::~Sequence()
{
	ClearTracks();
}

Sequence::Sequence(const Sequence& rhs)
{
	CopyInternal(rhs);
}

Sequence& Sequence::operator=(const Sequence& rhs)
{
	ClearTracks();

	CopyInternal(rhs);

	return *this;
}

Track* Sequence::AddTrack()
{
	Track* newTrack = new Track();

	_tracks.push_back(newTrack);

	return newTrack;
}

void Sequence::RemoveTrack(Track* track)
{
	TrackCollection::iterator it = std::find(_tracks.begin(), _tracks.end(), track);

	assert(it != _tracks.end());

	_tracks.erase(it);
}

void Sequence::ClearTracks()
{
	for (unsigned i = 0; i < _tracks.size(); ++i)
	{
		delete _tracks[i];
	}

	_tracks.clear();
}

void Sequence::BlitSequence(float* buffer, unsigned bufferSize, unsigned offset)
{
	BufferUtils::ZeroBuffer(buffer, bufferSize);

	for (unsigned i = 0; i < _tracks.size(); ++i)
	{
		_tracks[i]->BlitTrack(buffer, bufferSize, offset);
	}
}

void Sequence::CopyInternal(const Sequence& rhs)
{
	for(unsigned i = 0; i < rhs._tracks.size(); ++i)
	{
		_tracks.push_back(new Track(*rhs._tracks[i]));
	}
}