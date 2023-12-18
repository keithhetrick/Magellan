#pragma once

#include <JuceHeader.h>

//==============================================================================
class WebBrowserComponent : public juce::WebBrowserComponent {
public:
    WebBrowserComponent(juce::TextEditor& addressBox)
    : addressTextBox(addressBox) {}

    bool pageAboutToLoad(const juce::String& newURL) override {
        addressTextBox.setText(newURL, false);
        return true;
    }

    void newWindowAttemptingToLoad(const juce::String& newURL) override {
        goToURL(newURL);
    }

private:
    juce::TextEditor& addressTextBox;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WebBrowserComponent)
};

class WebBrowserWindow : public juce::Component {
public:
    WebBrowserWindow() {
        setOpaque(true);
        
        titleLabel.setText("Magellan", juce::dontSendNotification);
        titleLabel.setFont(juce::Font(24.0f, juce::Font::bold));
        titleLabel.setJustificationType(juce::Justification::centred);
        addAndMakeVisible(titleLabel);

        // Load the GitHub icon image
        juce::Image githubIcon = juce::ImageCache::getFromMemory(BinaryData::github_icon_png, BinaryData::github_icon_pngSize);
        
        // Set up the ImageButton with the GitHub icon
        if (githubIcon.isValid()) {
            githubButton.setImages(false, true, true,
                                   githubIcon, 1.0f, juce::Colours::transparentBlack,
                                   githubIcon, 1.0f, juce::Colours::white.withAlpha(0.7f),
                                   githubIcon, 1.0f, juce::Colours::white);
        }
        
        githubButton.onClick = [this] {
            juce::URL("https://github.com/keithhetrick").launchInDefaultBrowser();
        };
        addAndMakeVisible(githubButton);

        addAndMakeVisible(addressTextBox);
        addressTextBox.setTextToShowWhenEmpty("Enter a web address, e.g. https://www.dominos.com", juce::Colours::grey);
        addressTextBox.onReturnKey = [this] { webView->goToURL(addressTextBox.getText()); };
        
        webView.reset(new WebBrowserComponent(addressTextBox));
        addAndMakeVisible(webView.get());
        
        addAndMakeVisible(goButton);
        goButton.onClick = [this] { webView->goToURL(addressTextBox.getText()); };
        addAndMakeVisible(backButton);
        backButton.onClick = [this] { webView->goBack(); };
        addAndMakeVisible(forwardButton);
        forwardButton.onClick = [this] { webView->goForward(); };

        webView->goToURL("https://www.google.com");
    }

    void paint(juce::Graphics& g) override {
        g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    }
    
    void resized() override {
        auto area = getLocalBounds();
        
        auto titleArea = area.removeFromTop(40).reduced(8);
        int buttonSize = 30; // Size of the GitHub icon
        titleLabel.setBounds(titleArea.removeFromLeft(titleArea.getWidth() - buttonSize - 10));
        githubButton.setBounds(titleArea.removeFromRight(buttonSize));

        auto toolbarArea = area.removeFromTop(40);
        backButton.setBounds(toolbarArea.removeFromLeft(30));
        forwardButton.setBounds(toolbarArea.removeFromLeft(30));
        goButton.setBounds(toolbarArea.removeFromRight(60));
        addressTextBox.setBounds(toolbarArea);
        
        webView->setBounds(area);
    }

private:
    std::unique_ptr<WebBrowserComponent> webView;
    juce::TextEditor addressTextBox;
    juce::TextButton goButton      { "Go", "Go to URL" },
                     backButton    { "<", "Back" },
                     forwardButton { ">", "Forward" };
    juce::Label titleLabel;
    juce::ImageButton githubButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WebBrowserWindow)
};
