#include "monitor_inter.h"

#include <QColor>
#include <QFont>

monitor::MonitorInterModel::MonitorInterModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

monitor::MonitorInterModel::~MonitorInterModel()
{
}

QVariant monitor::MonitorInterModel::data(const QModelIndex &index, int role) const
{
    
    if (role == Qt::TextAlignmentRole) 
    {
        // 文本对齐方式，返回左对齐，垂直居中
        return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
    }
    else if (role == Qt::ForegroundRole)
    {
        // 文本颜色，返回黑色
        return QVariant::fromValue(QColor(Qt::black));
    }
    else if (role == Qt::BackgroundRole)
    {
        // 背景颜色，返回白色
        return QVariant::fromValue(QColor(Qt::white));
    }
    else
    {
        return QVariant();
    }
}

QVariant monitor::MonitorInterModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::FontRole) 
    {
        // 字体，返回微软雅黑，10号，加粗
        return QVariant::fromValue(QFont("Microsoft YaHei", 10, QFont::Bold));
    }
    else if (role == Qt::BackgroundRole) 
    {
        // 背景颜色，返回浅灰色
        return QVariant::fromValue(QColor(Qt::lightGray));
    }
    else
    {
        // 其他情况，调用父类的headerData函数
        return QAbstractTableModel::headerData(section, orientation, role);
    }
}

