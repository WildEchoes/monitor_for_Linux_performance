#ifndef __CPU_LOAD_H__
#define __CPU_LOAD_H__

#include <QAbstractTableModel>
#include <vector>

#include "monitor_inter.h"

#include "monitor_info.grpc.pb.h"
#include "monitor_info.pb.h"

namespace monitor {
    class CPULoadModel : public MonitorInterModel {
        Q_OBJECT
    public:
        explicit CPULoadModel(QObject *parent = nullptr);
        virtual ~CPULoadModel();

        // 获取表中数据
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
        // 获取表头数据
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

        int rowCount(const QModelIndex &parent = QModelIndex()) const override;  // 返回行数
        int columnCount(const QModelIndex &parent = QModelIndex()) const override; // 返回列数

        void UpdateMonitorInfo(const monitor::proto::MonitorInfo &monitor_info);  // 更新监控信息

    private:
        std::vector<QVariant> insertOneCpuLoad(const monitor::proto::CpuLoad &cpu_load);
        
        std::vector<std::vector<QVariant>> m_monitor_data; // 监控数据
        QStringList m_header; // 表头

        enum CPULoad{
            CPU_AVG_1 = 0,
            CPU_AVG_3,
            CPU_AVG_15,
            COLUMN_MAX
        };
    };
}

#endif // __CPU_LOAD_H__