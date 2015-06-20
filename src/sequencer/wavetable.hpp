#pragma once

class WaveTable
{

public:
    
    virtual ~WaveTable() { }
    
    virtual unsigned GetNumNotes() = 0;
	virtual unsigned GetKeyLength(unsigned key) = 0;
	virtual const float* GetKeyData(unsigned key) = 0;
    
    void BlitKey(float* buffer, unsigned bufferSize, unsigned offsetm, unsigned key, float volume);
    
};

class WaveTableSine : public WaveTable
{
    
private:
    
    float* _sourceBufferData;
	float** _waveTable;
    
public:
    
    WaveTableSine();
    ~WaveTableSine();
    
    unsigned GetNumNotes();
    unsigned GetKeyLength(unsigned key);
    const float* GetKeyData(unsigned key);
    
};