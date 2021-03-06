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

#include <lk/compiler.h>
#include <trusty_ipc.h>

__BEGIN_CDECLS

/**
 * struct tipc_hset - structure to wrap underlying handle set handle
 * @handle:  handle of underlying handle set
 */
struct tipc_hset {
    handle_t handle;
};

/**
 * tipc_hset_init() - initialize specified tipc handles set
 * @hset: pointer to &struct tipc_hset to initialize
 *
 * Creates a new handle set and store it's handle in @handle field of
 * wrapper structure
 *
 * Return: 0 on success, a negative error code otherwise
 */
int tipc_hset_init(struct tipc_hset* hset);

__END_CDECLS
