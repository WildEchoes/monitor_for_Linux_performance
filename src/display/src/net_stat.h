#ifndef __NET_STAT_H__
#define __NET_STAT_H__

#include "monitor_inter.h"

#include "monitor_info.grpc.pb.h"
#include "monitor_info.pb.h"

namespace monitor {
    class NetModel : public MonitorInterModel {
        Q_OBJECT
    public:
        explicit NetModel(QObject *parent = nullptr);
        virtual ~NetModel() {};

        // 获取表中数据
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
        // 获取表头数据
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

        int rowCount(const QModelIndex &parent = QModelIndex()) const override;  // 返回行数
        int columnCount(const QModelIndex &parent = QModelIndex()) const override; // 返回列数

        void UpdateMonitorInfo(const monitor::proto::MonitorInfo &monitor_info);  // 更新监控信息

    private:
        std::vector<QVariant> insertOneNetInfo(const monitor::proto::NetInfo &net_info);
        
        std::vector<std::vector<QVariant>> m_monitor_data; // 监控数据
        QStringList m_header; // 表头

        enum NetStat{
            NAME = 0,
            SEND_RATE,
            SEND_PACKETS_RATE,
            RCV_RATE,
            RCV_PACKETS_RATE,
            COLUMN_MAX
        };
    };
}

#endif // __NET_STAT_H__