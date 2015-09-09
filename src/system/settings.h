#ifndef SETTINGS_H
#define SETTINGS_H

#include "QSettings"
#include "QMap"


class MainWindow;
namespace System
{
    class Settings
    {
        friend class ::MainWindow;

    public:

        enum class Section
        {
            System,
            Audio,
            Midi,
            Transport,
            UI,
        };

    public:
        ~Settings();


        static void SetValue(Section section, const QString& valName, const QVariant &value);
        static QVariant GetValue(Section section, const QString& valName, const QVariant &defaultValue = QVariant());

        //The settings are saved automatically by the event loop at regular intervals, so you normally don't need to call this yourself.
        static void Save();

    protected:
        static void Load();
        static void Destroy();

    private:
        /* No instantiation. */
        Settings() {}

        /* Explicitly disallow copying. */
        Settings(const Settings&) = delete;
        Settings& operator= (const Settings&) = delete;

    private:

        static QMap<Section, QString> m_SectionStringMap;
        static QSettings *m_Settings;
    };
}
#endif // SETTINGS_H
