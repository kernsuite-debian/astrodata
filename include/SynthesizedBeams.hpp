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

#include <vector>
#include <string>

#include <Observation.hpp>
#include <Platform.hpp>


#pragma once

namespace AstroData {
// Generate beam mapping
void generateBeamMapping(const AstroData::Observation & observation, std::vector<unsigned int> & beamMapping, const unsigned int padding, const bool subbanding = false);
// Read beam mapping file
void readBeamMapping(const AstroData::Observation & observation, const std::string & inputFilename, std::vector<unsigned int> & beamMapping, const unsigned int padding, const bool subbanding = false);
} // AstroData

