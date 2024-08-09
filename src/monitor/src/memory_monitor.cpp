#include <string>
#include <vector>
#include "memory_monitor.h"
#include "read_flie.h"

namespace monitor {
    constexpr float KBToGB = 1000 * 1000;

    MemoryMonitor::MemoryMonitor()
    {
    }

    void MemoryMonitor::updateOnce(monitor::proto::MonitorInfo *monitorInfo)
    {
        ReadFile mem_file(std::string("/proc/meminfo"));
        MenInfo mem_info;
        std::vector<std::string> mem_datas;

        while (mem_file.readLine(&mem_datas))
        {
            if (mem_datas[0] == "MemToal:"){
                mem_info.total = std::stoll(mem_datas[1]);
            } else if (mem_datas[0] == "MemFree:"){
                mem_info.free = std::stoll(mem_datas[1]);
            } else if (mem_datas[0] == "MemAvailable:"){
                mem_info.avail = std::stoll(mem_datas[1]);
            } else if (mem_datas[0] == "Buffers:"){
                mem_info.buffers = std::stoll(mem_datas[1]);
            } else if (mem_datas[0] == "Cached:"){
                mem_info.cached = std::stoll(mem_datas[1]);
            } else if (mem_datas[0] == "SwapCached:"){
                mem_info.swap_cached = std::stoll(mem_datas[1]);
            } else if (mem_datas[0] == "Active:"){
                mem_info.active = std::stoll(mem_datas[1]);
            } else if (mem_datas[0] == "Inactive:"){
                mem_info.in_active = std::stoll(mem_datas[1]);
            } else if (mem_datas[0] == "Active(anon):"){
                mem_info.active_anon = std::stoll(mem_datas[1]);
            } else if (mem_datas[0] == "Inactive(anon):"){
                mem_info.inactive_anon = std::stoll(mem_datas[1]);
            } else if (mem_datas[0] == "Active(file):"){
                mem_info.active_file = std::stoll(mem_datas[1]);
            } else if (mem_datas[0] == "Inactive(file):"){
                mem_info.inactive_file = std::stoll(mem_datas[1]);
            } else if (mem_datas[0] == "Dirty:"){
                mem_info.dirty = std::stoll(mem_datas[1]);
            } else if (mem_datas[0] == "Writeback:"){
                mem_info.writeback = std::stoll(mem_datas[1]);
            } else if (mem_datas[0] == "AnonPages:"){
                mem_info.anon_pages = std::stoll(mem_datas[1]);
            } else if (mem_datas[0] == "Mapped:"){
                mem_info.mapped = std::stoll(mem_datas[1]);
            } else if (mem_datas[0] == "KReclaimable:"){
                mem_info.kReclaimable = std::stoll(mem_datas[1]);
            } else if (mem_datas[0] == "SReclaimable:"){
                mem_info.sReclaimable = std::stoll(mem_datas[1]);
            } else if (mem_datas[0] == "SUnreclaim:"){
                mem_info.sUnreclaim = std::stoll(mem_datas[1]);
            }

            mem_datas.clear();
        }
        
        auto mem_msg = monitorInfo->mutable_mem_info();

        mem_msg->set_total(mem_info.total / KBToGB);
        mem_msg->set_free(mem_info.free / KBToGB);
        mem_msg->set_avail(mem_info.avail / KBToGB);
        mem_msg->set_buffers(mem_info.buffers / KBToGB);
        mem_msg->set_cached(mem_info.cached / KBToGB);
        mem_msg->set_swap_cached(mem_info.swap_cached / KBToGB);
        mem_msg->set_active(mem_info.active / KBToGB);
        mem_msg->set_inactive(mem_info.in_active / KBToGB);
        mem_msg->set_active_anon(mem_info.active_anon / KBToGB);
        mem_msg->set_inactive_anon(mem_info.inactive_anon / KBToGB);
        mem_msg->set_active_file(mem_info.active_file / KBToGB);
        mem_msg->set_inactive_file(mem_info.inactive_file / KBToGB);
        mem_msg->set_dirty(mem_info.dirty / KBToGB);
        mem_msg->set_writeback(mem_info.writeback / KBToGB);
        mem_msg->set_anon_pages(mem_info.anon_pages / KBToGB);
        mem_msg->set_mapped(mem_info.mapped / KBToGB);
        mem_msg->set_kreclaimable(mem_info.kReclaimable / KBToGB);
        mem_msg->set_sreclaimable(mem_info.sReclaimable / KBToGB);
        mem_msg->set_sunreclaim(mem_info.sUnreclaim / KBToGB);
        // 计算内存使用率 avail更准确表示可用内存
        mem_msg->set_used_percent((mem_info.total - mem_info.avail) / mem_info.total * 100.00);
    }
}

/* /proc/meminfo
MemTotal:        7963004 kB
MemFree:         3738036 kB
MemAvailable:    5125116 kB
Buffers:            5292 kB
Cached:          1407864 kB
SwapCached:            0 kB
Active:           287308 kB
Inactive:        3194288 kB
Active(anon):       2188 kB
Inactive(anon):  2071136 kB
Active(file):     285120 kB
Inactive(file):  1123152 kB
Unevictable:           0 kB
Mlocked:               0 kB
SwapTotal:       2097152 kB
SwapFree:        2097152 kB
Dirty:                 0 kB
Writeback:             0 kB
AnonPages:       2000672 kB
Mapped:           451688 kB
Shmem:              4884 kB
KReclaimable:     278736 kB
Slab:             379412 kB
SReclaimable:     278736 kB
SUnreclaim:       100676 kB
KernelStack:       11728 kB
PageTables:        27128 kB
NFS_Unstable:          0 kB
Bounce:                0 kB
WritebackTmp:          0 kB
CommitLimit:     6078652 kB
Committed_AS:    4103340 kB
VmallocTotal:   34359738367 kB
VmallocUsed:       33244 kB
VmallocChunk:          0 kB
Percpu:             7776 kB
AnonHugePages:    497664 kB
ShmemHugePages:        0 kB
ShmemPmdMapped:        0 kB
FileHugePages:         0 kB
FilePmdMapped:         0 kB
HugePages_Total:       0
HugePages_Free:        0
HugePages_Rsvd:        0
HugePages_Surp:        0
Hugepagesize:       2048 kB
Hugetlb:               0 kB
DirectMap4k:       29696 kB
DirectMap2M:     5040128 kB
DirectMap1G:    11534336 kB
*/