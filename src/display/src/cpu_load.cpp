#include "cpu_load.h"

monitor::CPULoadModel::CPULoadModel(QObject *parent)
    : MonitorInterModel(parent)
{
    m_header << tr("CPU Load 1");  // 翻译
    m_header << tr("CPU Load 3");
    m_header << tr("CPU Load 15");
}

monitor::CPULoadModel::~CPULoadModel()
{
}

QVariant monitor::CPULoadModel::data(const QModelIndex &index, int role) const
{
    if (index.column() < 0 || index.column() >= CPULoad::COLUMN_MAX) 
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole) 
    {
        if (index.row() < m_monitor_data.size() && index.column() < COLUMN_MAX)
            return m_monitor_data[index.row()][index.column()];
    }

    return QVariant();
}

QVariant monitor::CPULoadModel::headerData(int section, Qt::Orientation orientation, int role) const
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

int monitor::CPULoadModel::rowCount(const QModelIndex &parent) const
{
    return m_monitor_data.size();
}

int monitor::CPULoadModel::columnCount(const QModelIndex &parent) const
{
    return CPULoad::COLUMN_MAX;
}

void monitor::CPULoadModel::UpdateMonitorInfo(const monitor::proto::MonitorInfo &monitor_info)
{
    beginResetModel(); // 数据源被完全替换或重新加载

    m_monitor_data.clear();  // 清空上一次的数据
    m_monitor_data.push_back(insertOneCpuLoad(monitor_info.cpu_load()));  // 插入新的数据

    endResetModel();
}

std::vector<QVariant> monitor::CPULoadModel::insertOneCpuLoad(const monitor::proto::CpuLoad &cpu_load)
{
    std::vector<QVariant> cpu_load_data;
    for (size_t i = CPULoad::CPU_AVG_1; i < CPULoad::COLUMN_MAX; ++i)
    {
        switch (i)
        {
        case CPULoad::CPU_AVG_1:
            cpu_load_data.push_back(QString::number(cpu_load.load_avg_1()));
            break;
        case CPULoad::CPU_AVG_3:
            cpu_load_data.push_back(QString::number(cpu_load.load_avg_3()));
            break;
        case CPULoad::CPU_AVG_15:
            cpu_load_data.push_back(QString::number(cpu_load.load_avg_15()));
            break;
        default:
            break;
        }
    }
    return cpu_load_data;
}
