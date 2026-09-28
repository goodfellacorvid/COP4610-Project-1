#pragma once

#include <sys/types.h>

void init_bg_jobs();
void add_bg_job(pid_t pid, const char *cmd);
void check_bg_jobs();