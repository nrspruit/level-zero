/*
 *
 * Copyright (C) 2021 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "../ze_lib.h"
#ifndef DYNAMIC_LOAD_LOADER
#include "../loader/ze_loader_internal.h"
#endif

namespace ze_lib
{
#ifndef DYNAMIC_LOAD_LOADER
    void context_dynamic_at_exit_destructor()
    {
        if (ze_lib::context) {
            delete ze_lib::context;
            ze_lib::context = nullptr;
        }
        if (loader::context) {
            delete loader::context;
            loader::context = nullptr;
        }
    }
    extern "C" BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
        if (fdwReason == DLL_PROCESS_ATTACH) {
            context = new context_t;
            loader::context = new loader::context_t;
        }
        return TRUE;
    }
#endif
}
