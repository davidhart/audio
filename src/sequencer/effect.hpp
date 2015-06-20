#pragma once

class Effect
{
public:
    virtual void Process(float* buffer, unsigned bufferSize, unsigned offset, float tempo) = 0;
    virtual ~Effect() { }
};