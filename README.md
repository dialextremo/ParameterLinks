# Parameter Linking in JUCE

This is a simple example of how to link parameters in JUCE. The example is a simple gain plugin that has two parameters for the left and right gain and a toggle for activating or deactivating it. It uses a AudioProcessorValueTreeState for setting the targeted parameter. This solution also works in Logic as it uses meta parameters.

Let me know if you have any suggestions!

## Building

```bash
$ cmake -S . -B build
$ cmake --build build
```

(Built with WolfSound's plugin template)
https://github.com/JanWilczek/audio-plugin-template
