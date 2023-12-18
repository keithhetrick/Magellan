/*
 ==============================================================================
 
 Modal.h
 Created: 17 Dec 2023 11:58:48am
 Author:  Keith Hetrick
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
 */
class ModalComponent : public juce::Component {
public:
    ModalComponent() {
        closeButton.setButtonText("Close");
        closeButton.onClick = [this] { setVisible(false); };
        addAndMakeVisible(closeButton);
        
        titleLabel.setFont(juce::Font(16.0f, juce::Font::bold));
        titleLabel.setText("Dora ain't got nothing on this Explorer", juce::dontSendNotification);
        addAndMakeVisible(titleLabel);
    }
    
    void resized() override {
        auto area = getLocalBounds().reduced(10);
        titleLabel.setBounds(area.removeFromTop(40));
        closeButton.setBounds(area.removeFromTop(24));
    }
    
    void paint(juce::Graphics& g) override {
        g.fillAll(juce::Colours::black.withAlpha(0.85f)); // Semi-transparent background
    }
    
private:
    juce::TextButton closeButton;
    juce::Label titleLabel;
};
