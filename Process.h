/*
 * SPDX-License-Identifier: GPL-2.0
 *
 * Copyright (c) 2018 Intel Corporation
 *
 * Authors: Fengguang Wu <fengguang.wu@intel.com>
 *          Yao Yuan <yuan.yao@intel.com>
 */

#ifndef AEP_PROCESS_H
#define AEP_PROCESS_H

#include <memory>
#include <vector>
#include <unordered_map>

#include "ProcPid.h"
#include "ProcMaps.h"
#include "ProcStatus.h"
#include "Option.h"
#include "PidContext.h"

class EPTMigrate;
typedef std::vector<std::shared_ptr<EPTMigrate>> IdleRanges;

class Process
{
  public:
    int load(pid_t n);
    int split_ranges();
    IdleRanges& get_ranges() { return idle_ranges; }
    void set_policy(Policy* pol);
    bool match_policy(Policy& policy);
    Policy* match_policies(PolicySet& policies);

  private:
    void add_range(unsigned long start, unsigned long end);

  public:
    pid_t      pid;
    Policy     policy;
    ProcStatus proc_status;
    ProcMaps   proc_maps;
    IdleRanges idle_ranges;
    PidContext context;
};

typedef std::unordered_map<pid_t, std::shared_ptr<Process>> ProcessHash;

class ProcessCollection
{
  public:
    int collect();
    int collect(PolicySet& policies);
    ProcessHash& get_proccesses() { return proccess_hash; }
    void dump();

  private:
    ProcPid pids;
    ProcessHash proccess_hash;
};

#endif
// vim:set ts=2 sw=2 et:
