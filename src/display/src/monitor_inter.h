#ifndef __MONITOR_INTER_H__
#define __MONITOR_INTER_H__

#include <QAbstractTableModel>
#include <QObject>

namespace monitor {
    class MonitorInterModel : public QAbstractTableModel {
        Q_OBJECT
    public:
    explicit MonitorInterModel(QObject *parent = nullptr);
    virtual ~MonitorInterModel();
    
    // 根据不同的角色返回相应的数据显示属性，如对齐方式、文本颜色和背景颜色
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    // 根据不同的角色返回相应的表头显示属性，如字体和背景颜色
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};
}

#endif // __MONITOR_INTER_H__