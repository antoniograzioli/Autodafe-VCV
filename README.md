# Autodafe Module Pack for VCV Rack

Autodafe Module Pack for VCV Rack contains a collection of utility, sequencer,
filter, oscillator, and effects modules:

LFO module with CV Input

Simple but handy 1x8 and 2x8 Multiples

Clock Divider

8-Steps and 16-Steps Sequencers

8x16 Trigger Sequencer

Fixed Filter Bank

Foldback distortion

Bitcrusher

Phaser

Chorus

Reverb

## Building

Builds use VCV Rack 2's plugin makefile. Set `RACK_DIR` to the Rack source
tree, for example:

```sh
make RACK_DIR=/path/to/Rack
make dist RACK_DIR=/path/to/Rack
```

STK and Gamma are fetched at pinned revisions, compiled for the selected Rack
target, and linked as position-independent static archives. The plugin does
not require either library to be installed on the user's system. Use
`make audit-deps RACK_DIR=/path/to/Rack` to verify dependency architectures.

The current release is 2.0.6. Module slugs, port/parameter IDs, patch JSON
data, and panel layouts remain compatible with earlier 2.0.x releases.

