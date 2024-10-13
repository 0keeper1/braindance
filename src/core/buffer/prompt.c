#include "prompt.h"
#include "../errors.h"
#include "./str.h"
#include "./buffer/chars.h"

#include <stdlib.h>

[[gnu::always_inline]]
inline Prompt promptCreate() {
    const Prompt prompt = {.len = 0, .start_ptr = nullptr, .end_ptr = nullptr};
    return prompt;
}
