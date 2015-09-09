#include "settings.h"

namespace System
{

    QSettings *Settings::m_Settings = 0;
    QMap<Settings::Section, QString> Settings::m_SectionStringMap;
    void Settings::Load()
    {
        if(!m_Settings)
            m_Settings = new QSettings(); //use application config for settings name etc

        if(m_SectionStringMap.size() == 0)
        {
            m_SectionStringMap[Section::System] = "System/";
            m_SectionStringMap[Section::Audio] = "Audio/";
            m_SectionStringMap[Section::Midi] = "Midi/";
            m_SectionStringMap[Section::Transport] = "Transport/";
            m_SectionStringMap[Section::UI] = "UI/";
        }
    }

    void Settings::Destroy()
    {
        delete m_Settings;
        m_Settings = 0;

        m_SectionStringMap.clear();
    }

    void Settings::SetValue(Section section, const QString& valName, const QVariant &value)
    {
        m_Settings->setValue(m_SectionStringMap[section] + valName, value);
    }

    QVariant Settings::GetValue(Settings::Section section, const QString &valName, const QVariant &defaultValue)
    {
        return m_Settings->value(m_SectionStringMap[section] + valName, defaultValue);
    }

    void Settings::Save()
    {
        m_Settings->sync();
    }
}
