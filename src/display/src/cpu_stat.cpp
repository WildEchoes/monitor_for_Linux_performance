#include "cpu_stat.h"

namespace monitor
{
    CPUStatModel::CPUStatModel(QObject *parent)
        : MonitorInterModel(parent)
    {
        m_header << tr("CPU Name");
        m_header << tr("CPU Percent");
        m_header << tr("Usr Percent");
        m_header << tr("Sys Percent");
        m_header << tr("Nice Percent");
        m_header << tr("Idle Percent");
        m_header << tr("Iowait Percent");
        m_header << tr("Irq Percent");
        m_header << tr("Softirq Percent");
    }

    QVariant CPUStatModel::data(const QModelIndex &index, int role) const
    {
        if (index.column() < 0 || index.column() >= CPUStat::COLUMN_MAX)
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
    }

    QVariant CPUStatModel::headerData(int section, Qt::Orientation orientation, int role) const
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

    int CPUStatModel::rowCount(const QModelIndex &parent) const
    {
        return m_monitor_data.size();
    }

    int CPUStatModel::columnCount(const QModelIndex &parent) const
    {
        return CPUStat::COLUMN_MAX;
    }

    void CPUStatModel::UpdateMonitorInfo(const monitor::proto::MonitorInfo &monitor_info)
    {
        beginResetModel();

        m_monitor_data.clear();
        for (int i = 0; i < monitor_info.cpu_stat_size(); i++)
        {
            m_monitor_data.push_back(insertOneCpuStat(monitor_info.cpu_stat(i)));
        }

        endResetModel();
    }

    std::vector<QVariant> CPUStatModel::insertOneCpuStat(const monitor::proto::CpuStat &cpu_stat)
    {
        std::vector<QVariant> cpu_stat_list;
        for(size_t i = CPUStat::CPU_NAME; i < CPUStat::COLUMN_MAX; ++i)
        {
            // 保持有序
            switch (i)
            {
            case CPUStat::CPU_NAME:
                cpu_stat_list.push_back(QString::fromStdString(cpu_stat.cpu_name()));
                break;
            case CPUStat::CPU_PERCENT:
                cpu_stat_list.push_back(cpu_stat.cpu_percent());
                break;
            case CPUStat::USR_PERCENT:
                cpu_stat_list.push_back(cpu_stat.usr_percent());
                break;
            case CPUStat::SYS_PERCENT:
                cpu_stat_list.push_back(cpu_stat.sys_percent());
                break;
            case CPUStat::NICE_PERCENT:
                cpu_stat_list.push_back(cpu_stat.nice_percent());
                break;
            case CPUStat::IDLE_PERCENT:
                cpu_stat_list.push_back(cpu_stat.idle_percent());
                break;
            case CPUStat::IOWAIT_PERCENT:
                cpu_stat_list.push_back(cpu_stat.iowait_percent());
                break;
            case CPUStat::IRQ_PERCENT:
                cpu_stat_list.push_back(cpu_stat.irq_percent());
                break;
            case CPUStat::SOFTIRQ_PERCENT:
                cpu_stat_list.push_back(cpu_stat.softirq_percent());
                break;
            default:
                break;
            }
        }

        return cpu_stat_list;
    }

} // namespace monitor
