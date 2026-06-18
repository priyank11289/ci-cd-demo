#include "math_utils.h"

int add(int a, int b) { return a + b; }

bool passes_exam(int score, bool has_extra_credit)
{
    return score >= 50 && has_extra_credit;
}
