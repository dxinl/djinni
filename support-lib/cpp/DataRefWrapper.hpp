/**
 * Copyright 2023 Bytedance, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "conf.hpp"
#include <cstdint>

#if defined(DISABLE_DATA_REF)
#include <vector>
#else
#include "DataRef.hpp"
#endif

namespace djinni {

#if defined (DISABLE_DATA_REF)

using DataRefWrapper = std::vector<uint8_t>;

static const uint8_t *DataRefBuf(const DataRefWrapper &dr) { return dr.data(); }
static size_t DataRefLen(const DataRefWrapper &dr) { return dr.size(); }

#else

using DataRefWrapper = djinni::DataRef;

static const uint8_t *DataRefBuf(const DataRefWrapper &dr) { return dr.buf(); }
static size_t DataRefLen(const DataRefWrapper &dr) { return dr.len(); }

#endif //DISABLE_DATA_REF

} // namespace djinni