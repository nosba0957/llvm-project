//===-- sanitizer_coverage_win_runtime_thunk.cpp --------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file defines things that need to be present in the application modules
// to interact with Sanitizer Coverage, when it is included in a dll.
//
//===----------------------------------------------------------------------===//
#if defined(SANITIZER_DYNAMIC_RUNTIME_THUNK) || \
    defined(SANITIZER_STATIC_RUNTIME_THUNK)
#  define SANITIZER_IMPORT_INTERFACE 1
#  include "sanitizer_win_defs.h"
#  include "sanitizer_win_thunk_interception.h"
// Define weak alias for all weak functions imported from sanitizer coverage.
#  define INTERFACE_FUNCTION(Name)
#  define INTERFACE_WEAK_FUNCTION(Name) REGISTER_WEAK_FUNCTION(Name)
#  include "sanitizer_coverage_interface.inc"
#endif  // defined(SANITIZER_DYNAMIC_RUNTIME_THUNK) ||
        // defined(SANITIZER_STATIC_RUNTIME_THUNK)

namespace __sanitizer {
// Add one, otherwise unused, external symbol to this object file so that the
// Visual C++ linker includes it and reads the .drective section.
void ForceWholeArchiveIncludeForSanCov() {}
}  // namespace __sanitizer
