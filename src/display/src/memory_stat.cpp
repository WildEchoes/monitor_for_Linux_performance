#include "memory_stat.h"

namespace monitor {
    MemoryModel::MemoryModel(QObject *parent)
        : MonitorInterModel(parent)
    {
        m_header << tr("Used Percent");
        m_header << tr("Total");
        m_header << tr("Free");
        m_header << tr("Avail");
        m_header << tr("Buffers");
        m_header << tr("Cached");
        m_header << tr("Swap Cached");
        m_header << tr("Active");
        m_header << tr("Inactive");
        m_header << tr("Active Anon");
        m_header << tr("Inactive Anon");
        m_header << tr("Dirty");
        m_header << tr("Writeback");
        m_header << tr("Anon Pages");
        m_header << tr("Mapped");
        m_header << tr("KReclaimable");
        m_header << tr("SReclaimable");
        m_header << tr("SUnreclaim");
    }

    QVariant MemoryModel::data(const QModelIndex &index, int role) const
    {
        if (index.column() < 0 || index.column() >= MemoryStat::COLUMN_MAX)
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

    QVariant MemoryModel::headerData(int section, Qt::Orientation orientation, int role) const
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

    int MemoryModel::rowCount(const QModelIndex &parent) const
    {
        return m_monitor_data.size();
    }

    int MemoryModel::columnCount(const QModelIndex &parent) const
    {
        return MemoryStat::COLUMN_MAX;
    }

    void MemoryModel::UpdateMonitorInfo(const monitor::proto::MonitorInfo &monitor_info)
    {
        beginResetModel();

        m_monitor_data.clear();
        m_monitor_data.push_back(insertOneMemoryInfo(monitor_info.mem_info()));

        endResetModel();
    }

    std::vector<QVariant> MemoryModel::insertOneMemoryInfo(const monitor::proto::MemoryInfo &mem_info)
    {
        std::vector<QVariant> mem_list;

        for(size_t i=MemoryStat::USED_PERCENT; i<MemoryStat::COLUMN_MAX; ++i)
        {
            switch(i)
            {
                case MemoryStat::USED_PERCENT:
                    mem_list.push_back(mem_info.used_percent());
                    break;
                case MemoryStat::TOTAL:
                    mem_list.push_back(mem_info.total());
                    break;
                case MemoryStat::FREE:
                    mem_list.push_back(mem_info.free());
                    break;
                case MemoryStat::AVAIL:
                    mem_list.push_back(mem_info.avail());
                    break;
                case MemoryStat::BUFFERS:
                    mem_list.push_back(mem_info.buffers());
                    break;
                case MemoryStat::CACHED:
                    mem_list.push_back(mem_info.cached());
                    break;
                case MemoryStat::SWAP_CACHED:
                    mem_list.push_back(mem_info.swap_cached());
                    break;
                case MemoryStat::ACTIVE:
                    mem_list.push_back(mem_info.active());
                    break;
                case MemoryStat::INACTIVE:
                    mem_list.push_back(mem_info.inactive());
                    break;
                case MemoryStat::ACTIVE_ANON:
                    mem_list.push_back(mem_info.active_anon());
                    break;
                case MemoryStat::INACTIVE_ANON:
                    mem_list.push_back(mem_info.inactive_anon());
                    break;
                case MemoryStat::DIRTY:
                    mem_list.push_back(mem_info.dirty());
                    break;
                case MemoryStat::WRITEBACK:
                    mem_list.push_back(mem_info.writeback());
                    break;
                case MemoryStat::ANON_PAGES:
                    mem_list.push_back(mem_info.anon_pages());
                    break;
                case MemoryStat::MAPPED:
                    mem_list.push_back(mem_info.mapped());
                    break;
                case MemoryStat::KRECLAIMABLE:
                    mem_list.push_back(mem_info.kreclaimable());
                    break;
                case MemoryStat::SRECLAIMABLE:
                    mem_list.push_back(mem_info.sreclaimable());
                    break;
                case MemoryStat::SUNRECLAIM:
                    mem_list.push_back(mem_info.sunreclaim());
                    break;
                default:
                    break;
            }
        }

        return mem_list;
    }
}
