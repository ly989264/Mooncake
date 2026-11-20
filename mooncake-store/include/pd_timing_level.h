#pragma once

// Parsing of PD_DIAG_LEVEL for the batch-write timing records (inline, so that the
// store library exports nothing new and a standalone test can include the same code).
// The rules match the Python parser in vLLM's pd_diagnostics.diag_level():
//   unset or empty      -> level 3, source "default"
//   exactly "1" "2" "3" -> that level, source "env"
//   anything else       -> level 3, source "invalid" (no trimming: " 2 " is invalid)

#include <cstring>

namespace mooncake {
namespace pd_timing {

struct Level {
    int level;
    const char* source;
};

inline Level ParseDiagLevel(const char* value) {
    if (value == nullptr || value[0] == '\0') return {3, "default"};
    if (std::strcmp(value, "1") == 0) return {1, "env"};
    if (std::strcmp(value, "2") == 0) return {2, "env"};
    if (std::strcmp(value, "3") == 0) return {3, "env"};
    return {3, "invalid"};
}

// MC_PD_TIMING: unset or anything but "0" means on; "0" means off.
inline bool ParseTimingSwitch(const char* value) {
    return !(value != nullptr && std::strcmp(value, "0") == 0);
}

}  // namespace pd_timing
}  // namespace mooncake
