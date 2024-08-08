#ifndef __CPU_STAT_H__
#define __CPU_STAT_H__

#include <QAbstractTableModel>
#include <vector>

#include "monitor_inter.h"

#include "monitor_info.grpc.pb.h"
#include "monitor_info.pb.h"

namespace monitor {
    class CPUStatModel : public MonitorInterModel {
        Q_OBJECT
    public:
        explicit CPUStatModel(QObject *parent = nullptr);
        virtual ~CPUStatModel() {};

        // 获取表中数据
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
        // 获取表头数据
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

        int rowCount(const QModelIndex &parent = QModelIndex()) const override;  // 返回行数
        int columnCount(const QModelIndex &parent = QModelIndex()) const override; // 返回列数

        void UpdateMonitorInfo(const monitor::proto::MonitorInfo &monitor_info);  // 更新监控信息

    private:
        std::vector<QVariant> insertOneCpuStat(const monitor::proto::CpuStat &cpu_stat);
        
        std::vector<std::vector<QVariant>> m_monitor_data; // 监控数据
        QStringList m_header; // 表头
        
        enum CPUStat{
            CPU_NAME = 0,
            CPU_PERCENT,
            USR_PERCENT,
            SYS_PERCENT,
            NICE_PERCENT,
            IDLE_PERCENT,
            IOWAIT_PERCENT,
            IRQ_PERCENT,
            SOFTIRQ_PERCENT,
            COLUMN_MAX
        };
    };
}

#endif