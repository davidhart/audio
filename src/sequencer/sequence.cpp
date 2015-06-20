#include "sequence.hpp"
#include "buffer_utils.hpp"

#include <cassert>
#include <algorithm>

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

Track* Sequence::AddTrack(const char* name)
{
	Track* newTrack = new Track();

	_tracks[name] = newTrack;

	return newTrack;
}

Track* Sequence::GetTrack(const char* name)
{
    TrackCollection::iterator it = _tracks.find(name);
    
    if (it == _tracks.end())
        return NULL;
    
    return it->second;
}

void Sequence::RemoveTrack(const char* name)
{
	TrackCollection::iterator it = _tracks.find(name);

	assert(it != _tracks.end());

	_tracks.erase(it);
}

void Sequence::ClearTracks()
{
	for (TrackCollection::iterator it = _tracks.begin(); it != _tracks.end(); ++it)
	{
		delete it->second;
	}

	_tracks.clear();
}

void Sequence::AddEffect(Effect* effect)
{
    _effectChain.insert(effect);
}

void Sequence::RemoveEffect(Effect* effect)
{
    _effectChain.erase(effect);
}

void Sequence::ClearEffects()
{
    _effectChain.clear();
}

void Sequence::BlitSequence(float* buffer, unsigned bufferSize, unsigned offset, float tempo)
{
	BufferUtils::ZeroBuffer(buffer, bufferSize);

	for (TrackCollection::iterator it = _tracks.begin(); it != _tracks.end(); ++it)
	{
		it->second->BlitTrack(buffer, bufferSize, offset, tempo);
	}
    
    for (EffectCollection::iterator it = _effectChain.begin(); it != _effectChain.end(); ++it)
    {
        (*it)->Process(buffer, bufferSize, offset, tempo);
    }
}

void Sequence::CopyInternal(const Sequence& rhs)
{
    _tracks.clear();
    
	for (TrackCollection::const_iterator it = rhs._tracks.begin(); it != rhs._tracks.end(); ++it)
	{
		_tracks[it->first] = new Track(*it->second);
	}
}

unsigned Sequence::GetLength() const
{
    unsigned maxLength = 0;
    
	for (TrackCollection::const_iterator it = _tracks.begin(); it != _tracks.end(); ++it)
	{
        maxLength = std::max(it->second->GetLength(), maxLength);
    }
    
    return maxLength;
}