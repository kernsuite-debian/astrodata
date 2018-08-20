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

#include <Observation.hpp>

namespace AstroData {

Observation::Observation() : nrBatches(0), nrStations(0), nrBeams(0), nrSynthesizedBeams(0), samplingTime(0.0f), nrSamplesPerBatch(0), nrSamplesPerBatch_subbanding(0), nrSamplesPerDispersedBatch(0), nrSamplesPerDispersedBatch_subbanding(0), nrSubbands(0), nrChannels(0), nrChannelsPerSubband(0), nrZappedChannels(0), minSubbandFreq(0.0), maxSubbandFreq(0.0), subbandBandwidth(0.0), minChannelFreq(0.0f), maxChannelFreq(0.0f), channelBandwidth(0.0f), nrDelayBatches(0), nrDelayBatches_subbanding(0), nrDMs(0), nrDMs_subbanding(0), firstDM(0.0f), firstDM_subbanding(0.0f), lastDM(0.0f), lastDM_subbanding(0.0f), DMStep(0.0f), DMStep_subbanding(0.0f), nrPeriods(0), firstPeriod(0), lastPeriod(0), periodStep(0), nrBins(0) {}

Observation::~Observation() {}

unsigned int Observation::getNrStations(const unsigned int padding) const {
  if ( padding == 0 ) {
    return nrStations;
  } else {
    return isa::utils::pad(nrStations, padding);
  }
}

unsigned int Observation::getNrBeams(const unsigned int padding) const {
  if ( padding == 0 ) {
    return nrBeams;
  } else {
    return isa::utils::pad(nrBeams, padding);
  }
}

unsigned int Observation::getNrSynthesizedBeams(const unsigned int padding) const {
  if ( padding == 0 ) {
    return nrSynthesizedBeams;
  } else {
    return isa::utils::pad(nrSynthesizedBeams, padding);
  }
}

unsigned int Observation::getNrSamplesPerBatch(const bool subbanding, const unsigned int padding) const {
  if ( padding == 0 ) {
    if ( subbanding ) {
      return nrSamplesPerBatch_subbanding;
    } else {
      return nrSamplesPerBatch;
    }
  } else {
    if ( subbanding ) {
      return isa::utils::pad(nrSamplesPerBatch_subbanding, padding);
    } else {
      return isa::utils::pad(nrSamplesPerBatch, padding);
    }
  }
}

unsigned int Observation::getNrSubbands(const unsigned int padding) const {
  if ( padding == 0 ) {
    return nrSubbands;
  } else {
    return isa::utils::pad(nrSubbands, padding);
  }
}

unsigned int Observation::getNrChannels(const unsigned int padding) const {
  if ( padding == 0 ) {
    return nrChannels;
  } else {
    return isa::utils::pad(nrChannels, padding);
  }
}

unsigned int Observation::getNrSamplesPerDispersedBatch(const bool subbanding, const unsigned int padding) const {
  if ( padding == 0 ) {
    if ( subbanding ) {
      return nrSamplesPerDispersedBatch_subbanding;
    } else {
      return nrSamplesPerDispersedBatch;
    }
  } else {
    if ( subbanding ) {
      return isa::utils::pad(nrSamplesPerDispersedBatch_subbanding, padding);
    } else {
      return isa::utils::pad(nrSamplesPerDispersedBatch, padding);
    }
  }
}

unsigned int Observation::getNrDelayBatches(const bool subbanding) const {
  if ( subbanding ) {
    return nrDelayBatches_subbanding;
  } else {
    return nrDelayBatches;
  }
}

unsigned int Observation::getNrDMs(const bool subbanding, const unsigned int padding) const {
  if ( padding == 0 ) {
    if ( subbanding ) {
      return nrDMs_subbanding;
    } else {
      return nrDMs;
    }
  } else {
    if ( subbanding ) {
      return isa::utils::pad(nrDMs_subbanding, padding);
    } else {
      return isa::utils::pad(nrDMs, padding);
    }
  }
}

float Observation::getFirstDM(const bool subbanding) const {
  if ( subbanding ) {
    return firstDM_subbanding;
  } else {
    return firstDM;
  }
}

float Observation::getLastDM(const bool subbanding) const {
  if ( subbanding ) {
    return lastDM_subbanding;
  } else {
    return lastDM;
  }
}

float Observation::getDMStep(const bool subbanding) const {
  if ( subbanding ) {
    return DMStep_subbanding;
  } else {
    return DMStep;
  }
}

unsigned int Observation::getNrPeriods(const unsigned int padding) const {
  if ( padding == 0 ) {
    return nrPeriods;
  } else {
    return isa::utils::pad(nrPeriods, padding);
  }
}

unsigned int Observation::getNrBins(const unsigned int padding) const {
  if ( padding == 0 ) {
    return nrBins;
  } else {
    return isa::utils::pad(nrBins, padding);
  }
}

void Observation::setFrequencyRange(const unsigned int subbands, const unsigned int channels, const float baseFrequency, const float bandwidth) {
  nrSubbands = subbands;
  nrChannels = channels;
  nrChannelsPerSubband = channels / subbands;
  minSubbandFreq = baseFrequency + ((nrChannelsPerSubband / 2) * bandwidth);
  maxSubbandFreq = baseFrequency + ((nrChannels - (nrChannelsPerSubband / 2)) * bandwidth);
  subbandBandwidth = nrChannelsPerSubband * bandwidth;
  minChannelFreq = baseFrequency;
  maxChannelFreq = baseFrequency + ((channels - 1) * bandwidth);
  channelBandwidth = bandwidth;
}

void Observation::setDMRange(const unsigned int dms, const float baseDM, const float step, const bool subbanding) {
  if ( subbanding ) {
    nrDMs_subbanding = dms;
    firstDM_subbanding = baseDM;
    lastDM_subbanding = baseDM + ((dms - 1) * step);
    DMStep_subbanding = step;
  } else {
    nrDMs = dms;
    firstDM = baseDM;
    lastDM = baseDM + ((dms - 1) * step);
    DMStep = step;
  }
}

void Observation::setPeriodRange(const unsigned int periods, const unsigned int basePeriod, const unsigned int step) {
  nrPeriods = periods;
  firstPeriod = basePeriod;
  lastPeriod = basePeriod + ((periods - 1) * step);
  periodStep = step;
}

void Observation::setNrDelayBatches(const unsigned int batches, const bool subbanding) {
  if ( subbanding ) {
    nrDelayBatches_subbanding = batches;
  } else {
    nrDelayBatches = batches;
  }
}

void Observation::setNrSamplesPerBatch(const unsigned int samples, const bool subbanding) {
  if ( subbanding ) {
    nrSamplesPerBatch_subbanding = samples;
  } else {
    nrSamplesPerBatch = samples;
  }
}

void Observation::setNrSamplesPerDispersedBatch(const unsigned int samples, const bool subbanding) {
  if ( subbanding ) {
    nrSamplesPerDispersedBatch_subbanding = samples;
  } else {
    nrSamplesPerDispersedBatch = samples;
  }
}

} // AstroData

