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

/* Augment time.h with trusty-specific functions. */
#include_next <time.h>

#include <lk/compiler.h>
#include <stdint.h>

__BEGIN_CDECLS

/* Prefixed with trusty_ because the signatures do not match POSIX. */
int trusty_gettime(clockid_t clock_id, int64_t* time);
int trusty_nanosleep(clockid_t clock_id, uint32_t flags, uint64_t sleep_time);

__END_CDECLS
