// comboboxmanager.h
#ifndef COMBOBOXMANAGER_H
#define COMBOBOXMANAGER_H

#include <QComboBox>
#include <QHash>
#include <QString>
#include <QVariant>
#include <functional>

// 定义组合框类型
enum class ComboBoxType {
    AcademicYear,
    Semester,
    Department,
    Capacity,
    Custom
};

// 组合框配置结构
struct ComboBoxConfig {
    QString displayText;  // 显示文本
    QVariant value;      // 实际值
    bool isDefault;      // 是否为默认选项
};

class ComboBoxManager {
public:
    static ComboBoxManager& instance();

    // 初始化指定类型的组合框
    void initializeComboBox(QComboBox* comboBox, ComboBoxType type);

    // 为自定义类型注册初始化函数
    void registerCustomInitializer(const QString& customType,
                                   std::function<QList<ComboBoxConfig>()> initializer);

    // 更新组合框数据
    void updateComboBoxData(ComboBoxType type, const QList<ComboBoxConfig>& newData);

    // 设置组合框样式
    void setComboBoxStyle(QComboBox* comboBox);

private:
    ComboBoxManager() = default;
    ~ComboBoxManager() = default;
    ComboBoxManager(const ComboBoxManager&) = delete;
    ComboBoxManager& operator=(const ComboBoxManager&) = delete;

    // 获取默认配置数据
    QList<ComboBoxConfig> getDefaultConfigs(ComboBoxType type);

    // 存储自定义初始化函数
    QHash<QString, std::function<QList<ComboBoxConfig>()>> customInitializers;

    // 缓存配置数据
    QHash<ComboBoxType, QList<ComboBoxConfig>> configCache;
};

#endif // COMBOBOXMANAGER_H
