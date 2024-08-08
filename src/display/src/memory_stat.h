#ifndef __MEMORY_STAT_H__
#define __MEMORY_STAT_H__

#include "monitor_inter.h"

#include "monitor_info.grpc.pb.h"
#include "monitor_info.pb.h"

namespace monitor {
    class MemoryModel : public MonitorInterModel {
        Q_OBJECT
    public:
        explicit MemoryModel(QObject *parent = nullptr);
        virtual ~MemoryModel() {};

        // 获取表中数据
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
        // 获取表头数据
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

        int rowCount(const QModelIndex &parent = QModelIndex()) const override;  // 返回行数
        int columnCount(const QModelIndex &parent = QModelIndex()) const override; // 返回列数

        void UpdateMonitorInfo(const monitor::proto::MonitorInfo &monitor_info);  // 更新监控信息

    private:
        std::vector<QVariant> insertOneMemoryInfo(const monitor::proto::MemoryInfo &mem_info);
        
        std::vector<std::vector<QVariant>> m_monitor_data; // 监控数据
        QStringList m_header; // 表头

        enum MemoryStat{
            USED_PERCENT = 0,
            TOTAL,
            FREE,
            AVAIL,
            BUFFERS,
            CACHED,
            SWAP_CACHED,
            ACTIVE,
            INACTIVE,
            ACTIVE_ANON,
            INACTIVE_ANON,
            DIRTY,
            WRITEBACK,
            ANON_PAGES,
            MAPPED,
            KRECLAIMABLE,
            SRECLAIMABLE,
            SUNRECLAIM,
            COLUMN_MAX
        };
    };
}

#endif // __MEMORY_STAT_H__