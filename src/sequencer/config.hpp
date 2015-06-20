#pragma once


// Global sample rate
#define AUDIO_SAMPLE_RATE 44100

// Rate to decrease volume for voices that are being terminated early in seconds
#define VOICE_MUTE_DECAY_RATE (1.0f / 20.0f)


#define VOICE_MUTE_DECAY_RATE_PER_TICK (AUDIO_SAMPLE_RATE * VOICE_MUTE_DECAY_RATE)


#define MAX_ACTIVE_VOICES_PER_TRACK 3

#define PI 3.14159265f