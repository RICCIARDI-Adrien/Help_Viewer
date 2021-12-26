/** @file Configuration.cpp
 * See Configuration.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <Configuration.hpp>

namespace Configuration
{
    /** Hold the system language Qt identifier. */
    static QLocale::Language _languageId = QLocale::English;
    /** Hold the custom system language string. */
    static QString _languageString;

    void initialize()
    {
        // Find current language
        _languageId = QLocale::system().language();

        // Determine custom language string, try to conform to ISO 639 (this might be replaced by QLocale::languageToCode() method as soon as only Qt 6.1 and onward versions are used)
        switch (_languageId)
        {
            case QLocale::French:
                _languageString = "fr";
                break;

            case QLocale::German:
            case QLocale::SwissGerman:
                _languageId = QLocale::German;
                _languageString = "de";
                break;

            case QLocale::Spanish:
                _languageString = "es";
                break;

            default:
                _languageString = "en";
                break;
        }
    }

    QLocale::Language getSystemLanguageId()
    {
        return _languageId;
    }

    QString getSystemLanguageString()
    {
        return _languageString;
    }
}
