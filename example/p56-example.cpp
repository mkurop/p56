//
// Created by marcin on 29.09.18.
//

#include <P56.h>
#include <AudioFile.h>

int main(int argc, char *argv[]) {

  AudioFile<float> audioFile;

  audioFile.load("../../data/speech.wav");

  t2r::P56 p56(audioFile.getSampleRate(), 16.);

  float *speech = new float[audioFile.getNumSamplesPerChannel()];

  for (int i = 0; i < audioFile.getNumSamplesPerChannel(); i++){
    speech[i] = audioFile.samples[0][i];
  }

  p56.compute(speech, audioFile.getNumSamplesPerChannel());

  delete speech;

  std::cout << "Active speech RMS level: " << p56.getLev() <<std::endl;
  std::cout << "Active speech factor: " << p56.getAf() << std::endl;
  if ((std::abs(p56.getLev() - 0.0061091) < 1e-4) && (std::abs(p56.getAf() - 0.875316) < 1e-3)) {
    std::cout << "SUCCESS (checked against VOICEBOX activlev.m function; not exact but resonably similar)";
    return 0;
  } else {
    std::cout << "ERROR";
    std::cout << p56.getLev() << " vs." << 0.0061091 << ";" << p56.getAf() << " vs. " << 0.87316;
    return 1;
  }
}

