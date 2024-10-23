#include "core/buffer/prompt.h"


[[gnu::always_inline]]
inline Prompt promptCreate() {
    Prompt prompt = {.len = 0, .start_ptr = nullptr, .end_ptr = nullptr};
    prompt.end_ptr = prompt.start_ptr = charsCreate('\0');
    return prompt;
}
