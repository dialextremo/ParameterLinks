//
// Created by Juan Pablo Correa on 8/02/2025.
// juanpablocra29@gmail.com
//

#include <juce_audio_processors/juce_audio_processors.h>
#ifndef WOLFSOUNDAUDIOPLUGINTEMPLATE_PARAMETERLINK_H
    #define WOLFSOUNDAUDIOPLUGINTEMPLATE_PARAMETERLINK_H

class ParameterLink : public juce::AudioProcessorValueTreeState::Listener
{
public:
    ParameterLink(const juce::String& parameterA,
                  const juce::String& parameterB,
                  juce::AudioProcessorValueTreeState* tree)
        : apvts(tree), parameters(parameterA, parameterB)
    {
        apvts->addParameterListener("gainL", this);
        apvts->addParameterListener("gainR", this);
    }
    void parameterChanged(const juce::String& parameterID, float newValue) override
    {
        if(beganGesture)
            return;
        juce::ScopedValueSetter<bool> setter(beganGesture, true);
        juce::String& targetParameter =
            parameterID == parameters.first ? parameters.second : parameters.first;
        apvts->getParameter(targetParameter)->setValueNotifyingHost(newValue);
    }
    ~ParameterLink() = default;

private:
    bool beganGesture = false;
    juce::AudioProcessorValueTreeState* apvts;
    std::pair<juce::String, juce::String> parameters;
};

#endif //WOLFSOUNDAUDIOPLUGINTEMPLATE_PARAMETERLINK_H
