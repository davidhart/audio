#pragma once

#include <map>
#include <string>
#include <set>

#include "track.hpp"
#include "effect.hpp"

// TODO: implement looping

class Sequence
{

private:

	typedef  std::map<std::string, Track*> TrackCollection;
	TrackCollection _tracks;
    typedef std::set<Effect*> EffectCollection;
    EffectCollection _effectChain;

public:

	Sequence();
	~Sequence();

	Sequence(const Sequence& rhs);
	Sequence& operator=(const Sequence& rhs);

	Track* AddTrack(const char* name);
    Track* GetTrack(const char* name);
	void RemoveTrack(const char* name);
	void ClearTracks();
    
    void AddEffect(Effect* effect);
    void RemoveEffect(Effect* effect);
    void ClearEffects();

	void BlitSequence(float* buffer, unsigned bufferSize, unsigned offset, float tempo);
    
    unsigned GetLength() const;

private:

	void CopyInternal(const Sequence& rhs);

};