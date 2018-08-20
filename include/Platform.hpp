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
#include <map>
#include <fstream>

#include <utils.hpp>

#pragma once

namespace AstroData {

// Exception: cannot read from a configuration/input file
class FileError : public std::exception {
public:
  explicit FileError(const std::string & message);
  ~FileError() noexcept;

  const char * what() const noexcept;

private:
  std::string message;
};

// Memory padding
typedef std::map<std::string, unsigned int> paddingConf;
// Vector unit width
typedef std::map<std::string, unsigned int> vectorWidthConf;

// Read configuration files
void readPaddingConf(paddingConf & padding, const std::string & paddingFilename);
void readVectorWidthConf(vectorWidthConf & vectorWidth, const std::string & vectorFilename);

} // AstroData

