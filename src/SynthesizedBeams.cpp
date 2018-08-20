// Copyright 2017 Netherlands Institute for Radio Astronomy (ASTRON)
// Copyright 2017 Netherlands eScience Center
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <fstream>

#include <SynthesizedBeams.hpp>

namespace AstroData {

void generateBeamMapping(const AstroData::Observation & observation, std::vector<unsigned int> & beamMapping, const unsigned int padding, const bool subbanding) {
  for ( unsigned int beam = 0; beam < observation.getNrSynthesizedBeams(); beam++ ) {
    if ( subbanding) {
      for ( unsigned int subband = 0; subband < observation.getNrSubbands(); subband++ ) {
        beamMapping[(beam * observation.getNrSubbands(padding / sizeof(unsigned int))) + subband] = beam % observation.getNrBeams();
      }
    } else {
      for ( unsigned int channel = 0; channel < observation.getNrChannels(); channel++ ) {
        beamMapping[(beam * observation.getNrChannels(padding / sizeof(unsigned int))) + channel] = beam % observation.getNrBeams();
      }
    }
  }
}

void readBeamMapping(const AstroData::Observation & observation, const std::string & inputFilename, std::vector<unsigned int> & beamMapping, const unsigned int padding, const bool subbanding) {
  std::ifstream inputFile;

  inputFile.open(inputFilename);
  if ( !inputFile ) {
    throw FileError("Impossible to open " + inputFilename);
  }
  for ( unsigned int sBeam = 0; sBeam < observation.getNrSynthesizedBeams(); sBeam++ ) {
    if ( subbanding ) {
      for ( unsigned int subband = 0; subband < observation.getNrSubbands(); subband++ ) {
        inputFile >> beamMapping[(sBeam * observation.getNrSubbands(padding / sizeof(unsigned int))) + subband];
      }
    } else {
      for ( unsigned int channel = 0; channel < observation.getNrChannels(); channel++ ) {
        inputFile >> beamMapping[(sBeam * observation.getNrChannels(padding / sizeof(unsigned int))) + channel];
      }
    }
  }
  inputFile.close();
}

} // AstroData

