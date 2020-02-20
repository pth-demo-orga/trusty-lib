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

#include <sys/mman.h>

#include <lk/err_ptr.h>
#include <stddef.h>
#include <stdint.h>
#include <trusty_syscalls.h>

void* mmap(void* uaddr,
           size_t size,
           int prot,
           int flags,
           int handle,
           off_t offset) {
    void* result;

    if (offset != 0) {
        return MAP_FAILED;
    }

    /*
     * or the flags together for now since the syscall doesn't have enough
     * arguments and now that we have real mappable handles, we have to dispatch
     * on the flags to switch between regions and handles
     */
    result = (void*)_trusty_mmap(uaddr, size, (uint32_t)prot | flags,
                                 (int32_t)handle);
    if (IS_ERR(result)) {
        return MAP_FAILED;
    }
    return result;
}

int munmap(void* uaddr, size_t size) {
    return _trusty_munmap(uaddr, size);
}

int prepare_dma(void* uaddr,
                uint32_t size,
                uint32_t flags,
                struct dma_pmem* pmem) {
    return _trusty_prepare_dma(uaddr, size, flags, pmem);
}

int finish_dma(void* uaddr, uint32_t size, uint32_t flags) {
    return _trusty_finish_dma(uaddr, size, flags);
}
