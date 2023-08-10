#include "MainComponent.h"

//==============================================================================

MainComponent::MainComponent()
: fChooser {"Load an Audio File"}

{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (0, 2);
    }
    
    addAndMakeVisible(deckGUI1);
    addAndMakeVisible(deckGUI2);

}


MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================


void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    player1.getNextAudioBlock(bufferToFill);
}

//void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
//{
//    auto* leftChan = bufferToFill.buffer->getWritePointer(0,
//                                                          bufferToFill.startSample);
//    auto* rightChan = bufferToFill.buffer->getWritePointer(0,
//                                                          bufferToFill.startSample);
//    for (auto i=0; i < bufferToFill.numSamples ; ++i)
//    {
////        double sample = rand.nextDouble()* 0.25;
////        double sample = fmod(phase, 0.2);
//        double sample = sin(phase) * 0.1;
//
//        leftChan[i] = sample;
//        rightChan[i] = sample;
//
//        phase += dphase;
//
//
//    }
//      bufferToFill.clearActiveBufferRegion();
//}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
    
    player1.releaseResources();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}
    // You can add your drawing code here!
    
//    g.setFont (20.0f);
//    g.setColour (juce::Colours::white);
//
//    int rowH = getHeight() / 5;
//    juce::Rectangle<int> textArea(0, 0, getWidth(), rowH);
//    g.drawText ("Hello from LA", textArea, juce::Justification::centred, true);
//}

void MainComponent::resized()
{
    deckGUI1.setBounds(0, 0, getWidth()/2,getHeight());
    deckGUI2.setBounds(getWidth()/2, 0, getWidth()/2,getHeight());

}


