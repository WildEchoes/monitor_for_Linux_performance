#ifndef __MEMORY_MONITOR_H__
#define __MEMORY_MONITOR_H__

#include "monitor_inter_.h"

namespace monitor {
    class MemoryMonitor : public MonitorInterface {
    public:
        struct MenInfo {
            int64_t total;  // 总内存 kB
            int64_t free;   // 空闲内存
            int64_t avail;  // 可用内存
            int64_t buffers;   // 块设备所占用的缓存页
            int64_t cached;    // 页缓存
            int64_t swap_cached; // 交换缓存
            int64_t active;     // active anon和active file
            int64_t in_active;  // inactive anon和inactive file
            int64_t active_anon;
            int64_t inactive_anon;
            int64_t active_file;
            int64_t inactive_file;
            int64_t dirty;      // 需要写入磁盘缓存数据
            int64_t writeback;  // 正在写回磁盘的数据
            int64_t anon_pages; // 未映射页的内存的大小
            int64_t mapped;     // 设备和文件等映射的大小
            int64_t kReclaimable; // 可回收的内存
            int64_t sReclaimable; // slab可回收的内存 slab是linux内核的一种内存分配器
            int64_t sUnreclaim;   // slab不可回收的内存
        };

        MemoryMonitor();
        virtual ~MemoryMonitor() {};

        void updateOnce(monitor::proto::MonitorInfo* monitorInfo) override;
        void stop() override {};
    
    private:

    };
}

#endif // __MEMORY_MONITOR_H__