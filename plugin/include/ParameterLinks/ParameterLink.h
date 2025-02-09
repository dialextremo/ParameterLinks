//
// Created by Juan Pablo Correa on 8/02/2025.
// juanpablocra29@gmail.com
//
#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

class ParameterLink : public juce::AudioProcessorValueTreeState::Listener
{
    enum class Type { Absolute, Delta, DeltaInv };

public:
    ParameterLink(const juce::String& parameterA,
                  const juce::String& parameterB,
                  juce::AudioProcessorValueTreeState* tree)
        : apvts(tree), parameters(parameterA, parameterB), type(Type::DeltaInv)
    {
        apvts->addParameterListener(parameterA, this);
        apvts->addParameterListener(parameterB, this);
        lastValue[0] = apvts->getParameter(parameterA)->getValue();
        lastValue[1] = apvts->getParameter(parameterB)->getValue();
    }

    void parameterChanged(const juce::String& parameterID, float newValue) override
    {
        if(isBusy || ! active) {
            lastValue[parameterID == parameters.first ? 0 : 1] = newValue;
            return;
        }

        juce::ScopedValueSetter<bool> setter(isBusy, true);
        juce::String& targetParameter =
            parameterID == parameters.first ? parameters.second : parameters.first;
        float oldValue = lastValue[parameterID == parameters.first ? 0 : 1];
        float currentTargetValue = apvts->getParameter(targetParameter)->getValue();

        float newTargetValue;
        if(type == Type::Delta) {
            float delta = newValue - oldValue;
            newTargetValue = currentTargetValue + delta;
        } else if(type == Type::DeltaInv) {
            float delta = newValue - oldValue;
            newTargetValue = currentTargetValue - delta;
        } else {
            newTargetValue = newValue;
        }

        lastValue[parameterID == parameters.first ? 0 : 1] = newValue;

        apvts->getParameter(targetParameter)->setValueNotifyingHost(newTargetValue);
    }

    void setMode(Type type_)
    {
        type = type_;
    }

    void setActive(bool active_)
    {
        active = active_;
    }

    ~ParameterLink() override = default;

private:
    bool isBusy = false;
    bool active = false;
    juce::AudioProcessorValueTreeState* apvts;
    std::pair<juce::String, juce::String> parameters;
    std::atomic<float> lastValue[2];
    Type type;
};