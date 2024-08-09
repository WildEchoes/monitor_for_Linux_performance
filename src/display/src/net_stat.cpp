#include "net_stat.h"


namespace monitor
{
    NetModel::NetModel(QObject *parent)
        : MonitorInterModel(parent)
    {
        m_header << tr("Name");
        m_header << tr("Send Rate");
        m_header << tr("Send Packets Rate");
        m_header << tr("Receive Rate");
        m_header << tr("Receive Packets Rate");
    }

    QVariant NetModel::data(const QModelIndex &index, int role) const
    {
        if (index.column() < 0 || index.column() >= NetStat::COLUMN_MAX)
        {
            return QVariant();
        }
        else if (role == Qt::DisplayRole)
        {
            if (index.row() < m_monitor_data.size() && index.column() < COLUMN_MAX)
            {
                return m_monitor_data[index.row()][index.column()];
            }
        }
        else
        {
            return QVariant();
        }
        
        return QVariant();
    }

    QVariant NetModel::headerData(int section, Qt::Orientation orientation, int role) const
    {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
        {
            return m_header[section];
        }
        else
        {
            return MonitorInterModel::headerData(section, orientation, role);
        }
    }

    int NetModel::rowCount(const QModelIndex &parent) const
    {
        return m_monitor_data.size();
    }

    int NetModel::columnCount(const QModelIndex &parent) const
    {
        return NetStat::COLUMN_MAX;
    }

    void NetModel::UpdateMonitorInfo(const monitor::proto::MonitorInfo &monitor_info)
    {
        beginResetModel();

        m_monitor_data.clear();
        for (int i = 0; i < monitor_info.net_info_size(); i++)
        {
            m_monitor_data.push_back(insertOneNetInfo(monitor_info.net_info(i)));
        }

        endResetModel();
    }

    std::vector<QVariant> NetModel::insertOneNetInfo(const monitor::proto::NetInfo &net_info)
    {
        std::vector<QVariant> net_list;

        for(size_t i=NetStat::NAME; i<NetStat::COLUMN_MAX; ++i)
        {
            switch(i)
            {
                case NetStat::NAME:
                    net_list.push_back(QString::fromStdString(net_info.name()));
                    break;
                case NetStat::SEND_RATE:
                    net_list.push_back(QString::number(net_info.send_rate()));
                    break;
                case NetStat::SEND_PACKETS_RATE:
                    net_list.push_back(QString::number(net_info.send_packets_rate()));
                    break;
                case NetStat::RCV_RATE:
                    net_list.push_back(QString::number(net_info.rcv_rate()));
                    break;
                case NetStat::RCV_PACKETS_RATE:
                    net_list.push_back(QString::number(net_info.rcv_packets_rate()));
                    break;
                default:
                    break;
            }
        }

        return net_list;
    }
} // namespace monitor
