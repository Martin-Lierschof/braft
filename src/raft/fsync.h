// libraft - Quorum-based replication of states across machines.
// Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved

// Author: Zhangyi Chen (chenzhangyi01@baidu.com)
// Date: 2016/02/23 17:51:13

#ifndef  PUBLIC_RAFT_FSYNC_H
#define  PUBLIC_RAFT_FSYNC_H

#include <unistd.h>
#include <gflags/gflags.h>
#include "raft/storage.h"

namespace raft {

DECLARE_bool(raft_use_fsync_rather_than_fdatasync);

inline int raft_fsync(int fd) {
    int ret;
    if (FLAGS_raft_use_fsync_rather_than_fdatasync) {
        do {
            ret = fsync(fd);
        } while (ret != 0 && errno == EINTR);
    } else {
        do {
            ret = fdatasync(fd);
        } while (ret != 0 && errno == EINTR);
    }
    return ret;
}

inline bool raft_sync_meta() {
    return FLAGS_raft_sync || FLAGS_raft_sync_meta;
}

}  // namespace raft

#endif  //PUBLIC_RAFT_FSYNC_H
