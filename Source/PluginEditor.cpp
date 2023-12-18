/*
 ==============================================================================
 
 PluginEditor.cpp
 Created: 17 Dec 2023 11:59:07am
 Author:  Keith Hetrick
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
/**
 */
MagellanAudioProcessorEditor::MagellanAudioProcessorEditor(ExploraditoAudioProcessor& p)
: AudioProcessorEditor(&p), audioProcessor(p) {
    
    webBrowser.setVisible(false);  // Initially hide the web browser window
    addAndMakeVisible(modalComponent);
    modalComponent.toFront(true); // Ensure it's at the front on plugin load
    
    // Add the web browser window component and make it visible
    addAndMakeVisible(webBrowser);
    
    // Make the editor resizable and use the bottom-right corner for resizing
    setResizable(true, true);
    addAndMakeVisible(resizableCorner);
    
    // Configure the resize limits (min and max sizes)
    resizeConstrainer.setSizeLimits(400, 300, 1200, 900);
    setResizeLimits(400, 300, 1200, 900);
    
    // Set the initial size of the plugin window
    setSize(700, 600);
}

MagellanAudioProcessorEditor::~MagellanAudioProcessorEditor() {
    // Reset the LookAndFeel to avoid dangling pointers
}

void MagellanAudioProcessorEditor::paint(juce::Graphics& g) {
    // Background gradient fill
    juce::ColourGradient backgroundGradient(juce::Colours::sienna, 0, 0,
                                            juce::Colours::slategrey, getWidth(), getHeight(), false);
    g.setGradientFill(backgroundGradient);
    g.fillAll();
    
    // Text gradient
    juce::ColourGradient textGradient(juce::Colours::sienna, 0, 0,
                                      juce::Colours::slategrey, 0, 30, false); // Adjust as needed
    
    // Create a GlyphArrangement for the text
    juce::GlyphArrangement glyphArrangement;
    juce::Font font("Helvetica", 24.0f, juce::Font::bold);
    glyphArrangement.addLineOfText(font, "Magellan", 0, 0);
    
    // Convert the GlyphArrangement to a Path
    juce::Path textPath;
    glyphArrangement.createPath(textPath);
    
    // Centering the text
    juce::Rectangle<float> textBounds = textPath.getBounds();
    float x = (getWidth() - textBounds.getWidth()) / 2.0f;
    float y = 40; // Adjust Y position as needed
    
    // Draw the text with the gradient
    g.setGradientFill(textGradient);
    g.fillPath(textPath, juce::AffineTransform::translation(x, y));
}

void MagellanAudioProcessorEditor::closeModalComponent() {
    modalComponent.setVisible(false);
    webBrowser.setVisible(true);  // Show the web browser when modal is closed
}

void MagellanAudioProcessorEditor::resized() {
    // Debugging: Output or check the resized call
    //    DBG("PluginEditor resized to: " << getWidth() << " x " << getHeight());
    
    modalComponent.setBounds(getLocalBounds());
    modalComponent.toFront(true);
    
    // Define the area for the web browser window
    auto webBrowserArea = getLocalBounds();
    
    // Reduce the area by the size of the resizable corner
    const int cornerSize = 15;  // Adjust this size as needed
    webBrowserArea.removeFromBottom(cornerSize).removeFromRight(cornerSize);
    
    // Set the bounds for the web browser
    webBrowser.setBounds(webBrowserArea);
    
    // Position the resizable corner component
    resizableCorner.setBounds(getWidth() - cornerSize, getHeight() - cornerSize, cornerSize, cornerSize);
}

