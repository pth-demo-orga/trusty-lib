/*
 * Copyright (C) 2018 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

/* Augment sys/mman.h with trusty-specific functions. */
#include_next <sys/mman.h>

#include <stdint.h>
#include <uapi/mm.h>

/* Don't use convenience macros here, it will polute the namespace. */
#ifdef __cplusplus
extern "C" {
#endif

/* Trusty specific. */
long prepare_dma(void* uaddr,
                 uint32_t size,
                 uint32_t flags,
                 struct dma_pmem* pmem);
long finish_dma(void* uaddr, uint32_t size, uint32_t flags);

#ifdef __cplusplus
}
#endif
