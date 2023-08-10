/*
  ==============================================================================



  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player)
    : fChooser("Choose a file"), // Initialize fChooser first
      player(_player)            // Then initialize player
{
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);

    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    
    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);
    
    volSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.0, 100.0);
    posSlider.setRange(0.0, 1.0);
}

DeckGUI::~DeckGUI()
{

}

void DeckGUI::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);
    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("DeckGUI", getLocalBounds(),
                juce::Justification::centred, true);
}

void DeckGUI::resized()
{
    double rowH = getHeight() / 6;
    playButton.setBounds(0, 0, getWidth(), rowH);
    stopButton.setBounds(0, rowH, getWidth(), rowH);
    volSlider.setBounds(0, rowH * 2, getWidth(), rowH);
    speedSlider.setBounds(0, rowH * 3, getWidth(), rowH);
    posSlider.setBounds(0, rowH * 4, getWidth(), rowH);
    loadButton.setBounds(0, rowH * 5, getWidth(), rowH);
}

void DeckGUI::buttonClicked(juce::Button* button)
{
    if(button == &playButton)
    {
        std::cout << "Play button clicked" << std::endl;
        player->start();
    }
    if (button == &stopButton)
    {
        std::cout << "Stop button clicked" << std::endl;
        player->stop();
    }
    if (button == &loadButton)
    {
        auto fileChooserFlags = juce::FileBrowserComponent::canSelectFiles;

        fChooser.launchAsync(fileChooserFlags, [this](const juce::FileChooser& chooser)
        {
            juce::File chosenFile = chooser.getResult();
            std::cout << "Chosen file: " << chosenFile.getFullPathName() << std::endl;
            player->loadURL(juce::URL{chosenFile});
        });
        std::cout << "Load button clicked" << std::endl;
    }
}

void DeckGUI::sliderValueChanged(juce::Slider* slider)
{
    if(slider == &volSlider)
    {
        player->setGain(slider->getValue());
    }

    if(slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }
    if(slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue());
    }
}
