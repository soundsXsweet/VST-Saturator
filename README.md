# VST-Saturator


This is not the full program, as the required JUCE libraries exceed Github's upload size.

Please download the full program files here: https://drive.google.com/open?id=1a8k-_6MmE3h_5xKUzN-jXoxN5gnjB4sN

Core goals: to utilize existing frameworks in order to best showcase an understanding of DSP code.

This is a VST3 saturator plugin, designed to provide harmonic overtones, non-destructive clipping, slight compression, and saturation to an audio channel inside of a DAW. For testing and demonstration purposes, there is also a half-wave rectifier, imitating an analog diode recitifer. This cuts off half of the waveform, leading to a very destructive output. The soft clip saturator is the core of this program. The parameters are also logarithmically tied rather than linearlly, in order to bring them more in line with what we as humans are used to hearing when we increase/decrease audio parameters. 

Placeholder for demonstration video.
