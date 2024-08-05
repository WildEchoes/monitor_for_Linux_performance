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

        // 根据不同的角色返回相应的数据显示属性，如对齐方式、文本颜色和背景颜色
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
        // 根据不同的角色返回相应的表头显示属性，如字体和背景颜色
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        int columnCount(const QModelIndex &parent = QModelIndex()) const override;

        void UpdateMonitorInfo(const monitor::proto::MonitorInfo &monitor_info);

    private:
        std::vector<QVariant> insertOneCpuLoad(const monitor::proto::CpuLoad &cpu_load);
        
        std::vector<std::vector<QVariant>> m_monitor_data;
        QStringList m_header;

        enum CPULoad{
            CPU_AVG_1 = 0,
            CPU_AVG_3,
            CPU_AVG_15,
            COLUMN_MAX
        };
    };
}

#endif // __CPU_LOAD_H__