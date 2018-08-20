// Copyright 2017 Netherlands Institute for Radio Astronomy (ASTRON)
// Copyright 2017 Netherlands eScience Center
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>

#include "Observation.hpp"


#pragma once

namespace AstroData {

template< typename T > void generatePulsar(const unsigned int period, const unsigned int width, const float DM, const AstroData::Observation & observation, const unsigned int padding, std::vector< std::vector< T > * > & data, const bool random = false);
template< typename T > void generateSinglePulse(const unsigned int width, const float DM, const AstroData::Observation & observation, const unsigned int padding, std::vector< std::vector< T > * > & data, const uint8_t inputBits, const bool random = false);

// Implementations
template< typename T > void generatePulsar(const unsigned int period, const unsigned int width, const float DM, const AstroData::Observation & observation, const unsigned int padding, std::vector< std::vector< T > * > & data, const bool random) {
  std::srand(std::time(0));
  // Generate the  "noise"
  for ( unsigned int batch = 0; batch < observation.getNrBatches(); batch++ ) {
    data[batch] = new std::vector< T >(observation.getNrChannels() * observation.getNrSamplesPerBatch(false, padding / sizeof(T)));
    if ( random ) {
      for ( unsigned int channel = 0; channel < observation.getNrChannels(); channel++ ) {
        for ( unsigned int sample = 0; sample < observation.getNrSamplesPerBatch(); sample++ ) {
          data[batch]->at((channel * observation.getNrSamplesPerBatch(false, padding / sizeof(T))) + sample) = static_cast< T >(std::rand() % 25);
        }
      }
    } else {
      std::fill(data[batch]->begin(), data[batch]->end(), static_cast< T >(8));
    }
  }
  // Generate the pulsar
  float inverseHighFreq = 1.0f / (observation.getMaxFreq() * observation.getMaxFreq());
  float kDM = 4148.808f * DM;
  for ( unsigned int channel = 0; channel < observation.getNrChannels(); channel++ ) {
    float inverseFreq = 1.0f / ((observation.getMinFreq() + (channel * observation.getChannelBandwidth())) * (observation.getMinFreq() + (channel * observation.getChannelBandwidth())));
    float delta = kDM * (inverseFreq - inverseHighFreq);
    unsigned int shift = static_cast< unsigned int >(delta * observation.getNrSamplesPerBatch());

    for ( unsigned int sample = shift; sample < observation.getNrBatches() * observation.getNrSamplesPerBatch(); sample += period ) {
      for ( unsigned int i = 0; i < width; i++ ) {
        if ( sample + i >= observation.getNrBatches() * observation.getNrSamplesPerBatch() ) {
        break;
        }
        unsigned int batch = (sample + i) / observation.getNrSamplesPerBatch();
        unsigned int internalSample = (sample + i) % observation.getNrSamplesPerBatch();

        if ( random ) {
          data[batch]->at((channel * observation.getNrSamplesPerBatch(false, padding / sizeof(T))) + internalSample) = static_cast< T >(std::rand() % 128);
        } else {
          data[batch]->at((channel * observation.getNrSamplesPerBatch(false, padding / sizeof(T))) + internalSample) = static_cast< T >(42);
        }
      }
    }
  }
}

template< typename T > void generateSinglePulse(const unsigned int width, const float DM, const AstroData::Observation & observation, const unsigned int padding, std::vector< std::vector< T > * > & data, const uint8_t inputBits, const bool random) {
  std::srand(std::time(0));
  // Generate the  "noise"
  for ( unsigned int batch = 0; batch < observation.getNrBatches(); batch++ ) {
    if ( inputBits >= 8 ) {
      data[batch] = new std::vector< T >(observation.getNrChannels() * observation.getNrSamplesPerBatch(false, padding / sizeof(T)));
    } else {
      data[batch] = new std::vector< T >(observation.getNrChannels() * isa::utils::pad(observation.getNrSamplesPerBatch() / (8 / inputBits), padding / sizeof(T)));
    }
    if ( random ) {
      for ( unsigned int channel = 0; channel < observation.getNrChannels(); channel++ ) {
        for ( unsigned int sample = 0; sample < observation.getNrSamplesPerBatch(); sample++ ) {
          if ( inputBits >= 8 ) {
            data[batch]->at((channel * observation.getNrSamplesPerBatch(false, padding / sizeof(T))) + sample) = static_cast< T >(std::rand() % 25);
          } else {
            unsigned int byte = sample / (8 / inputBits);
            uint8_t firstBit = (sample % (8 / inputBits)) * inputBits;
            uint8_t value = static_cast< unsigned int >(std::rand() % (inputBits - 1));
            unsigned char buffer = data[batch]->at((channel * isa::utils::pad(observation.getNrSamplesPerBatch() / (8 / inputBits), padding / sizeof(T))) + byte);

            for ( uint8_t bit = 0; bit < inputBits; bit++ ) {
              isa::utils::setBit(buffer, isa::utils::getBit(value, bit), firstBit + bit);
            }
            data[batch]->at((channel * isa::utils::pad(observation.getNrSamplesPerBatch() / (8 / inputBits), padding / sizeof(T))) + byte) = buffer;
          }
        }
      }
    } else {
      if ( inputBits >= 8 ) {
        std::fill(data[batch]->begin(), data[batch]->end(), static_cast< T >(8));
      } else {
        std::fill(data[batch]->begin(), data[batch]->end(), static_cast< T >(0));
      }
    }
  }
  // Generate the pulse
  unsigned int batch = 0;
  unsigned int sample = 0;
  float inverseHighFreq = 1.0f / std::pow(observation.getMaxFreq(), 2.0f);
  float kDM = 4148.808f * DM;

  if ( random ) {
    batch = std::rand() % (observation.getNrBatches() / 2);
    sample = std::rand() % (observation.getNrSamplesPerBatch() - width);
  } else {
    batch = observation.getNrBatches() / 2;
    sample = observation.getNrSamplesPerBatch() / 2;
  }

  for ( unsigned int channel = 0; channel < observation.getNrChannels(); channel++ ) {
    float inverseFreq = 1.0f / std::pow(observation.getMinFreq() + (channel * observation.getChannelBandwidth()), 2.0f);
    unsigned int shift = static_cast< unsigned int >(kDM * (inverseFreq - inverseHighFreq) * observation.getNrSamplesPerBatch());

    for ( unsigned int i = 0; i < width; i++ ) {
      if ( batch + ((sample + i + shift) / observation.getNrSamplesPerBatch()) >= observation.getNrBatches() ) {
      break;
      }

      if ( random ) {
        if ( inputBits >= 8 ) {
          data[batch + ((sample + i + shift) / observation.getNrSamplesPerBatch())]->at((channel * observation.getNrSamplesPerBatch(false, padding / sizeof(T))) + (sample + i + shift)) = static_cast< T >(std::rand() % 256);
        } else {
          uint8_t value = static_cast< unsigned int >(std::rand() % inputBits);
          unsigned int byte = ((sample + i + shift) % observation.getNrSamplesPerBatch()) / (8 / inputBits);
          uint8_t firstBit = (((sample + i + shift) % observation.getNrSamplesPerBatch()) % (8 / inputBits)) * inputBits;
          unsigned char buffer = data[batch + ((sample + i + shift) / observation.getNrSamplesPerBatch())]->at((channel * isa::utils::pad(observation.getNrSamplesPerBatch() / (8 / inputBits), padding / sizeof(T))) + byte);

          for ( uint8_t bit = 0; bit < inputBits; bit++ ) {
            isa::utils::setBit(buffer, isa::utils::getBit(value, bit), firstBit + bit);
          }
          data[batch + ((sample + i + shift) / observation.getNrSamplesPerBatch())]->at((channel * isa::utils::pad(observation.getNrSamplesPerBatch() / (8 / inputBits), padding / sizeof(T))) + byte) = buffer;
        }
      } else {
        if ( inputBits >= 8 ) {
          data[batch + ((sample + i + shift) / observation.getNrSamplesPerBatch())]->at((channel * observation.getNrSamplesPerBatch(false, padding / sizeof(T))) + ((sample + i + shift) % observation.getNrSamplesPerBatch())) = static_cast< T >(42);
        } else {
          unsigned int byte = ((sample + i + shift) % observation.getNrSamplesPerBatch()) / (8 / inputBits);
          uint8_t firstBit = (((sample + i + shift) % observation.getNrSamplesPerBatch()) % (8 / inputBits)) * inputBits;
          unsigned char buffer = 0;

          buffer = data[batch + ((sample + i + shift) / observation.getNrSamplesPerBatch())]->at((channel * isa::utils::pad(observation.getNrSamplesPerBatch() / (8 / inputBits), padding / sizeof(T))) + byte);

          for ( uint8_t bit = 0; bit < inputBits; bit++ ) {
            isa::utils::setBit(buffer, isa::utils::getBit(inputBits, bit), firstBit + bit);
          }
          data[batch + ((sample + i + shift) / observation.getNrSamplesPerBatch())]->at((channel * isa::utils::pad(observation.getNrSamplesPerBatch() / (8 / inputBits), padding / sizeof(T))) + byte) = buffer;
        }
      }
    }
  }
}

} // AstroData

