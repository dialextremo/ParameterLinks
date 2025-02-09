#include <memory>

#include "ParameterLinks/PluginEditor.h"
#include "ParameterLinks/PluginProcessor.h"

namespace audio_plugin
{
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor& p)
    : AudioProcessorEditor(&p), processorRef(p), valueTreeState(processorRef.apvts)
{
    gainSliderL.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainSliderL.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
    gainSliderR.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainSliderR.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
    addAndMakeVisible(gainSliderL);
    gainSliderAttachmentL = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        processorRef.apvts, "gainL", gainSliderL);
    addAndMakeVisible(gainSliderR);
    gainSliderAttachmentR = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        processorRef.apvts, "gainR", gainSliderR);

    toggleButton.onStateChange = [this] { processorRef.link.setActive(toggleButton.getToggleState()); };
    toggleButton.setToggleState(true, juce::NotificationType::sendNotification);
    addAndMakeVisible(toggleButton);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(400, 300);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {}

void AudioPluginAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a
    // solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void AudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto bounds = getLocalBounds();
    auto width = getWidth();
    auto height = getHeight();
    toggleButton.setBounds(bounds.removeFromBottom(height / 5));
    gainSliderL.setBounds(bounds.removeFromLeft(width / 2));
    gainSliderR.setBounds(bounds);
}

} // namespace audio_plugin
