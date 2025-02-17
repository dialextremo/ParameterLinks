#pragma once

#include "PluginProcessor.h"

namespace audio_plugin {

class AudioPluginAudioProcessorEditor : public juce::AudioProcessorEditor {
public:
  explicit AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor&);
  ~AudioPluginAudioProcessorEditor() override;

  void paint(juce::Graphics&) override;
  void resized() override;

private:
  // This reference is provided as a quick way for your editor to
  // access the processor object that created it.
  AudioPluginAudioProcessor& processorRef;
  juce::AudioProcessorValueTreeState& valueTreeState;
  juce::Slider gainSliderL;
  juce::Slider gainSliderR;
  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainSliderAttachmentL;
  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainSliderAttachmentR;

  juce::ToggleButton toggleButton;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessorEditor)
};
}  // namespace audio_plugin
