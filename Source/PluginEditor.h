/*
 ==============================================================================
 
 PluginEditor.h
 Created: 17 Dec 2023 11:59:07a
 Author:  Keith Hetrick
 
 =============================================================================
 */
#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "WebBrowserWindow.h"
#include "Modal.h"

//==============================================================================
/**
 */
class MagellanAudioProcessorEditor : public juce::AudioProcessorEditor {
public:
    MagellanAudioProcessorEditor(ExploraditoAudioProcessor&);
    ~MagellanAudioProcessorEditor() override;
    
    void paint(juce::Graphics&) override;
    void resized() override;
    
    // Method to handle the modal close action
    void closeModalComponent();
    
private:
    ExploraditoAudioProcessor& audioProcessor;
    WebBrowserWindow webBrowser;
    
    // Modal popup
    ModalComponent modalComponent;
    
    // Declare buttons
    juce::TextButton showWindowsButton;
    juce::TextButton closeWindowsButton;
    
    // Additions for resizable corner
    juce::ComponentBoundsConstrainer resizeConstrainer;
    juce::ResizableCornerComponent resizableCorner {this, &resizeConstrainer};
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MagellanAudioProcessorEditor)
};
