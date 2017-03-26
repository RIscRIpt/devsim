#pragma once

typedef double engine_time;

class engine;
class flow;
class event;

static constexpr engine_time ALWAYS = -0.0;
static constexpr engine_time NEVER = 1.79769e+308;
