#include "cpu_softirq.h"

namespace monitor {
    CPUSoftIrqModel::CPUSoftIrqModel(QObject *parent)
        : MonitorInterModel(parent)
    {
        m_header << tr("CPU Number");
        m_header << tr("hi");
        m_header << tr("Timer");
        m_header << tr("Net TX");
        m_header << tr("Net RX");
        m_header << tr("Block");
        m_header << tr("IRQ Poll");
        m_header << tr("Tasklet");
        m_header << tr("Sched");
        m_header << tr("HRTimer");
        m_header << tr("RCU");
    }

    QVariant CPUSoftIrqModel::data(const QModelIndex &index, int role) const
    {
        if (index.column() < 0 || index.column() >= SoftIrq::COLUMN_MAX)
        {
            return QVariant();
        }
        else if (role == Qt::DisplayRole)
        {
            if (index.row() < m_monitor_data.size() && index.column() < SoftIrq::COLUMN_MAX)
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

    QVariant CPUSoftIrqModel::headerData(int section, Qt::Orientation orientation, int role) const
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

    int CPUSoftIrqModel::rowCount(const QModelIndex &parent) const
    {
        return m_monitor_data.size();
    }

    void CPUSoftIrqModel::UpdateMonitorInfo(const monitor::proto::MonitorInfo &monitor_info)
    {
        beginResetModel();
        m_monitor_data.clear();
        for (size_t i=0; i < monitor_info.soft_irq_size(); ++i)
        {
            m_monitor_data.push_back(insertOneSoftirq(monitor_info.soft_irq(i)));
        }
        endResetModel();
    }

    std::vector<QVariant> CPUSoftIrqModel::insertOneSoftirq(const monitor::proto::SoftIrq &softirq)
    {
        std::vector<QVariant> softIrq_list;

        for(size_t i=SoftIrq::CPU_NUM; i < SoftIrq::COLUMN_MAX; ++i)
        {
            switch (i)
            {
                case SoftIrq::CPU_NUM:
                    softIrq_list.push_back(QString::fromStdString(softirq.cpu()));
                    break;
                case SoftIrq::HI:
                    softIrq_list.push_back(softirq.hi());
                    break;
                case SoftIrq::TIMER:
                    softIrq_list.push_back(softirq.timer());
                    break;
                case SoftIrq::NET_TX:
                    softIrq_list.push_back(softirq.net_tx());
                    break;
                case SoftIrq::NET_RX:
                    softIrq_list.push_back(softirq.net_rx());
                    break;
                case SoftIrq::BLOCK:
                    softIrq_list.push_back(softirq.block());
                    break;
                case SoftIrq::IRQ_POLL:
                    softIrq_list.push_back(softirq.irq_poll());
                    break;
                case SoftIrq::TASKLET:
                    softIrq_list.push_back(softirq.tasklet());
                    break;
                case SoftIrq::SCHED:
                    softIrq_list.push_back(softirq.sched());
                    break;
                case SoftIrq::HRTIMER:
                    softIrq_list.push_back(softirq.hrtimer());
                    break;
                case SoftIrq::RCU:
                    softIrq_list.push_back(softirq.rcu());
                    break;
                default:
                    break;
            }
        }

        return softIrq_list;
    }

    int CPUSoftIrqModel::columnCount(const QModelIndex &parent) const
    {
        return SoftIrq::COLUMN_MAX;
    }
}