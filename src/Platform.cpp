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

#include <Platform.hpp>

namespace AstroData {

FileError::FileError(const std::string & message) : message(message) {}

FileError::~FileError() noexcept {}

const char * FileError::what() const noexcept {
  return message.c_str();
}

void readPaddingConf(paddingConf & padding, const std::string & paddingFilename) {
  std::string temp;
  std::ifstream paddingFile(paddingFilename);

  if ( !paddingFile ) {
    throw FileError("ERROR: impossible to open padding file \"" + paddingFilename + "\"");
  }
  while ( ! paddingFile.eof() ) {
    unsigned int middle = 0;

    std::getline(paddingFile, temp);
    if ( ! std::isalpha(temp[0]) ) {
      continue;
    }
    middle = temp.find(" ");
    padding.insert(std::make_pair(temp.substr(0, middle), isa::utils::castToType<std::string, unsigned int>(temp.substr(middle + 1))));
  }
}

void readVectorWidthConf(vectorWidthConf & vectorWidth, const std::string & vectorFilename) {
  std::string temp;
  std::ifstream vectorFile(vectorFilename);

  if ( !vectorFile ) {
    throw FileError("ERROR: impossible to open vector file \"" + vectorFilename + "\"");
  }
  while ( ! vectorFile.eof() ) {
    unsigned int middle = 0;

    std::getline(vectorFile, temp);
    if ( ! std::isalpha(temp[0]) ) {
      continue;
    }
    middle = temp.find(" ");
    vectorWidth.insert(std::make_pair(temp.substr(0, middle), isa::utils::castToType<std::string, unsigned int>(temp.substr(middle + 1))));
  }
}

} // AstroData

