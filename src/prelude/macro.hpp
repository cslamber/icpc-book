#define L1(...) [&](const auto& it) { return __VA_ARGS__; }
#define L2(...) [&](const auto& it1, const auto& itr) { return __VA_ARGS__; }
