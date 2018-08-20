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

#include <string>
#include <limits>

#include <utils.hpp>


#pragma once

namespace AstroData {

class Observation {
public:
  Observation();
  ~Observation();

  // General observation parameters
  unsigned int getNrBatches() const;
  unsigned int getNrDelayBatches(const bool subbanding = false) const;
  unsigned int getNrStations(const unsigned int padding = 0) const;
  unsigned int getNrBeams(const unsigned int padding = 0) const;
  unsigned int getNrSynthesizedBeams(const unsigned int padding = 0) const;
  float getSamplingTime() const;
  unsigned int getNrSamplesPerBatch(const bool subbanding = false, const unsigned int padding = 0) const;
  unsigned int getNrSamplesPerDispersedBatch(const bool subbanding = false, const unsigned int padding = 0) const;
  // Frequency parameters
  unsigned int getNrSubbands(const unsigned int padding = 0) const;
  unsigned int getNrChannels(const unsigned int padding = 0) const;
  unsigned int getNrChannelsPerSubband() const;
  unsigned int getNrZappedChannels() const;
  float getSubbandMinFreq() const;
  float getSubbandMaxFreq() const;
  float getSubbandBandwidth() const;
  float getMinFreq() const;
  float getMaxFreq() const;
  float getChannelBandwidth() const;
  // Dispersion measures
  unsigned int getNrDMs(const bool subbanding = false, const unsigned int padding = 0) const;
  float getFirstDM(const bool subbanding = false) const;
  float getLastDM(const bool subbanding = false) const;
  float getDMStep(const bool subbanding = false) const;
  // Periods
  unsigned int getNrPeriods(const unsigned int padding = 0) const;
  unsigned int getFirstPeriod() const;
  unsigned int getLastPeriod() const;
  unsigned int getPeriodStep() const;
  unsigned int getNrBins(const unsigned int padding = 0) const;

  // General observation parameters
  void setNrBatches(const unsigned int batches);
  void setNrDelayBatches(const unsigned int batches, const bool subbanding = false);
  void setNrStations(const unsigned int stations);
  void setNrBeams(const unsigned int beams);
  void setNrSynthesizedBeams(const unsigned int beams);
  void setSamplingTime(const float sampling);
  void setNrSamplesPerBatch(const unsigned int samples, const bool subbanding = false);
  void setNrSamplesPerDispersedBatch(const unsigned int samples, const bool subbanding = false);
  // Frequency parameters
  void setFrequencyRange(const unsigned int subbands, const unsigned int channels, const float baseFrequency, const float bandwidth);
  void setNrZappedChannels(const unsigned int zappedChannels);
  // Dispersion measures
  void setDMRange(const unsigned int dms, const float baseDM, const float step, const bool subbanding = false);
  // Periods
  void setPeriodRange(const unsigned int periods, const unsigned int basePeriod, const unsigned int step);
  void setNrBins(const unsigned int bins);

private:
  unsigned int nrBatches;
  unsigned int nrStations;
  unsigned int nrBeams;
  unsigned int nrSynthesizedBeams;
  float samplingTime;
  unsigned int nrSamplesPerBatch;
  unsigned int nrSamplesPerBatch_subbanding;
  unsigned int nrSamplesPerDispersedBatch;
  unsigned int nrSamplesPerDispersedBatch_subbanding;

  unsigned int nrSubbands;
  unsigned int nrChannels;
  unsigned int nrChannelsPerSubband;
  unsigned int nrZappedChannels;
  float minSubbandFreq;
  float maxSubbandFreq;
  float subbandBandwidth;
  float minChannelFreq;
  float maxChannelFreq;
  float channelBandwidth;

  unsigned int nrDelayBatches;
  unsigned int nrDelayBatches_subbanding;
  unsigned int nrDMs;
  unsigned int nrDMs_subbanding;
  float firstDM;
  float firstDM_subbanding;
  float lastDM;
  float lastDM_subbanding;
  float DMStep;
  float DMStep_subbanding;

  unsigned int nrPeriods;
  unsigned int firstPeriod;
  unsigned int lastPeriod;
  unsigned int periodStep;
  unsigned int nrBins;
};

// Implementations
inline unsigned int Observation::getNrBatches() const {
  return nrBatches;
}

inline float Observation::getSamplingTime() const {
  return samplingTime;
}

inline unsigned int Observation::getNrChannelsPerSubband() const {
  return nrChannelsPerSubband;
}

inline unsigned int Observation::getNrZappedChannels() const {
  return nrZappedChannels;
}

inline float Observation::getSubbandMinFreq() const {
  return minSubbandFreq;
}

inline float Observation::getSubbandMaxFreq() const {
  return maxSubbandFreq;
}

inline float Observation::getSubbandBandwidth() const {
  return subbandBandwidth;
}

inline float Observation::getMinFreq() const {
  return minChannelFreq;
}

inline float Observation::getMaxFreq() const {
  return maxChannelFreq;
}

inline float Observation::getChannelBandwidth() const {
  return channelBandwidth;
}

inline unsigned int Observation::getFirstPeriod() const {
  return firstPeriod;
}

inline unsigned int Observation::getLastPeriod() const {
  return lastPeriod;
}

inline unsigned int Observation::getPeriodStep() const {
  return periodStep;
}

inline void Observation::setNrBatches(const unsigned int batches) {
  nrBatches = batches;
}

inline void Observation::setNrStations(const unsigned int stations) {
  nrStations = stations;
}

inline void Observation::setNrBeams(const unsigned int beams) {
  nrBeams = beams;
}

inline void Observation::setNrSynthesizedBeams(const unsigned int beams) {
  nrSynthesizedBeams = beams;
}

inline void Observation::setSamplingTime(const float sampling) {
  samplingTime = sampling;
}

inline void Observation::setNrZappedChannels(const unsigned int zappedChannels) {
  nrZappedChannels = zappedChannels;
}

inline void Observation::setNrBins(const unsigned int bins) {
  nrBins = bins;
}

} // AstroData

