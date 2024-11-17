// comboboxmanager.cpp
#include "comboboxmanager.h"
#include <QFont>
#include <QDateTime>

ComboBoxManager& ComboBoxManager::instance() {
    static ComboBoxManager instance;
    return instance;
}

void ComboBoxManager::initializeComboBox(QComboBox* comboBox, ComboBoxType type) {
    if (!comboBox) return;

    comboBox->clear();
    setComboBoxStyle(comboBox);

    QList<ComboBoxConfig> configs;

    // 如果缓存中有数据，使用缓存数据
    if (configCache.contains(type)) {
        configs = configCache[type];
    } else {
        configs = getDefaultConfigs(type);
        configCache[type] = configs;
    }

    // 添加选项
    for (const auto& config : configs) {
        comboBox->addItem(config.displayText, config.value);
        if (config.isDefault) {
            comboBox->setCurrentText(config.displayText);
        }
    }
}
QList<ComboBoxConfig> ComboBoxManager::getDefaultConfigs(ComboBoxType type) {
    QList<ComboBoxConfig> configs;

    switch (type) {
    case ComboBoxType::AcademicYear: {
        configs.append({"请选择学年", -1, true});  // Add default empty option
        int currentYear = QDateTime::currentDateTime().date().year();
        for (int year = currentYear; year >= currentYear - 10; --year) {
            configs.append({
                QString::number(year),
                year,
                false
            });
        }
        break;
    }

    case ComboBoxType::Semester: {
        configs = {
            {"请选择学期", -1, true},
            {"第一学期", 1, false},
            {"第二学期", 2, false},
            {"第三学期", 3, false}
        };
        break;
    }

    case ComboBoxType::Department: {
        configs = {
            {"请选择院系", "", true},  // 默认空选项
            {"计算机科学与技术学院", "CS", false},
            {"电子工程学院", "EE", false},
            {"数学与统计学院", "MATH", false},
            {"物理科学与技术学院", "PHY", false},
            {"化学与分子工程学院", "CHEM", false},
            {"生命科学学院", "BIO", false},
            {"外国语学院", "ENG", false},
            {"历史文化学院", "HIST", false},
            {"法学院", "LAW", false},
            {"经济学院", "ECON", false},
            {"管理学院", "MANAGE", false},
            {"医学院", "MED", false},
            {"艺术学院", "ART", false},
            {"教育学院", "EDU", false},
            {"环境科学与工程学院", "ENV", false},
            {"建筑学院", "ARCH", false}
        };
        break;
    }
    case ComboBoxType::Capacity: {
        configs = {
            {"请选择容量", -1, true},  // Add default empty option
            {"有", true, false},
            {"无", false, false}
        };
        break;
    }
    default:
        break;
    }

    return configs;
}
void ComboBoxManager::updateComboBoxData(ComboBoxType type,
                                         const QList<ComboBoxConfig>& newData) {
    configCache[type] = newData;
}

void ComboBoxManager::registerCustomInitializer(
    const QString& customType,
    std::function<QList<ComboBoxConfig>()> initializer) {
    customInitializers[customType] = initializer;
}

void ComboBoxManager::setComboBoxStyle(QComboBox* comboBox) {
    // 设置字体
    QFont font = comboBox->font();
    font.setFamily("Microsoft YaHei");
    font.setPixelSize(14);
    font.setHintingPreference(QFont::PreferFullHinting);
    comboBox->setFont(font);

    // 设置样式
    comboBox->setMinimumWidth(120);
    comboBox->setStyleSheet(
        "QComboBox {"
        "    padding: 5px 10px;"
        "    border: 1px solid #ccc;"
        "    border-radius: 4px;"
        "    background: white;"
        "}"
        "QComboBox::drop-down {"
        "    border: none;"
        "    width: 24px;"
        "    border-top-right-radius: 8px;"
        "    border-bottom-right-radius: 8px;"
        "}"
        "QComboBox::down-arrow {"
        "    image: url(:/icon/img/down-arrow.png);"
        "    width: 12px;"
        "    height: 12px;"
        "}"
        "QComboBox QAbstractItemView {"
        "    border: 1px solid #e0e0e0;"
        "    border-radius: 8px;"
        "    padding: 4px;"
        "    margin-top: 4px;"
        "    background-color: white;"
        "    selection-background-color: #f0f7ff;"
        "    selection-color: #4a90e2;"
        "    outline: none;"
        "}"
        );
}
