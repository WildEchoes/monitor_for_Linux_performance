#ifndef __CPU_SOFTIRQ_H__
#define __CPU_SOFTIRQ_H__  

#include "monitor_inter.h"

#include "monitor_info.grpc.pb.h"
#include "monitor_info.pb.h"

namespace monitor {
    class CPUSoftIrqModel : public MonitorInterModel {
        Q_OBJECT
    public:
        explicit CPUSoftIrqModel(QObject *parent = nullptr);
        virtual ~CPUSoftIrqModel() {};

        // 获取表中数据
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
        // 获取表头数据
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

        int rowCount(const QModelIndex &parent = QModelIndex()) const override;  // 返回行数
        int columnCount(const QModelIndex &parent = QModelIndex()) const override; // 返回列数

        void UpdateMonitorInfo(const monitor::proto::MonitorInfo &monitor_info);  // 更新监控信息

    private:
        std::vector<QVariant> insertOneSoftirq(const monitor::proto::SoftIrq &softirq);
        
        std::vector<std::vector<QVariant>> m_monitor_data; // 监控数据
        QStringList m_header; // 表头

        enum SoftIrq{
            CPU_NUM = 0,
            HI,
            TIMER,
            NET_TX,
            NET_RX,
            BLOCK,
            IRQ_POLL,
            TASKLET,
            SCHED,
            HRTIMER,
            RCU,
            COLUMN_MAX
        };
    };
}

#endif // __CPU_SOFTIRQ_H__